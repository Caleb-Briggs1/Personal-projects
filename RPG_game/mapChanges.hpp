
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
struct nextCur {
	int next;
	posString cur;
};
class stringArr { //this is very slow, could definitely be sped up
public:
	std::string arr;
	int size;
	void create() {
		arr = "";
		size = 0;
		//TESTING BELOW

	

	}
	std::string createValue(std::string loc, std::string value) {
		std::string tmp = loc + "|" + value + "!";
		
		return tmp;
	}
	void push(std::string loc, std::string value ) {
		arr += createValue(loc,value);
		size++;
		
		//std::cout << arr;
		usleep(5000);
		
	}
	void finish() {
		//sorts it so it is ready to use
		sort();

		
	}
	void loadFile() {
		std::ifstream myReadFile;
		myReadFile.open("mapInject.txt");
		

		char cur;
		std::string Current;
		bool mode = false;
		int count=0;
		while (cur != '~') {

				if (cur != '\033' && !mode) {
					myReadFile >> cur;	
					arr += std::to_string(cur);
					mode = true;
					Current = "";
				}
				else {
					//problem with it not interpeting
					myReadFile >> cur;	
					
					if (cur == '!') {
						Current = "\033" +  std::string(Current.substr(8)) ;

						
						
						arr += "|";
						arr += Current;
						Current = "";
						arr += cur;

						mode = false;
						
					}
					else {
						

						Current += cur;
					}

				}
    			
    		
    			


 		}
 		
		myReadFile.close();
		//return readVal;
	}
	void intoFile() {
		std::ofstream outputFile("mapInject.txt");
		arr += "~";
		outputFile<<arr;

		outputFile.close();

	}
	void sort() {
		for (int j= 0; size > j; j++) {
			int max = 0;
			int index = 0;
			int locGet = 0;
			for (int i = 0; size-j > i; i++) {
				nextCur b = getFast(locGet);
				locGet = b.next;
				if (b.cur.pos > max) {
					max = b.cur.pos;

					index = i;
				}
			}
			//this part is wrong
			posString holdTmp = get(index);
			std::string hold = createValue(std::to_string(holdTmp.pos),holdTmp.value);
			
			posString getJTmp = get((size-1)-j);
			std::string getJ = createValue(std::to_string(getJTmp.pos),getJTmp.value);
			
			std::cout << "J: " << getJ + "\n" ;
			//std::cout << "H: " << hold + "\n"  ;
			//it appreas to be working correctlu
			
			set(index,getJ);
			set((size-1)-j,hold);
			
			
		}
	}
	void set(int id,std::string newValue) {
		int start = stoi(readUntil('!',arr,id-1,true,true));
		int end = stoi(readUntil('!',arr,id,true,true));
		arr =  arr.substr(0,start+1) + newValue + arr.substr(end+1);
		
	}
	nextCur getFast(int start) { //start needs to be the last item
		
		//int end = stoi((readUntil('!',arr,1,true,true,start))); //gets pos of end
		std::string create = "";

		while(arr[start] != '!') {
			create+= arr[start++];

		}
	
		
		std::string pos = readUntil('|',create,0);
		pos.erase(pos.length()-1);
		std::string value = readAfter('|',create);
		posString finalRes = {stoi(pos),value};
		
		nextCur finalRes2 = {start+1,finalRes};
		//gets quikcly the start and the end
		return finalRes2;



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
	std::string readUntil(char char_,std::string string, int times, bool destr = true, bool returnCount = false, int start = 0) {
		if (returnCount && times < 0) {
			return "-1";
		}
		std::string res = "";
		int count = 0;
		for (int i = start; string.length() > i; i++) {
			res += string[i];
			if (string[i] == char_) {
				if (times == count++ ) {
					if (returnCount) {
						return std::to_string(i);
					}
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


