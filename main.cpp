#include <iostream>
#include "cmdline.h"
#include "game.h"
using namespace std;

const std::string VERSION = "0.01";
bool debugFlag = false;

int main(int argc, char *argv[]) {
	cmdline::parser a;
	a.add("debug", 'd', "debagFlag = true に設定します。");
	a.add<string>("table", 't', "ローマ字テーブルファイル名", false, "./googleNihongoRomajiTable");
	a.add("sequence", 's', "文字列を順に表示(デフォルトはランダム)");
	a.parse_check(argc, argv);

	debugFlag = a.exist("debug");

	srand(time(NULL));
	cout << "Brownie ver. " << VERSION << endl;

	/* TODO set with getopt */
	string sourceFile = a.get<string>("table");

	Game newGame(sourceFile);
	newGame.setSeq(a.exist("sequence"));
	newGame.run();
	cout << "You have done!";

	cout << endl;
	return 0;
}
