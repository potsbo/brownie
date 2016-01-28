#include <string>
#include "abcdvorak.h"
#include "game.h"
#include "cmdline.h"
// test
ABCDvorak::ABCDvorak(){
	/* TODO: load save data */
	table.set(TABLE_FILE_PREFIX+dvorakTableName);
};

int ABCDvorak::run(){
	for(int i = currentPhase; i < endPahese; i++ ){
		string index = to_string(i);
		if(index.size() == 1){
			index = '0' + index;
		}

		const string prefix = "ABasicCourseinDvorak/";
		string objectiveFile = prefix + "abcd" + index;

		Game abcdGame(table,objectiveFile);
		abcdGame.setSeq(true);
		abcdGame.setTypoMax(3); // TODO: make this modifiable
		int result = abcdGame.run();
		if(result == 3){
			cout << endl << "save?[Yn]:";
			string input;
			cin >> input;
			if(input != "n" && input != "N"){
				return abcdGame.save();
			}else{
				cout << "discard data" << endl;
			}
			return 0;
		}
	}
	return 0;
}

void ABCDvorak::setTable(string table){
	this->dvorakTableName = table;
}

void ABCDvorak::setPhase(int phase){
	this->currentPhase = phase;
}
