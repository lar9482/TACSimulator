#pragma once

class Lexer {
private:
	void matchIdentifer();
	void matchWhitespace();
	void matchOneSymbol();
	void matchInteger();
};