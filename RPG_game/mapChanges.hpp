
#include <string>
#ifndef  mapChanges_hpp
#define mapChanges_hpp
//make structure for string array
//alows you to inject color and other such properties
//looks like this

//always in form like this

//"a|b!c|d!f|g!"
struct posString {
	int pos;
	std::string value;
};
class stringArr { //this is very slow, could definitely be sped up
public:
	std::string arr;
	int size;
	void create() {
		arr = "";
		size = 0;
	}
	void push(std::string loc, std::string value ) {
		std::string tmp = loc + "|" + value;
		arr += tmp;
		arr += "!";
		size++;
		std::cout << arr; //shows loc pos CAN REMOVE
	}
	posString get(int id) {
		std::string res = (readUntil('!',arr,id));
		std::string pos = readUntil('|',res,0);
		pos.erase(pos.length()-1);
		std::string value = readAfter('|',res);
		value.erase(value.length()-1);
		posString finalRes = {stoi(pos),value};
		return finalRes;
		
	}
	std::string readAfter(char char_,std::string arr) {
		bool startRead = false;
		std::string res = "";
		for (int i = 0; arr.length() > i; i++) {
			if(startRead) {
				res += arr[i];
			}
			if (arr[i] == char_) {
				startRead = true;
			}

		}
		return res;
	}
	std::string readUntil(char char_,std::string string, int times, bool destr = true) {
		std::string res = "";
		int count = 0;
		for (int i = 0; string.length() > i; i++) {
			res += string[i];
			if (string[i] == char_) {
				if (times == count++ ) {
					return res;
				}
				else {
					if(destr) {
						res = "";
					}
				}
			}
			
		}
		return res;
	}

};




#endif


