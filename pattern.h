#pragma once

#include "split.h"
#include "stringj.h"
extern bool debugFlag;

class Pattern {
	private:
		std::string stroke;
		StringJ kana;
		std::string output;
	public:
		Pattern(){};
		Pattern(char i, StringJ r, std::string o = ""){
			this->stroke = i;
			this->kana = r;

			if(output.size()>1){
				std::cout << "ERROR" << std::endl;
				exit(1);
				/* TODO for now we can NOT put more than one char after putting a kana */
			}
			this->output = o;
		}
		Pattern(char i, char r, std::string o = ""){
			std::string stroke(1,i);
			this->stroke = stroke;
			StringJ strj(r);
			this->kana = strj;
		}
		Pattern(std::string str){
			using namespace std;
			vector<string> sro = split(str,'\t');
			if(sro.size() > 1 && sro.size() < 4){
				this->stroke = sro[0];
				StringJ strj(sro[1]);
				this->kana = strj;
				if(sro.size() == 3){
					this->output = sro[3];
				}
			}
			/* this->print(); */
		}
		bool isValid(){
			if(stroke != "")
				return true;
			return false;
		}
		bool hasSameStrokeWith(Pattern pat){
			if(this->stroke == pat.getStroke()){
				return true;
			}
			return false;
		}
		bool isCompatibleWithNextInput(std::vector<char> requiredAlphabet){
			if(output == "" && this->kana.size() < 1){
				return true;
			}else{
				/* TODO think about the case kana has more then one letters */
				for(char letter : requiredAlphabet)
					if(letter == output[0])
						return true;
				return false;
			}
		}
		bool isCompatibleWithCurrentInput(std::string currentInput){
			for(int i = 0; i < currentInput.size(); i++)
				if(stroke[i] != currentInput[i])
					return false;
			return true;
		}
		char nthStroke(int i){
			return stroke[i];
		}

		std::string getStroke(){
			return stroke;
		}

		std::vector<std::string> getObjective(int i = -1){
			using namespace std;
			vector<string> res;
			for(int i = 0; i < kana.size(); i++){
				res.push_back(this->kana.nthUnicodeLetter(i));
			}
			if(res.empty() && debugFlag){
				cout << "Error: no objectiveKana for \'"<< stroke << "\'" << this->stroke.size();
				for(char c : stroke){
					printf("%d",c);
				}
				cout << endl;

				/* exit(1); */
			}
			return res;
		}
		std::string getOutput(){
			return output;
		}
		
		void print(std::string splitter = "\n"){
			std::cout << stroke << "\t" << kana.getStr() << "\t" << output << splitter;
		}
};


