#pragma once

#include <algorithm> 
#include <fstream>
#include <set>
#include "set.h"
#include "pattern.h"
#include "romajitable.h"
#include "split.h"
#include "stringj.h"
#include "keyboard.h"

extern bool debugFlag;



class Game {
	private:
		int loop = 3;
		RomajiTable romajiTable;
		CandidatePattern candidatePat;
		vector<string> objectiveList;
		vector<Pattern> potentialPattern;
		bool seqFlag = false; // true -> set objective with normal order, false -> random order

		char waitForValidInput(set<char> validInputList = set<char>());
		Pattern getProcessablePattern(string unprocessedInputs);
		int calcuPotentialPatternNum(string unprocessedInputs, int unuseInput = -1);
		set<char> makeValidInputList(StringJ objective, int index,string unprocessedInputs);
		void typeStringChallenge(StringJ objective);
		void process(string *unprocessedInputs, int *index, int unuseInputNum = 0);
	public:
		Game(string tableFile = "googleNihongoRomajiTable", string objectiveFile = "default");
		void run();
		void addObjective(string newObjective);
		void setSeq(bool flag);
};
