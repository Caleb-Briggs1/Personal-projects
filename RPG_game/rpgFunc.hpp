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
	int actualPos = 0;
	std::cout << "sucess\n";
	int posSkip = map.find("☺");
	//std::cout << mapInject.arr;
	int curInject = 0;
	std::cout << map.length() << "\n\n^^\n";
	std::cout << mapInject.arr.substr(150,700);
	//std::cout << mapInject.get(9).pos;


	
	for (int i = 0; map.length() > i;i++) {
		//loop through mapInject here
		
		
		
			//this needs to run a sub string of whatever length the happy face is
			
		//std::cout << i << "\n";
		//std::cout << curInject<< "\n";
		std::cout << mapInject.get(curInject).pos;
		if (mapInject.get(curInject).pos == actualPos+charPosX + (charPosY * (mapSizeX+1) )  ) {
			std::cout << mapInject.get(curInject).value;
			curInject ++;
		}

		
		if (i == posSkip) {
				actualPos -= 2;
			}
		actualPos ++;
		std::cout << map[i]; //re add this when possible, turned off for debugging
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
std::string readFile(std::string file, int addX , int addY, bool specialMode) {
	//add creating color, so using the /r maybe for read or something like that
	std::ifstream inFile;
	inFile.open(file);
	std::string x;
	
	char z;
	std::string res = "";
	bool onSpecial = false;
	bool superSpecial = false;
	int count = addX + (addY*(mapSizeX+1) );
	int distToT = 0;
	std::string numCount = "";
	while (inFile >> z) {
		x = z;
		
			if (x == "\\") {

				onSpecial = true;

			}
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
				
				distToT = 0;
				}
				//green
				if (x == "G") {
				mapInject.push(std::to_string(count),"\033[32m") ;
				onSpecial = false;
				x = '\033';
				
				distToT = 0;
				}
				if (x == "]") {
					x = '\033';
					//"\033[38;5;120m"
					if (specialMode) {
						mapInject.push(std::to_string(count),"\033[38;5;" + numCount + "m") ;
					}
					numCount = "";
					superSpecial = false;
					onSpecial = false;
				}
				if (superSpecial == true ) {
					numCount += x;
					
					x = '\033';

				}
				if (x == "[") {
				
				x = '\033';
				numCount = "";
				superSpecial = true;
				onSpecial = true;
				}
				

				//reset
				if (x == "T") {
				mapInject.push(std::to_string(count),"\033[30m") ;
				onSpecial = false;
				x = '\033';
				

				}
				if (x == "N") {
					count += mapSizeX-distToT ; //its here, the pointer is going at the line below, instead of going back to the start
					x = "\n";
					onSpecial = false;
					distToT = 0;
				}
				
			}
		
		if (!onSpecial) {
			
			if ( !(x == "\033") ) {
				res += x;
				count++;
				distToT++;

			}
		}
		
	}
	return res;
}






#endif