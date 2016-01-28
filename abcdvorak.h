#pragma once

#include <string>
#include "game.h"

class ABCDvorak{
	private:
		int currentPhase = 1;
		int endPahese = 29;
		string dvorakTableName = "ascii";
		RomajiTable table;
	public:
		ABCDvorak();
		void setTable(string table);
		void setPhase(int phase);
		int run();
};
