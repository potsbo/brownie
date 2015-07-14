#include "keyboard.h"
#include <iostream>
// works only on Unix-like
char getKeyboardInput(){
	system ("/bin/stty raw");
	char inputChar = getchar();
	system ("/bin/stty cooked");
	return inputChar;
}
