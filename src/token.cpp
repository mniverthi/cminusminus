#include "token.hpp"
using namespace std;
Token::Token(TokenType which, std::string input) {
    type = which;
    text = input;
}