#include <iostream>
#include <unistd.h>
#include "rpgFunc.hpp"
//using namespace std;


//PROBSBLy FASTER FORM OF GET, RIGHT NOW IT HAS TO LOOP FROM THE STRAT< COULD SPECIFIY START CORDINATEs
//Order inject to make it run faster !!!
//ALSO, DONT REPRINT IF THE SAME VALUE AS LAST TIME
//Needs speed improvements
//One is that it should only print one new line, instead of reprinting the entire map
//also, preload map

//ERROR IN DRAW MAP

#include <stdlib.h> //for system
//make this into something nice, like walking past memories
//reload
/*
	ALSO, SEE HERE FOR COLOR: http://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html
	Use this for the pattern:https://jonasjacek.github.io/colors/
	coudl use this site: https://manytools.org/hacker-tools/convert-images-to-ascii-art/go
	and then parse the data
*/
//NOT WORKING IF SMILEY FACE GOES PAST THE DRAW SYMBOLS
/*
 ...................
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
	mapInject.create();
	//slime._init_(-12,2,"slime.txt");
	std::string res = ""; 


	res = readFile("map.txt",0,0,true); //were going to create the file
	

	mapInject.loadFile();
	
	
	//mapInject.finish(); //sort it, were now done
	//mapInject.intoFile();
	/*
	while(true) {
		 
		
		run(res);
		
		
	}
	*/
	
	
	
	
	
}


void run(std::string MAP) {
	std::string map = putMap();
	
	update();
	 	
	map = putObj(map, MAP,0,0);
	
	//map = slime.display(map);
	map = putChar(map);
	//slime.display(map);

	drawMap(map);


	move();
	reset();
	
}



