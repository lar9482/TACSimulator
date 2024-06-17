#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <memory>
#include "../Assembler/Assembler.h"
#include "../Assembler/Lexer.h"
#include "../Assembler/Parser.h"


using std::string;
using std::queue;
using std::unique_ptr;

void assembleFile(string const& filePath) {
	string program = readProgramFromFile(filePath);
	
	Lexer lexer;
	queue<Token> tokenQueue = lexer.scanProgram(program);
	Parser parser(tokenQueue);
	queue<unique_ptr<Inst>> allInsts = parser.parseProgram();

	while (allInsts.size() > 0) {
		auto inst = allInsts.front().get();
		inst->assembleInst();
		allInsts.pop();
	}
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