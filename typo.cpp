#include "typo.h"
Typo::Typo(char c){
	this->c = c;
}
void Typo::increment(){
	cnt++;
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
bool TypoSet::reachLimit(){
	return (mistakeMax > 0 && tempCnt > mistakeMax);
}
