#include "reader.h"
#include <fstream>
#include <iostream>
using namespace std;

Reader::Reader() : readingMode(console) {}

Reader::Reader(std::string filepath/**<[in]path of the file*/, mode m/**<[in]mode of read*/) : readingMode(m) {
	//although should not happen, but it's possible
	//that the caller specify readingMode to be console,
	//while using this constructor that takes a filepath
	if(readingMode != console){
		  inputFile.open(filepath.c_str());
		  //todo handle error opening file
	}
}

Reader::~Reader(){
	if(inputFile.is_open()){
		inputFile.close();
	}
}

std::string Reader::readConsole(){
	/**
	 * Read line from cin and return it as a string
	 *<br> if string == "exit", return empty string
	 */
	string s;
	if(inputFile.is_open()){
		getline(std::cin, s);
		cout << s << endl;
		if (s == "exit")
			return "";
		return s;
	}
	return "";
}

std::string Reader::readFile(){
	/**
	 * Read the whole file and return it as a string,
	 *<br> if not reached end of file, otherwise return
	 * empty string
	 */
	string result = "";
	string str = "";
	while(getline(inputFile, str)){
		result +=  str + "\n";
	}
	return result;
}

std::string Reader::read(){
	switch(readingMode){
	case file:
		return readFile();
		break;
	case console:
		return readConsole();
		break;
	case file_console:
		/**
		 * read the whole file first, return it as a string,
		 *<br> then start reading from the console
		 */
		std::string tmp = readFile();
		if(tmp != ""){
			return tmp;
		}else{
			return readConsole();
		}
		break;
	}
}


