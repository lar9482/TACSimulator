#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <memory>
#include "../Assembler/Assembler.h"
#include "../Assembler/Lexer.h"

using std::string;
using std::queue;

void assembleFile(string const& filePath) {
	string program = readProgramFromFile(filePath);
	
	Lexer lexer;
	queue<Token> tokenQueue = lexer.scanProgram(program);
}

string readProgramFromFile(string const& filePath) {
	std::ifstream file(filePath);

	if (!file) {
		throw UnableToReadFromFileException(filePath);
	}

	std::ostringstream ss;
	ss << file.rdbuf();

	string programContent = ss.str();

	return programContent;
}