#include "token.hpp"
using namespace std;
std::unordered_map<TokenType, string> Token::type_vals = {{LABEL, "LABEL"}, {GOTO, "GOTO"}, {PRINT, "PRINT"}, {INPUT, "INPUT"}, {LET, "LET"}, {IF, "IF"}, 
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
bool Token::isKeyword() {
    return !text.compare(type_vals[type]) && type >= 100 && type <= 200;
}
            
