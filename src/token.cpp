#include "token.hpp"
using namespace std;
//should probably add all token types
std::unordered_map<TokenType, string> Token::keywords = {{LABEL, "LABEL"}, {GOTO, "GOTO"}, {PRINT, "PRINT"}, {INPUT, "INPUT"}, {LET, "LET"}, {IF, "IF"}, 
{THEN, "THEN"}, {ENDIF, "ENDIF"}, {WHILE, "WHILE"}, {REPEAT, "REPEAT"}, {ENDWHILE, "ENDWHILE"}};

Token::Token(TokenType which, std::string input) {
    type = which;
    text = input;
}
Token::Token(TokenType which, char input) {
    type = which;
    text = to_string(input);
}
Token::Token() { }
string Token::getContent() {
    return text;
}
TokenType Token::getType() {
    return type;
}
void Token::setType(TokenType which) { 
    type = which;
}
void Token::setContent(std::string input) { 
    text = input;
}
void Token::setContent(char input) { 
    text = to_string(input);
}
bool Token::isCharacter() {
    return text.length() == 1;
}
TokenType Token::isKeyword(string text) {
    std::unordered_map<TokenType, string>::iterator it = keywords.begin();
    while (it != keywords.end()) {
        if (!text.compare(it -> second)) {
            return it -> first;
        }
        advance(it, 1);
    }
    return TokenType::IDENT; 
}
            
