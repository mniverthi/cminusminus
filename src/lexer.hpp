#pragma once
#ifndef LEXER
#define LEXER
#include <string>
class Lexer {
    private:
        int current_pos;
        int current_char;
        std::string file_path;
        std::string source;
        int length;
        int current_line;
        int current_linechar;
    public:
        Lexer(std::string path) { }
        void nextCharacter() { }
        void skipComment() { }
        char peekCharacter() { }
        void skipSpace() { }
        void skipComment() { }
        char getToken() { }
        void abortMission(string message) { }
};
#endif