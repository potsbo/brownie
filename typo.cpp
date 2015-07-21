#include "typo.h"
Typo::Typo(char c){
	this->c = c;
}

void Typo::increment (){
	this->cnt++;
}

void TypoSet::analyze(){
	/* TODO: implement analyze() */
	int alloverTypoCnt;
	for(char c : typoList){
		std::vector<Typo>::iterator itr;
		bool found = false;
		while(itr != typoSet.end()){
			if((*itr).getChara() == c){
				(*itr).increment();
				found = true;
				break;
			}
		}
		if(!found){
			typoSet.push_back(c);
		}
	}
}

void TypoSet::add(char c){
	typoList.push_back(c);
	tempCnt++;
}
void TypoSet::resetTempCnt(){
	tempCnt = 0;
}
void TypoSet::setMax(int max){
	this->mistakeMax = max;
}

bool TypoSet::reachLimit(){
	return (mistakeMax > 0 && tempCnt > mistakeMax);
}
