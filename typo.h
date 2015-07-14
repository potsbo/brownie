#pragma once
#include <set>
#include <vector>
class Typo {
	private:
		int cnt = 0;
		char c;
	public:
		Typo(char c);
		void increment();
};

class TypoSet  {
	private:
		std::set<Typo> typoSet;
		std::vector<char> typoList;
		int tempCnt = 0;
		int mistakeMax = 0;
		void analyze();
	public:
		void add(char c);
		void resetTempCnt();
		bool reachLimit();
		void setMax(int max);
};
