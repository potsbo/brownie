#include <string>
#include "abcdvorak.h"
#include "game.h"

ABCDvorak::ABCDvorak(string saveData){
/* TODO: load save data */
	table.set(TABLE_FILE_PREFIX+dvorakTableName);
};
void ABCDvorak::run(){
	for(int i = currentPhase; i < endPahese; i++ ){
		string index = to_string(i);
		if(index.size() == 1){
			index = '0' + index;
		}

		const string prefix = "ABasicCourseinDvorak/";
		string objectiveFile = prefix + "abcd" + index;

		Game abcdGame(table,objectiveFile);
		abcdGame.setSeq(true);
		abcdGame.run();
	}
}

void ABCDvorak::setTable(string table){
	this->dvorakTableName = table;
}
