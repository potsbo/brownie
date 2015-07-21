#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include "pattern.h"
extern bool debugFlag;

/* collection of pattern that can put a kana */
class PatternsForAKana {
	private:
		std::string objectiveKana;
		std::vector<Pattern> patterns;	
		std::vector<std::string> strokes;
	public:
		PatternsForAKana(Pattern newPat);
		bool isAbleToReturn(std::string letter);
		bool canHold(Pattern pat);
		void add(Pattern newPat);
		std::vector<std::string> getStrokes();
		std::vector<Pattern> getPatterns();
		void print();
};


class CandidatePattern {
	private:
		std::vector<Pattern> pats;
		Pattern patternToProcess;
	public:
		bool hasProcessablePatternOf(std::string unprocessedInputs);
		CandidatePattern();
		CandidatePattern(PatternsForAKana patterns);
		Pattern getSelected();
		void reset(std::vector<Pattern> pats);
		void onlyCompatibleWithNextKanas(StringJ objective, int index, std::vector<Pattern> allPatterns);
		void onlyCompatibleWithCurrentInput(std::string currentInput);
		std::vector<char> getNthStrokes(int i);
		/* this is safe to use after you call onlyCompatibleWithCurrentInput and onlyCompatibleWithNextLetter */
		std::set<char> getValidInput(std::string unprocessedInputs);
};

class RomajiTable {
	private:
		std::vector<PatternsForAKana> analysedPatterns;
		std::vector<Pattern> allPatterns;

	public:
		void set(std::string sourceFile);
		void printAnalysedPatterns();
		PatternsForAKana firstCandidate(std::string kana);
		std::vector<Pattern> getAllPattern();
		CandidatePattern getCandidate(std::string letter);
};

