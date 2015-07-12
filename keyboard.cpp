#include <iostream>
// works only on Unix-like
char getKeyboardInput(){
	system ("/bin/stty raw");
	char inputChar = getchar();
	system ("/bin/stty cooked");
	if(inputChar <= 31){
		switch(inputChar){
			case 3:
				exit(1);
		}
	}
	return inputChar;
}
