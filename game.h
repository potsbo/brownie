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
		string gameTitle;
		bool seqFlag = false; // true -> set objective with normal order, false -> random order

		/* about typeStringChallenge */
		void typeStringChallenge(StringJ objective);
		set<char> makeValidInputList(StringJ objective, int index,string unprocessedInputs);
		char waitForValidInput(set<char> validInputList = set<char>());
		int calcuPotentialPatternNum(string unprocessedInputs, int unuseInput = -1);
		void process(string *unprocessedInputs, int *index, int unuseInputNum = 0);
		Pattern getProcessablePattern(string unprocessedInputs);
	public:
		Game(string tableFile = "googleNihongoRomajiTable", string objectiveFile = "default");
		void addObjective(string newObjective);
		void setSeq(bool flag);
		void setRound(int num);
		void run();
};
