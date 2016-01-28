#include <iostream>
#include "cmdline.h"
#include "game.h"
using namespace std;

const std::string VERSION = "0.01";
bool debugFlag = false;

int main(int argc, char *argv[]) {
	cmdline::parser a;
	a.add("debug", 'd', "debagFlag = true に設定");
	a.add<string>("table", 't', "ローマ字テーブルファイル名", false, "googleNihongoRomajiTable");
	a.add<string>("objective", 'o', "文字列ファイル指定", false, "default");
	a.add<int>("typo", '\0', "ミスタイプ数上限設定", false, -1);
	a.add<int>("phase", '\0', "スタート時のレッスン番号指定", false, 1);
	a.add("abcd", '\0', "A Basic Course in Dvorak");
	a.add("sequence", 's', "文字列を順に表示(デフォルトはランダム)");
	a.parse_check(argc, argv);

	debugFlag = a.exist("debug");

	srand(time(NULL));
	cout << "Brownie ver. " << VERSION << endl;

	string sourceFile = a.get<string>("table");
	string objectiveFile = a.get<string>("objective");

	if(a.exist("abcd")){
		Game abcdGame("ascii","ABasicCourseinDvorak");
		// basic setting
		abcdGame.setPhase(a.get<int>("phase"));
		abcdGame.setSeq(true);

		// typo setting 
		int typoMax = 3;
		if(a.get<int>("typo") != -1) typoMax = a.get<int>("typo");
		abcdGame.setTypoMax(typoMax);

		abcdGame.run();
	}else{
		Game newGame(sourceFile,objectiveFile);
		newGame.setSeq(a.exist("sequence"));
		newGame.setTypoMax(a.get<int>("typo"));
		newGame.run();
	}

	cout << endl;
	return 0;
}
