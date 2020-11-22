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
Token::TokenType Token::getType() {
    return type;
}