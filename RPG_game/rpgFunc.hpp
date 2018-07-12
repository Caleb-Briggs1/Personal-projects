#include <iostream>

#include <termios.h>
#ifndef rpgFunc_hpp
#define rpgFunc_hpp
#include "rpg.hpp"
#include "characters.hpp"
#include "mapChanges.hpp"

//..
std::string map;
stringArr mapInject;
std::string putMap() {
	std::string s = "";
	for (int col = 0; mapSizeY > col; col++) {
		for (int row = 0; mapSizeX > row; row++) {
			s = s +  ".";
		}
		s = s+"\n";
	}
	return s;
}
void drawMap(std::string map) {
	for (int i = 0; map.length() > i;i++) {
		//loop through mapInject here
		for (int j = 0; mapInject.size > j; j++) {
			if (mapInject.get(j).pos == i+charPosX + (charPosY * (mapSizeX+1) )  ) {
				std::cout << mapInject.get(j).value;
			}
		}
		std::cout << map[i];
	}
}
std::string putObj(std::string map, std::string obj, int locX, int locY) {
	int curY = locY + mapSizeY/2; //add scroll properties
	int curX = locX + mapSizeX/2;
	for (int i = 0; obj.length() > i; i++) {

		if (obj[i] == '\n'){
			
			curX = locX+ mapSizeX/2;
			curY += 1;
			
		}
		else {
			if ( (curX-charPosX) < mapSizeX && curY-charPosY < mapSizeY && curX-charPosX >= 0 && curY-charPosY >= 0) {
				map[ (curX-charPosX) + ( (curY-charPosY)*(mapSizeX+1) ) ] = obj[i];
				
			}
			curX += 1;
		}
	}

	return map;
}
char getInput() {
	//@Author:  Luc Lieber
	struct termios t;
	tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
    t.c_lflag &= ~ICANON; //Manipulate the flag bits to do what you want it to do
    tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
    //end Author
	char b;
	b = std::getchar();
	return b;
}
void move() {
	char mov = getInput();
	if (mov == 'w') {
		charPosY -= 1;
	}
	else if(mov == 's') {
		charPosY += 1;
	}
	else if(mov == 'd') {
		charPosX += 1;
	}
	else if(mov == 'a') {
		charPosX -= 1;
	}

}
std::string putChar(std::string map) {

	//map[ (mapSizeX+1) * int(mapSizeY/2) + ( int((mapSizeX)/2) ) ] = 'O';
	//this might need to change, ovverriding cuasing some weird results
	map.insert((mapSizeX+1) * int(mapSizeY/2) + ( int((mapSizeX)/2) ),"☺");
	map.erase((mapSizeX+1) * int(mapSizeY/2) + ( int((mapSizeX)/2) ) +3,1);
	//map[ (mapSizeX+1) * int(mapSizeY/2) + ( int((mapSizeX)/2) ) +1 ] = '-';
	return map;
}
std::string readFile(std::string file) {
	//add creating color, so using the /r maybe for read or something like that
	std::ifstream inFile;
	inFile.open(file);
	std::string x;
	char z;
	std::string res = "";
	bool onSpecial = false;
	int count = 0;
	while (inFile >> z) {
		x = z;
		//std::cout << "running";
		if (x == "\\") {

			onSpecial = true;

		}
		//problem with all these large string
		if (onSpecial) {
			if (x == "S") {
			x = " ";
			onSpecial = false;
			}
			//red
			if (x == "R") {
			mapInject.push(std::to_string(count),"\033[31m") ;
			onSpecial = false;
			x = '\033';
			std::cout << "pushed";
			}
			//green
			if (x == "G") {
			mapInject.push(std::to_string(count),"\033[32m") ;
			onSpecial = false;
			x = '\033';
			std::cout << "pushed";
			}
			//reset
			if (x == "T") {
			mapInject.push(std::to_string(count),"\033[30m") ;
			onSpecial = false;
			x = '\033';
			std::cout << "pushed";
			}
			if (x == "N") {
				x = "\n";
				onSpecial = false;
			}
			
		}
		if (!onSpecial) {
			
			if ( !(x == "\033") ) {
				res += x;
				count++;
			}
		}
		
	}
	return res;
}





#endif