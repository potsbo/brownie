#pragma once
#include <string>
#include <iostream>
class StringJ : public std::string{
	private:
		std::string str = "";
	public:
		StringJ(std::string str);
		StringJ(char);
		StringJ();
		std::string nthUnicodeLetter(int nth);
		/* int size(); */
		int size();
		std::string getStr();
};
