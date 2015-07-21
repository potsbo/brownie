#include "keyboard.h"
#include <iostream>
// works only on Unix-like
char getKeyboardInput(){
	system ("/bin/stty raw -echo");
	char inputChar = getchar();
	system ("/bin/stty cooked echo");
	if(inputChar <= 31){
		switch(inputChar){
			case 3:
				exit(1);
		}
	}
	return inputChar;
}
