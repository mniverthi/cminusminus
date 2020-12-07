#pragma once
#ifndef PARSER
#define PARSER
#include <string>
#include <iostream>
#include <unordered_set>
#include "lexer.hpp"
#include "emitter.hpp"
class Parser {
    private:
        Lexer* lexer;
        Token* curr;
        Token* peek;
        Emitter* emitter;
    public:
        unordered_set<string> jumped_labels;
        unordered_set<string> declared_labels;
        unordered_set<string> symbols;
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