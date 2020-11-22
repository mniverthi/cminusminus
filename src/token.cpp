#include "token.hpp"
using namespace std;
Token::Token(TokenType which, std::string input) {
    type = which;
    text = input;
}
Token::Token(TokenType which, char input) {
    type = which;
    text = to_string(input);
}
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
            