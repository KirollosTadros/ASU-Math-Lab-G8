#include "variable.h"
#include "matrix.h"
#include "number.h"
#include "parser.h"
#include "reader.h"
#include <iostream>

#include "test.h" //remove on delivery

using namespace std;

int main(int argc, char* argv[]){

	/*
	 * Process the program arguments
	 */

	string filename = "";
	//interactive mode:
	//user can input commands from console, after
	//the whole input file is parsed, or without
	//parsing an input file first, if no filename
	//is given
	bool interactiveMode = false;
	if(argc < 2 || argc > 3){
		cout << "Wrong number of arguments to program" << endl;
		cout << "Usage: " << argv[0] << " <filename> [-i]" << endl;
		return -1;
	}else{
		for(int i=1; i<argc; ++i){
			if((string) argv[i] == "-i"){
				interactiveMode = true;
			}else{
				filename = argv[i];
			}
		}
	}

	/*
	 * 	Create Reader object according to
	 * 	program arguments
	 */

	Reader* reader;
	if(filename.length() == 0){
		reader = new Reader();
	}else if(interactiveMode){
		reader = new Reader(filename, Reader::file_console);
	}else{
		reader = new Reader(filename, Reader::file);
	}

	/*
	 * Read and parse
	 */
	Parser parser;
	string inputString;
	inputString = reader->read();
	while(inputString != ""){
		parser.parse(inputString);
		inputString = reader->read();
	}

	delete reader;
    return 0;
}
