#pragma once
#ifndef PARSER
#define PARSER
#include <string>
#include <stack>
#include <iostream>
#include "lexer.hpp"
class Parser {
    private:
        Lexer* lexer;
        Token* curr;
        Token* peek;
        stack<Token*> seen;
    public:
        Parser(Lexer* lexer);
        void abort(string message);
        bool checkToken(TokenType desired);
        bool checkPeek(TokenType desired);
        void nextToken();
        void matchToken(TokenType desired);
        void parse();
        void run();
        void print();
        void expression();
};
#endif