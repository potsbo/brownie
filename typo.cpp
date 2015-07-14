#include "typo.h"
Typo::Typo(char c){
	this->c = c;
}

void TypoSet::analyze(){
	/* TODO: implement analyze() */
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
