#include "ascii.h"
std::string asciiTable(int startPoint, int endPoint){
	std::string asciies;
	for(int i = startPoint; i < endPoint; i++){
		asciies += i;
		asciies += "\t";
		asciies += i;
	}
	return asciies;
}
