#include "reader.h"

Reader::Reader() : readingMode(console) {}

Reader::Reader(std::string filepath, mode m) : readingMode(m) {
	//although should not happen, but it's possible
	//that the caller specify readingMode to be console,
	//while using this constructor that takes a filepath
	if(readingMode != console){
		inputFile.open(filepath);
	}
}

Reader::~Reader(){
	if(inputFile.is_open()){
		inputFile.close();
	}
}

std::string Reader::readConsole(){
	/*
	 * Read line from cin and return it as a string
	 * if string == "exit", return empty string
	 */
	return ""; //todo remove this and implement the function
}

std::string Reader::readFile(){
	/*
	 * Read the whole file and return it as a string,
	 * if not reached end of file
	 */

	//note inputFile is already defined and opened
	return ""; //todo remove this and implement the function
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
		/*
		 * read the whole file first, return it as a string,
		 * then start reading from the console
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
