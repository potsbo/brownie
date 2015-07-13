#include <string>
#include "game.h"

class ABCDvorak{
	private:
		int currentPhase = 1;
		int endPahese = 29;
		string dvorakTable = "ascii";
	public:
		ABCDvorak(string saveData = ""){}

		void run(){
			for(int i = currentPhase; i < endPahese; i++ ){
				string index = to_string(i);
				if(index.size() == 1){
					index = '0' + index;
				}
				string objectiveFile = "abcd" + index;

				Game abcdGame(dvorakTable,objectiveFile);
				abcdGame.run();
			}
		}

};
