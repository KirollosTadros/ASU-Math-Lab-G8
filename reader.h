#ifndef READER_H
#define READER_H

#include <string>
#include <fstream>

class Reader{
public:
	enum mode{file/**file mode read*/, console/**console mode read*/, file_console/**file passed through console mode read*/};
	Reader();
	Reader(std::string filepath, mode m = file);
	~Reader();
	Reader(Reader const& other) = delete;
	Reader& operator=(Reader const& rhs) = delete;
	std::string read();
private:
	std::ifstream inputFile;
	mode readingMode /**reading mode*/;
	std::string readConsole();
	std::string readFile();

};

#endif //READER_H
