#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "stringJ.h"
#include "keyboard.h"
#include "cmdline.h"
#include "pattern.h"
#include "split.h"
#include "romajitable.h"
using namespace std;

const std::string VERSION = "0.01";
const std::string TABLE_FILE_PREFIX = "./tables/";
const std::string OBJECTIVE_FILE_PREFIX= "./objectives/";
bool debugFlag = false;

template<typename T_TYPE>
bool prefixMatch(T_TYPE prefix, T_TYPE objective){
	if(prefix.size() > objective.size()){
		return false;
	}

	bool found = true;

	for(int i = 0; i < prefix.size(); i++){
		if(prefix[i] != objective[i]){
			found = false;
			break;
		}
	}

	return found;
}

class Game {
	private:
		int loop = 3;
		RomajiTable romajiTable;
		CandidatePattern candidatePat;
		vector<string> objectiveList;
		vector<Pattern> potentialPattern;

		char waitForValidInput(vector<char> validInputList = vector<char>()){
			/* cout << "now you can type" << endl; */
			bool valid = false;
			cout << " "; // place holder
			while( !valid ){
				cout << "\x1b[1D"; // move cursor to left by 1 char
				char input = getKeyboardInput();
				for( char candidate : validInputList){
					if( input == candidate){
						valid = true;
						cout << input;
						return input;
					}
				}
				if(valid) break;

				cout << "\x1b[K";  // delete output from right of cursor to end of line

				/* make it red */
				cout << "\x1b[31m";
				cout << input;
				cout << "\x1b[0m";
			}

			/* the loop cant be existed */
			cout << "ERROR:" << endl;
			exit(1);
		}

		Pattern process(string unprocessedInputs){
			vector<Pattern> patternSet;
			if(!potentialPattern.empty()){
				patternSet = potentialPattern;
			}else{
				patternSet = romajiTable.getAllPattern();
			}
			for(Pattern pat : patternSet)
				if(unprocessedInputs == pat.getStroke())
					return pat;


			cout << "ERROR: " << endl;
			exit(1);
		}

		int calcuPotentialPatternNum(string unprocessedInputs, int unuseInput = 0){
			if(unuseInput > unprocessedInputs.size()){
				exit(1);
			}

			if(unuseInput > 0)
				unprocessedInputs = unprocessedInputs.substr(0, unprocessedInputs.size() - unuseInput);
			potentialPattern.clear();

			vector<Pattern> patternSet;
			if(!potentialPattern.empty()){
				patternSet = potentialPattern;
			}else{
				patternSet = romajiTable.getAllPattern();
			}
			if(debugFlag && unuseInput > 0)
				cout << endl << "(in calcuPotentialPatternNum())unprocessedInputs = " << unprocessedInputs << endl;

			int patternNum = 0;
			if(unuseInput == 0){
				for(Pattern pat : patternSet)
					patternNum += (int)prefixMatch<string>(unprocessedInputs, pat.getStroke());
			}else{
				for(Pattern pat : patternSet){
					/* cout << unprocessedInputs << " == " << pat.getStroke() << "?)" <<endl; */
					patternNum += (int)(unprocessedInputs == pat.getStroke());
					/* (pat.getStroke() == unprocessedInputs); */
				}
			}

			return patternNum;
		}

		vector<char> makeValidInputList(StringJ objective, int index,string unprocessedInputs){
			string objectiveKana = objective.nthUnicodeLetter(index);
			candidatePat.reset(romajiTable.firstCandidate(objectiveKana).getPatterns());
			candidatePat.onlyCompatibleWithCurrentInput(unprocessedInputs);
			vector<char> validInputList = candidatePat.getValidInput(unprocessedInputs);

			int cnt = 0;
			Pattern processablePat;
			for(Pattern pat : romajiTable.getAllPattern()){
				if(pat.getStroke() == unprocessedInputs){
					cnt++;
					processablePat = pat;	
					if(cnt > 1)
						break;
				}
			}
			vector<char> anotherList;
			if(cnt == 1){
				string stroke = processablePat.getStroke();
				string output = processablePat.getOutput();
				std::vector<string> kana = processablePat.getObjective();
				string potentialInput;
				for(int i = stroke.size(); i < unprocessedInputs.size(); i++){
					potentialInput += unprocessedInputs[i];
				}
				anotherList = makeValidInputList(objective, index+kana.size(), potentialInput);
			}

			validInputList.insert(validInputList.end(), anotherList.begin(), anotherList.end());
			/* check valid inputs */
			if(validInputList.empty()){
				cout << "No valid input for objectiveKana " << objectiveKana;
				cout  << " and unprocessedInputs \"" << unprocessedInputs << "\"" << endl;
				exit(1);
			}
			return validInputList;
		}

