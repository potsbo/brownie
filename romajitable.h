#pragma once
extern bool debugFlag;

/* collection of pattern that can put a kana */
class PatternsForAKana {
	private:
		std::string objectiveKana;
		std::vector<Pattern> patterns;	
		std::vector<std::string> strokes;
	public:
		PatternsForAKana(Pattern newPat){
			if(!newPat.isValid()){
				newPat.print("");
				std::cout << "is not valid" << std::endl;
			}else{
				objectiveKana = newPat.getObjective()[0];
				patterns.push_back(newPat);
				strokes.push_back(newPat.getStroke());
			}
		}
		bool isAbleToReturn(std::string letter){
			return (objectiveKana == letter);
		}
		bool canHold(Pattern pat){
			/* std::cout << "hello in canhold()" << std::endl; */
			if(pat.isValid()){
				if( objectiveKana == pat.getObjective()[0]){
					return true;
				}
			}
			/* cout << "can't hold" << endl; */
			return false;
		}
		void add(Pattern newPat){
			if(newPat.isValid()){
			patterns.push_back(newPat);
			strokes.push_back(newPat.getStroke());
			}
			/* cout << patterns.size() << endl; */
			/* this->print(); */
		}
		std::vector<std::string> getStrokes(){
			return strokes;
		}

		std::vector<Pattern> getPatterns(){
			return patterns;
		}

		void print(){
			std::cout << "Objective: " << this->objectiveKana << " " << patterns.size() << std::endl;
			for(Pattern pat : patterns){
				pat.print();
			}
		}
};


class CandidatePattern {
	private:
		std::vector<Pattern> pats;
		Pattern patternToProcess;
	public:
		bool hasProcessablePatternOf(std::string unprocessedInputs){
			if(debugFlag)
				std::cout << std::endl << "stroke challenge " << unprocessedInputs << std::endl;
			for(Pattern pat : pats){
				if(unprocessedInputs == pat.getStroke()){
					patternToProcess = pat;
					return true;
				}
			}
			return false;
		}

		CandidatePattern(){};
		CandidatePattern(PatternsForAKana patterns){
			pats = patterns.getPatterns();
		}

		Pattern getSelected(){
			if(patternToProcess.isValid())
				return patternToProcess;
			std::cout << "ERROR: patternToProcess has not been created properly" << std::endl;
			exit(1);
		}

		void reset(std::vector<Pattern> pats){
			this->pats.clear();
			this->pats = pats;
		}

		void onlyCompatibleWithNextKanas(StringJ objective, int index, std::vector<Pattern> allPatterns){
			std::vector<char> requiredAlphabet;
			std::vector<Pattern>::iterator itr = pats.begin();
			while (itr != pats.end()) {
				bool compatiFlag = true;
				std::vector<std::string> kana = (*itr).getObjective();

				for(int i = 0; i < kana.size(); i++){
					if(i + index > objective.size()){
						compatiFlag = false;
						break;
					}
					if(kana[i] != objective.nthUnicodeLetter(i + index)){
						compatiFlag = false;
					}
				}
				if(!compatiFlag) {
					itr = pats.erase(itr);
				} else {
					++itr;
				}
			}

		}
		void onlyCompatibleWithCurrentInput(std::string currentInput){
			std::vector<Pattern>::iterator it;
			for( it=pats.begin(); it!=pats.end(); it++){
				if( !(*it).isCompatibleWithCurrentInput(currentInput)){
					pats.erase(it);
				}
			}
		}
		std::vector<char> getNthStrokes(int i){
			using namespace std;
			vector<char> letters;
			for( Pattern some : pats ){
				letters.push_back(some.nthStroke(i));
			}
			return letters;
		}
		
		/* this is safe to use after you call onlyCompatibleWithCurrentInput and onlyCompatibleWithNextLetter */
		std::set<char> getValidInput(std::string unprocessedInputs){
			if(debugFlag)
				for(Pattern pat : pats){
					std::cout << pat.getStroke() << std::endl;
				}
			std::vector<char> validInputList = getNthStrokes(unprocessedInputs.size());
			std::set<char> validInputSet;
			for(char c : validInputList){
				validInputSet.insert(c);
			}
			/* TODO exclude \0 */
			return validInputSet;
		}
};

class RomajiTable {
	private:
		std::vector<PatternsForAKana> analysedPatterns;
		std::vector<Pattern> allPatterns;
	public:
		void set(std::string sourceFile = "googleNihongoRomajiTable"){
			std::string tableString;
			if( sourceFile == ""){ 
				/* create table with ascii code */
				int startPoint = 32;
				int endPoint = 127;
				for(int i = startPoint; i < endPoint; i++){
					analysedPatterns.push_back(Pattern(i,i));
				}
			}else{
				std::ifstream ifs(sourceFile);
				if (ifs.fail()){
					std::cerr << "失敗" << std::endl;
					exit(1);
				}

				std::vector<Pattern> uniquePatterns;
				std::string line;
				while (getline(ifs, line)){
					Pattern newPattern(line);

					/* search same stroke to rewrite it */
					std::vector<Pattern>::iterator it;
					for( it=uniquePatterns.begin(); it!=uniquePatterns.end(); it++){
						if( (*it).hasSameStrokeWith(newPattern)){
							uniquePatterns.erase(it);
							break;
						}
					}
					uniquePatterns.push_back(newPattern);
				}
				Pattern sentinel(" \t ");
				uniquePatterns.push_back(sentinel);


				if(debugFlag)
					std::cout << "uniquePatterns.size() = " << uniquePatterns.size() << std::endl;
				allPatterns = uniquePatterns;

				for(Pattern newPattern : uniquePatterns){
					/* std::cout << "uniquePatterns loop..." << std::endl; */
					/* search a kana */
					bool found = false;
					for(int i = 0; i < analysedPatterns.size(); i++){
						if(analysedPatterns[i].canHold(newPattern)){
							/* cout << "hello in for loop" << endl; */
							analysedPatterns[i].add(newPattern);
							found = true;
							break;
						}
					}
					if(!found){
						analysedPatterns.push_back(newPattern);
					}
				}
			}
			if(debugFlag)
				printAnalysedPatterns();
		}

		void printAnalysedPatterns(){
			std::cout << "analysedPatterns.size(): " << analysedPatterns.size() << std::endl;
			for(PatternsForAKana patterns : analysedPatterns){
				patterns.print();
			}
		}

		PatternsForAKana firstCandidate(std::string kana){
			for(PatternsForAKana potentialPatterSet : analysedPatterns){
				if(potentialPatterSet.isAbleToReturn(kana)){
					return potentialPatterSet;
				}
			}
			std::cout << "breakpoint before" << std::endl;
			std::cout << "breakpoint after" << std::endl;
			std::cout << "ERROR: no usable stroke for \"" 
				<< kana << "\"  was found; check your romaji table" << std::endl;
			exit(1);
		}

		std::vector<Pattern> getAllPattern(){
			return allPatterns;
		}

		CandidatePattern getCandidate(std::string letter){
			for(PatternsForAKana potentialPatterSet : analysedPatterns){
				if(potentialPatterSet.isAbleToReturn(letter)){
					return CandidatePattern(potentialPatterSet);
				}
			}
			std::cout << "ERROR: no usable stroke for \"" 
				<< letter << "\"  was found; check your romaji table" << std::endl;
			exit(1);
		}
};

