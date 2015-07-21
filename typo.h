#pragma once
#include <set>
#include <vector>
class Typo {
	private:
		int cnt = 0;
		char c;
	public:
		Typo(char c);
		int getCnt();
		int getChara();
		void increment();
};

class TypoSet  {
	private:
		std::vector<Typo> typoSet;
		std::vector<char> typoList;
		int tempCnt = 0;
		int mistakeMax = 0;
		int rankTopOf = 5;
		void analyze();
	public:
		void add(char c);
		void resetTempCnt();
		bool reachLimit();
		void setMax(int max);
};
