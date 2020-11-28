#pragma once
#ifndef LEXER
#define LEXER
#include <string>
#include <iostream>
#include "token.hpp"
class Lexer {
    private:
        int current_sourcepos;
        char current_char;
        // std::string file_path;
        std::string source;
        int length;
        int current_line;
        int current_linepos;
    public:
        Lexer(std::string path);
        void nextCharacter();
        void skipComment();
        char peekCharacter();
        void skipSpace();
        void skipComment();
        Token* getToken();
        void abort(string message);
        int getCurrentLine();
        int getCurrentLinePos();
};
#endif