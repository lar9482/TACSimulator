#include <string>
#include <fstream>
#include <sstream>

#include "../Assembler/Assembler.h"
#include "../Assembler/Lexer.h"

using std::string;

void assembleFile(string const& filePath) {
	string program = readProgramFromFile(filePath);
	
	Lexer lexer;
	lexer.scanProgram(program);
}

string readProgramFromFile(string const& filePath) {
	std::ifstream file(filePath);

	if (!file) {
		UnableToReadFromFileException exception(filePath);
		throw exception;
	}

	std::ostringstream ss;
	ss << file.rdbuf();

	string programContent = ss.str();

	return programContent;
}