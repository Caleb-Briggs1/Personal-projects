#include <iostream>
#include <unistd.h>
#include "rpgFunc.hpp"
//using namespace std;

#include <stdlib.h> //for system
//reload
/*
 .
 ...................................................................................
 ........................................................................................
*/


//create another variable for map that specifies where to add special formatting
//ie 5-10 could be green
//12-30 blue
//etc
//move character into its own file, which is included inside of rpgFunc, 
void run(std::string MAP);


#define update() printf("\033[H") //moves cursor
#define reset() printf("\033[2J")


staticChar slime;
int main() 
{
	slime._init_(0,-5,"slime.txt");
	std::string res = "";
	mapInject.create();
	res = readFile("map.txt");
	std::cout << mapInject.arr;

	/*
	while(true) {
		
		//run(res);
		
		
	}
	*/
	
	
	
}


void run(std::string MAP) {
	std::string map = putMap();
	update();
	 	
	map = putObj(map, MAP,-mapSizeX/2,-mapSizeY/2);
	map = putObj(map, "******\n*    *\n******",-30,-30);
	map = slime.display(map);
	map = putChar(map);
	slime.display(map);
	drawMap(map);


	move();
	reset();
		
}




//Instead of actually printing when using a function, reutrn what is displays on line 0-x
//each function should do this, so that then they can all be printed together