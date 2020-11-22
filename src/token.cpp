#include "token.hpp"
using namespace std;
Token::Token(TokenType which, std::string input) {
    type = which;
    text = input;
}
string Token::getContent() {
    return text;
}
Token::TokenType Token::getType() {
    return type;
}