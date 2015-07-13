#pragma once

#include <string>
#include "game.h"

class ABCDvorak{
	private:
		int currentPhase = 1;
		int endPahese = 29;
		string dvorakTable = "ascii";
	public:
		ABCDvorak(string saveData = "");
		void run();
};
