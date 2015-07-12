#include "stringj.h"

int cntByte(unsigned char cChar){
	int iByte;
	if ((cChar >= 0x00) && (cChar <= 0x7f)) {
		iByte = 1;
	} else if ((cChar >= 0xc2) && (cChar <= 0xdf)) {
		iByte = 2;
	} else if ((cChar >= 0xe0) && (cChar <= 0xef)) {
		iByte = 3;
	} else if ((cChar >= 0xf0) && (cChar <= 0xf7)) {
		iByte = 4;
	} else if ((cChar >= 0xf8) && (cChar <= 0xfb)) {
		iByte = 5;
	} else if ((cChar >= 0xfc) && (cChar <= 0xfd)) {
		iByte = 6;
	} else {
		iByte = 0;
	}
	return iByte;
}

using namespace std;
StringJ::StringJ(string str){
	this->str = str;
}
StringJ::StringJ(char c){
	string str(1,c);
	this->str = str;
}

StringJ::StringJ(){}
string StringJ::nthUnicodeLetter(int nth){
	using namespace std;
	nth++;
	int pos = 0;
	int char_size = 0;

	for (int i = 0; i < nth; i++){
		pos += char_size;
		if(pos > this->str.size())
			break;
		char_size = cntByte(str[pos]);
	}
	return str.substr(pos, char_size);
}

int StringJ::size(){
	int len = 0;
	int pos = 0;
	while(pos < this->str.size()){
		pos += cntByte(this->str[pos]);
		len++;
	}

	return len;
}

string StringJ::getStr(){
	return this->str;
}
