#include "game.h"
#include "match.h"

char Game::waitForValidInput(set<char> validInputList){
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

Pattern Game::getProcessablePattern(string unprocessedInputs){
	for(Pattern pat : romajiTable.getAllPattern())
		if(unprocessedInputs == pat.getStroke())
			return pat;

	cout << "ERROR: " << endl;
	exit(1);
}

int Game::calcuPotentialPatternNum(string unprocessedInputs, int unuseInput){

	if(unuseInput > 0)
		unprocessedInputs = unprocessedInputs.substr(0, unprocessedInputs.size() - unuseInput);

	if(debugFlag && unuseInput > 0)
		cout << endl << "(in calcuPotentialPatternNum())unprocessedInputs = " << unprocessedInputs << endl;

	int patternNum = 0;
	if(unuseInput == -1){
		for(Pattern pat : romajiTable.getAllPattern())
			patternNum += (int)prefixMatch<string>(unprocessedInputs, pat.getStroke());
	}else{
		for(Pattern pat : romajiTable.getAllPattern()){
			patternNum += (int)(unprocessedInputs == pat.getStroke());
		}
	}

	return patternNum;
}

set<char> Game::makeValidInputList(StringJ objective, int index,string unprocessedInputs){
	string objectiveKana = objective.nthUnicodeLetter(index);
	candidatePat.reset(romajiTable.firstCandidate(objectiveKana).getPatterns());
	candidatePat.onlyCompatibleWithCurrentInput(unprocessedInputs);
	candidatePat.onlyCompatibleWithNextKanas(objective, index, romajiTable.getAllPattern());
	set<char> validInputList = candidatePat.getValidInput(unprocessedInputs);

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
	set<char> anotherList;
	if(cnt == 1){
		string stroke = processablePat.getStroke();
		vector<string> kana = processablePat.getObjective();
		string potentialInput;
		for(int i = stroke.size(); i < unprocessedInputs.size(); i++){
			potentialInput += unprocessedInputs[i];
		}
		anotherList = makeValidInputList(objective, index+kana.size(), potentialInput);
		/* TODO check infinite loop */
	}

	validInputList = Union(validInputList, anotherList);
	if(debugFlag){
		cout << "validInputList: [";
		for(char c : validInputList)
			cout << c;
		cout << "]" << endl;
	}
	/* check valid inputs */
	if(validInputList.empty()){
		cout << "No valid input for objectiveKana " << objectiveKana;
		cout  << " and unprocessedInputs \"" << unprocessedInputs << "\"" << endl;
		exit(1);
	}

	validInputList.erase('\0');
	return validInputList;
}

void Game::process(string *unprocessedInputs, int *index, int unuseInputNum){
	Pattern selectedPattern = getProcessablePattern(unprocessedInputs->substr(0,unprocessedInputs->size() -unuseInputNum));
	string unprocessedInputsStore 
		= unprocessedInputs->substr(unprocessedInputs->size()-unuseInputNum, unprocessedInputs->size());
	vector<string> carryKana;
	carryKana = selectedPattern.getObjective();
	*index += carryKana.size(); 
	*unprocessedInputs = selectedPattern.getOutput() + unprocessedInputsStore;
	if(debugFlag){
		cout << "carryKana.size() = " << carryKana.size();
		cout << "kana ";
		for( string str : carryKana)
			cout << str;
		cout << " is proccessed" << endl;
	}
}

void Game::typeStringChallenge(StringJ objective){

	int index = 0;
	string unprocessedInputs = "";
	if(debugFlag){
		cout << "objective.size() = " << objective.size() << endl;
	}

	while(index < objective.size()-1){

		if(debugFlag){
			string objectiveKana = objective.nthUnicodeLetter(index);
			cout << "new objective: " << objectiveKana << "  (" << index << "th letter)" << endl;
			cout << "unprocessedInputs: " << unprocessedInputs << endl;
		}

		set<char> validInputList = makeValidInputList(objective, index, unprocessedInputs);

		unprocessedInputs += waitForValidInput(validInputList);

		if(calcuPotentialPatternNum(unprocessedInputs) == 1){
			process(&unprocessedInputs, &index);
		}else if(calcuPotentialPatternNum(unprocessedInputs) == 0){
			if(calcuPotentialPatternNum(unprocessedInputs,1) == 1){
				process(&unprocessedInputs, &index,1);
			}
		}

	}
}

void Game::setObjective(string objectiveFile){
	objectiveFile = OBJECTIVE_FILE_PREFIX + objectiveFile;
	std::ifstream ifs(objectiveFile);
	if (ifs.fail()){
		std::cerr << objectiveFile << " の読み込みに失敗" << std::endl;
		exit(1);
	}

	string line;
	while (getline(ifs, line)){
		if(line[0] == '#'){
			int i = 1;
			while(line[i] == ' '){
				i++;
			}
			gameTitle += line.substr(i,line.size()) + '\n';
		}else{
			addObjective(line + " ");
		}
	}

	cout << "文字列リスト読み込み完了" << endl;

}

Game::Game(RomajiTable table, string objectiveFile){
	setTable(table);
	setObjective(objectiveFile);
}

Game::Game(string tableFile, string objectiveFile){
	tableFile = TABLE_FILE_PREFIX + tableFile;
	romajiTable.set(tableFile);
	cout << "ローマ字テーブル読み込み完了" << endl;
	setObjective(objectiveFile);
}

void Game::addObjective(string newObjective){
	vector<string> newList= split(newObjective,'\n');
	this->objectiveList.insert(objectiveList.end(), newList.begin(), newList.end());
}

void Game::setSeq(bool flag){
	this->seqFlag = flag;
}

void Game::setRound(int num){
	this->loop = num;
}

void Game::setTable(RomajiTable table){
	this->romajiTable = table;
}

void Game::run(){
	cout << endl << gameTitle << endl;
	for(int i = 0; i < loop; i++){
		int objectiveListSize = objectiveList.size();
		string objective;
		if(seqFlag){
			loop = objectiveList.size();
			objective = objectiveList[i];
		}else{
			objective = objectiveList[rand() % objectiveListSize];
		}

		cout << objective << endl;
		typeStringChallenge(objective);
		cout <<  endl << "Done " << i+1 << " of " << loop << endl;
	}
}