		void typeStringChallenge(StringJ objective){

			int index = 0;
			string unprocessedInputs = "";
			potentialPattern.clear();
			if(debugFlag)
				cout << "objective.size() = " << objective.size() << endl;

			while(index < objective.size()){

				if(debugFlag){
					string objectiveKana = objective.nthUnicodeLetter(index);
					cout << "new objective: " << objectiveKana << "  (" << index << "th letter)" << endl;
					cout << "unprocessedInputs: " << unprocessedInputs << endl;
				}

				vector<char> validInputList = makeValidInputList(objective, index, unprocessedInputs);

				/* loop until getting valid input */
				unprocessedInputs += waitForValidInput(validInputList);
				if(debugFlag)
					cout  << "unprocessedInputs \"" << unprocessedInputs << "\"" << endl;

				/* if unprocessedInputs is same with any pattern, go to nextletter */
				if(calcuPotentialPatternNum(unprocessedInputs) == 0){
					if(calcuPotentialPatternNum(unprocessedInputs,1) == 1){
						/* cout << "processing n" << endl; */
						Pattern selectedPattern = process(unprocessedInputs.substr(0,unprocessedInputs.size()-1));
						vector<string> carryKana;
						carryKana = selectedPattern.getObjective();
						string storeInput = unprocessedInputs;
						unprocessedInputs = "";
						for(int i = selectedPattern.getStroke().size(); i < storeInput.size(); i++){
							unprocessedInputs += storeInput[i];
						}

						if(debugFlag)
							cout  << "renewed unprocessedInputs \"" << unprocessedInputs << "\"" << endl;

						index += carryKana.size(); 
						if(debugFlag){
							cout << endl;
							cout << "carryKana.size() = " << carryKana.size();
							cout << "kana ";
							for( string str : carryKana)
								cout << str;
							cout << " is proccessed" << endl;
						}
					}
				}

				if(calcuPotentialPatternNum(unprocessedInputs) == 1){
					if(candidatePat.hasProcessablePatternOf(unprocessedInputs)){
						Pattern selectedPattern = candidatePat.getSelected();
						vector<string> carryKana;
						carryKana = selectedPattern.getObjective();
						index += carryKana.size(); 
						unprocessedInputs = selectedPattern.getOutput();
						if(debugFlag){
							cout << "carryKana.size() = " << carryKana.size();
							cout << "kana ";
							for( string str : carryKana)
								cout << str;
							cout << " is proccessed" << endl;
						}
					}
				}

			}
		}

	public:
		Game(string tableFile = "googleNihongoRomajiTable", string objectiveFile = "default"){
			tableFile = TABLE_FILE_PREFIX + tableFile;
			romajiTable.set(tableFile);
			cout << "ローマ字テーブル読み込み完了" << endl;

			objectiveFile = OBJECTIVE_FILE_PREFIX + objectiveFile;
			std::ifstream ifs(objectiveFile);
			if (ifs.fail()){
				std::cerr << objectiveFile << " の読み込みに失敗" << std::endl;
				exit(1);
			}
			string line;
			while (getline(ifs, line)){
				addObjective(line);
			}
			cout << "文字列リスト読み込み完了" << endl;
		}
		void run(){
			for(int i = 0; i < loop; i++){
				int objectiveListSize = objectiveList.size();
				string objective = objectiveList[rand() % objectiveListSize];

				cout << "Type " << objective << endl;
				cout << " " << objective << endl;
				typeStringChallenge(objective);
				cout <<  endl << "Done " << i+1 << " of " << loop << endl;
			}
		}

		void addObjective(string newObjective){
			vector<string> newList= split(newObjective,'\n');
			objectiveList.insert(objectiveList.end(), newList.begin(), newList.end());
		}

};

int main(int argc, char *argv[]) {
	cmdline::parser a;
	a.add("debug", 'd', "debagFlag = true に設定します。");
	a.add<string>("table", 't', "ローマ字テーブルファイル名", false, "./googleNihongoRomajiTable");
	a.parse_check(argc, argv);
	debugFlag = a.exist("debug");

	srand(time(NULL));
	cout << "Brownie ver. " << VERSION << endl;

	/* TODO set with getopt */
	string sourceFile = a.get<string>("table");

	Game newGame(sourceFile);
	newGame.run();
	cout << "You have done!";

	cout << endl;
	return 0;
}
