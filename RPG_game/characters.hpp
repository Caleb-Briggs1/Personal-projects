#ifndef characters_hpp

#define characters_hpp
std::string readFile(std::string look,int x, int y, bool specialMode = true);
std::string putObj(std::string map,std::string look, int x, int y);
class staticChar 
{

private:
	//takes string and loads that file and parses it with the special rules
	bool touch(std::string parsedLook) {
		int pos = x + (y*(mapSizeX+1) );
		int yCur = y;
		int playerPos = charPosX + (charPosY*(mapSizeX) );
		for (int i = 0; parsedLook.length() > i; i++) {
			if (parsedLook[i] != '\n') {

				if (playerPos == pos ) {
					return true;
				}
				
				pos++;
			}
			else {
			pos = x + (++yCur*mapSizeX+1);
			}


		}
		
		return false;
	}
	std::string parse(std::string look) {
		return readFile(look,x+mapSizeX/2,y + mapSizeY/2 );
		//in case any special rules are implemented, deal with them here
	}

public:
	int x;
	int y;
	std::string look;
	void _init_(int x_, int y_,std::string inlook) {
		x = x_ ;
		y = y_ ; 
		look = parse(inlook);
		

	}
	std::string display(std::string map) {
		if(touch(look)) {
			//what things to do if touching
		}
		return putObj(map, look,x,y);
	}


};

#endif