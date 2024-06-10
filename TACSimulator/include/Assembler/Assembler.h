#pragma once

#include <string>
#include <exception>

void assembleFile(std::string const& filePath);
std::string readProgramFromFile(std::string const& filePath);

class UnableToReadFromFileException : public std::exception
{
private:
	std::string filePath;
public:
	UnableToReadFromFileException(std::string const& filePath) :
		filePath(filePath) {}

	virtual const char* what() const throw() {
		return filePath.c_str();
	}
};