#include <string>
#include "abcdvorak.h"

ABCDvorak::ABCDvorak(string saveData ){};
void ABCDvorak::run(){
	for(int i = currentPhase; i < endPahese; i++ ){
		string index = to_string(i);
		if(index.size() == 1){
			index = '0' + index;
		}
		string objectiveFile = "abcd" + index;

		Game abcdGame(dvorakTable,objectiveFile);
		abcdGame.setSeq(true);
		abcdGame.run();
	}
}

