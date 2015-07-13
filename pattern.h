#pragma once

#include "split.h"
#include "stringj.h"
extern bool debugFlag;

class Pattern {
	private:
		std::string stroke;
		StringJ kana;
		std::string output;
	public:
		Pattern();
		Pattern(char i, StringJ r, std::string o = "");
		Pattern(char i, char r, std::string o = "");
		Pattern(std::string str);
		bool isValid();
		bool hasSameStrokeWith(Pattern pat);
		bool isCompatibleWithNextInput(std::vector<char> requiredAlphabet);
		bool isCompatibleWithCurrentInput(std::string currentInput);
		char nthStroke(int i);
		std::string getStroke();
		std::vector<std::string> getObjective(int i = -1);
		std::string getOutput();
		void print(std::string splitter = "\n");
};


