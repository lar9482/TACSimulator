#include "../Assembler/Lexer.h"
#include <string>
#include <utility>
#include <stdexcept>
#include <iostream>
#include <queue>

using std::string;
using std::pair;
using std::queue;

queue<Token> Lexer::scanProgram(string& program) {
    queue<Token> allTokens;
    
    while (program.length() > 0) {
        pair<MatchType, string> longestMatchWithType = findLongestMatch(program);
        MatchType type = longestMatchWithType.first;
        string longestMatch = longestMatchWithType.second;

        switch (type) {
            case MatchType::Identifier: 
                allTokens.push(resolveIdentifier(longestMatch)); break;
            case MatchType::OneSymbol:
                allTokens.push(resolveOneSymbol(longestMatch)); break;
            case MatchType::Integer:
                allTokens.push(Token(longestMatch, TokenType::integer, lineCounter, columnCounter)); break;
            case MatchType::Whitespace:
                if (longestMatch == "\n") {
                    columnCounter = 1;
                    lineCounter++;
                }

                break;
            default:
                throw std::runtime_error("Unable to match type");
                break;
        }
        
        columnCounter += static_cast<int>(longestMatch.size());
        program.erase(0, longestMatch.size());
    }

    return allTokens;
}

pair<MatchType, string> Lexer::findLongestMatch(string const& program) const {
    MatchType longestMatchType = MatchType::Identifier;
    string longestMatch = matchIdentifer(program);
    size_t longestMatchLength = longestMatch.size();

    string possibleOneSymbolMatch = matchOneSymbol(program);
    string possibleIntegerMatch = matchInteger(program);
    string possibleWhitespaceMatch = matchWhitespace(program);

    if (possibleOneSymbolMatch.size() > longestMatchLength) {
        longestMatchType = MatchType::OneSymbol;
        longestMatchLength = possibleOneSymbolMatch.size();
        longestMatch = possibleOneSymbolMatch;
    }

    if (possibleIntegerMatch.size() > longestMatchLength) {
        longestMatchType = MatchType::Integer;
        longestMatchLength = possibleIntegerMatch.size();
        longestMatch = possibleIntegerMatch;
    }

    if (possibleWhitespaceMatch.size() > longestMatchLength) {
        longestMatchType = MatchType::Whitespace;
        longestMatchLength = possibleWhitespaceMatch.size();
        longestMatch = possibleWhitespaceMatch;
    }

    if (longestMatchLength == 0) {
        throw std::runtime_error("Unable to find a longest match");
    }

    pair<MatchType, string> longestMatchWithType;
    longestMatchWithType.first = longestMatchType;
    longestMatchWithType.second = longestMatch;

    return longestMatchWithType;
}

/*
 * Identifiers will be matched by "[a-zA-Z]_1[a-zA-Z0-9]*"
 */
string Lexer::matchIdentifer(string const& program) const {
    string identifier = "";
    int i = 0;
    if ((program[i] >= 'a' && program[i] <= 'z') || 
        (program[i] >= 'A' && program[i] <= 'Z')) {
        identifier += program[i];
        i++;
    }
    else {
        return identifier;
    }

    while ((program[i] >= 'a' && program[i] <= 'z') || 
        (program[i] >= 'A' && program[i] <= 'Z') ||
        (program[i] >= '0' && program[i] <= '9')) {
        identifier += program[i];
        i++;
    }

    return identifier;
}

/*
 * Whitespace will be matched by "\r|\n|\t|\s"
 */
string Lexer::matchWhitespace(string const& program) const {
    string whitespace = "";

    if (program[0] == '\r' || program[0] == '\n' ||
        program[0] == '\t' || program[0] == ' ') {
        whitespace += program[0];
    }

    return whitespace;
}

/*
 * One symbols will be matched by ",|:|[|]"
 */
string Lexer::matchOneSymbol(string const& program) const {
    string oneSymbol = "";
    if (program[0] == ',' || program[0] == ':' ||
        program[0] == '[' || program[0] == ']') {
        oneSymbol += program[0];
    }

    return oneSymbol;
}

/*
 * Integers will be matched by "-?[0-9]"
 */
string Lexer::matchInteger(string const& program) const {
    string integer = "";
    int i = 0;
    if (program[i] == '-') {
        integer += program[i];
        i++;
    }

    while (program[i] >= '0' && program[i] <= '9') {
        integer += program[i];
        i++;
    }
    return integer;
}

/*
 * Dang this is ugly. But, C++ lacks pattern matching for strings, so yeah. 
 */
