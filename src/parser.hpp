#pragma once
#ifndef PARSER
#define PARSER
#include <string>
#include <iostream>
#include "lexer.hpp"
#include "emitter.hpp"
class Parser {
    private:
        Lexer* lexer;
        Token* curr;
        Token* peek;
        Emitter* emitter;
    public:
        Parser(Lexer* lexer, Emitter* emitter);
        void abort(string message);
        bool checkToken(TokenType desired);
        bool checkPeek(TokenType desired);
        void nextToken();
        void matchToken(TokenType desired);
        void parse();
        void run();
        void newline();
        void expression();
        void comparison();
        void term();
        void unary();
        void primary();
};
#endif