Token Lexer::resolveIdentifier(string const& identifier) const {
    if (identifier == "r0") return Token(identifier, TokenType::r0_Reg, lineCounter, columnCounter);
    else if (identifier == "r1") return Token(identifier, TokenType::r1_Reg, lineCounter, columnCounter);
    else if (identifier == "r2") return Token(identifier, TokenType::r2_Reg, lineCounter, columnCounter);
    else if (identifier == "r3") return Token(identifier, TokenType::r3_Reg, lineCounter, columnCounter);
    else if (identifier == "r4") return Token(identifier, TokenType::r4_Reg, lineCounter, columnCounter);
    else if (identifier == "r5") return Token(identifier, TokenType::r5_Reg, lineCounter, columnCounter);
    else if (identifier == "r6") return Token(identifier, TokenType::r6_Reg, lineCounter, columnCounter);
    else if (identifier == "r7") return Token(identifier, TokenType::r7_Reg, lineCounter, columnCounter);
    else if (identifier == "r8") return Token(identifier, TokenType::r8_Reg, lineCounter, columnCounter);
    else if (identifier == "r9") return Token(identifier, TokenType::r9_Reg, lineCounter, columnCounter);
    else if (identifier == "r10") return Token(identifier, TokenType::r10_Reg, lineCounter, columnCounter);
    else if (identifier == "r11") return Token(identifier, TokenType::r11_Reg, lineCounter, columnCounter);
    else if (identifier == "r12") return Token(identifier, TokenType::r12_Reg, lineCounter, columnCounter);
    else if (identifier == "r13") return Token(identifier, TokenType::r13_Reg, lineCounter, columnCounter);
    else if (identifier == "r14") return Token(identifier, TokenType::r14_Reg, lineCounter, columnCounter);
    else if (identifier == "r15") return Token(identifier, TokenType::r15_Reg, lineCounter, columnCounter);
    else if (identifier == "r16") return Token(identifier, TokenType::r16_Reg, lineCounter, columnCounter);
    else if (identifier == "r17") return Token(identifier, TokenType::r17_Reg, lineCounter, columnCounter);
    else if (identifier == "r18") return Token(identifier, TokenType::r18_Reg, lineCounter, columnCounter);
    else if (identifier == "r19") return Token(identifier, TokenType::r19_Reg, lineCounter, columnCounter);
    else if (identifier == "r20") return Token(identifier, TokenType::r20_Reg, lineCounter, columnCounter);
    else if (identifier == "r21") return Token(identifier, TokenType::r21_Reg, lineCounter, columnCounter);
    else if (identifier == "r22") return Token(identifier, TokenType::r22_Reg, lineCounter, columnCounter);
    else if (identifier == "r23") return Token(identifier, TokenType::r23_Reg, lineCounter, columnCounter);
    else if (identifier == "r24") return Token(identifier, TokenType::r24_Reg, lineCounter, columnCounter);
    else if (identifier == "r25") return Token(identifier, TokenType::r25_Reg, lineCounter, columnCounter);
    else if (identifier == "rSP") return Token(identifier, TokenType::rSP_Reg, lineCounter, columnCounter);
    else if (identifier == "rFP") return Token(identifier, TokenType::rFP_Reg, lineCounter, columnCounter);
    else if (identifier == "rRET") return Token(identifier, TokenType::rRET_Reg, lineCounter, columnCounter);
    else if (identifier == "rHI") return Token(identifier, TokenType::rHI_Reg, lineCounter, columnCounter);
    else if (identifier == "rLO") return Token(identifier, TokenType::rLO_Reg, lineCounter, columnCounter);
    else if (identifier == "rIP") return Token(identifier, TokenType::rIP_Reg, lineCounter, columnCounter);
    else if (identifier == "mov") return Token(identifier, TokenType::mov_Inst, lineCounter, columnCounter);
    else if (identifier == "add") return Token(identifier, TokenType::add_Inst, lineCounter, columnCounter);
    else if (identifier == "sub") return Token(identifier, TokenType::sub_Inst, lineCounter, columnCounter);
    else if (identifier == "mult") return Token(identifier, TokenType::mult_Inst, lineCounter, columnCounter);
    else if (identifier == "div") return Token(identifier, TokenType::div_Inst, lineCounter, columnCounter);
    else if (identifier == "and") return Token(identifier, TokenType::and_Inst, lineCounter, columnCounter);
    else if (identifier == "or") return Token(identifier, TokenType::or_Inst, lineCounter, columnCounter);
    else if (identifier == "xor") return Token(identifier, TokenType::xor_Inst, lineCounter, columnCounter);
    else if (identifier == "not") return Token(identifier, TokenType::not_Inst, lineCounter, columnCounter);
    else if (identifier == "nor") return Token(identifier, TokenType::nor_Inst, lineCounter, columnCounter);
    else if (identifier == "sllv") return Token(identifier, TokenType::sllv_Inst, lineCounter, columnCounter);
    else if (identifier == "srav") return Token(identifier, TokenType::srav_Inst, lineCounter, columnCounter);
    else if (identifier == "movI") return Token(identifier, TokenType::movI_Inst, lineCounter, columnCounter);
    else if (identifier == "addI") return Token(identifier, TokenType::addI_Inst, lineCounter, columnCounter);
    else if (identifier == "subI") return Token(identifier, TokenType::subI_Inst, lineCounter, columnCounter);
    else if (identifier == "multI") return Token(identifier, TokenType::multI_Inst, lineCounter, columnCounter);
    else if (identifier == "divI") return Token(identifier, TokenType::divI_Inst, lineCounter, columnCounter);
    else if (identifier == "andI") return Token(identifier, TokenType::andI_Inst, lineCounter, columnCounter);
    else if (identifier == "orI") return Token(identifier, TokenType::orI_Inst, lineCounter, columnCounter);
    else if (identifier == "xorI") return Token(identifier, TokenType::xorI_Inst, lineCounter, columnCounter);
    else if (identifier == "notI") return Token(identifier, TokenType::notI_Inst, lineCounter, columnCounter);
    else if (identifier == "norI") return Token(identifier, TokenType::norI_Inst, lineCounter, columnCounter);
    else if (identifier == "sll") return Token(identifier, TokenType::sll_Inst, lineCounter, columnCounter);
    else if (identifier == "sra") return Token(identifier, TokenType::sra_Inst, lineCounter, columnCounter);
    else if (identifier == "bEq") return Token(identifier, TokenType::bEq_Inst, lineCounter, columnCounter);
    else if (identifier == "bNe") return Token(identifier, TokenType::bNe_Inst, lineCounter, columnCounter);
    else if (identifier == "bLt") return Token(identifier, TokenType::bLt_Inst, lineCounter, columnCounter);
    else if (identifier == "bGt") return Token(identifier, TokenType::bGt_Inst, lineCounter, columnCounter);
    else if (identifier == "bLTz") return Token(identifier, TokenType::bLTz_Inst, lineCounter, columnCounter);
    else if (identifier == "bGTz") return Token(identifier, TokenType::bGTz_Inst, lineCounter, columnCounter);
    else if (identifier == "jmp") return Token(identifier, TokenType::jmp_Inst, lineCounter, columnCounter);
    else if (identifier == "jmpL") return Token(identifier, TokenType::jmpL_Inst, lineCounter, columnCounter);
    else if (identifier == "jmpL_Reg") return Token(identifier, TokenType::jmpL_Reg_Inst, lineCounter, columnCounter);
    else if (identifier == "jmpRet") return Token(identifier, TokenType::jmpRet_Inst, lineCounter, columnCounter);
    else if (identifier == "lb") return Token(identifier, TokenType::lb_Inst, lineCounter, columnCounter);
    else if (identifier == "lw") return Token(identifier, TokenType::lw_Inst, lineCounter, columnCounter);
    else if (identifier == "sb") return Token(identifier, TokenType::sb_Inst, lineCounter, columnCounter);
    else if (identifier == "sw") return Token(identifier, TokenType::sw_Inst, lineCounter, columnCounter);
    else if (identifier == "halt") return Token(identifier, TokenType::halt_Inst, lineCounter, columnCounter);
    else if (identifier == "printw_Int") return Token(identifier, TokenType::printw_Int_Inst, lineCounter, columnCounter);
    else if (identifier == "printw_Hex") return Token(identifier, TokenType::printw_Hex_Inst, lineCounter, columnCounter);
    else if (identifier == "printw_Bin") return Token(identifier, TokenType::printw_Bin_Inst, lineCounter, columnCounter);
    else return Token(identifier, TokenType::identifier, lineCounter, columnCounter);
}

Token Lexer::resolveOneSymbol(string const& oneSymbol) const {
    if (oneSymbol == ",") return Token(oneSymbol, TokenType::comma, lineCounter, columnCounter); 
    else if (oneSymbol == ":") return Token(oneSymbol, TokenType::colon, lineCounter, columnCounter);
    else if (oneSymbol == "[") return Token(oneSymbol, TokenType::startBracket, lineCounter, columnCounter);
    else if (oneSymbol == "]") return Token(oneSymbol, TokenType::endBracket, lineCounter, columnCounter);
    else throw std::runtime_error("Unable to match " + oneSymbol + " with a token type");
}