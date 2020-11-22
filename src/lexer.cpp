#include <bits/stdc++.h>
#include "lexer.hpp"
#include "token.hpp"
using namespace std;

Lexer::Lexer(string path) { // initializes lexer class and sets up input string for parsing
    ifstream temp(path);
    if (temp) {
        stringstream ss;
        ss << temp.rdbuf();
        source = ss.str();
        current_sourcepos = -1;
        current_char = 0;
        current_linepos = 1;
        current_line = 1;
        file_path = path;
        length = source.length();
        // cout << source << endl;
        nextCharacter();
    } else {
        exit(EXIT_FAILURE);
    }
}
void Lexer::nextCharacter() { // moves next character pointer
    if (++current_sourcepos >= length) {
        current_char = '\0'; // reached the end of the file
    } else {
        current_char = source[current_sourcepos];
    }
}
void Lexer::skipComment() {

}
char Lexer::peekCharacter() {
    return current_sourcepos + 1 >= length ? '\0' : source[current_sourcepos + 1];
}
void Lexer::skipSpace() {

}
string Lexer::getToken() {
    Token current;
    if (current_char == '+') {
        current.setContent('+');
        current.setType(TokenType::PLUS);
    } else if (current_char == '-') {
        current.setContent('-');
        current.setType(TokenType::MINUS);
    } else if (current_char == '*') {
        current.setContent('*');
        current.setType(TokenType::ASTERISK);
    } else if (current_char == '/') {
        current.setContent('/');
        current.setType(TokenType::SLASH);
    } else if (current_char == '\n') {
        current.setContent('\n');
        current.setType(TokenType::NEWLINE);
        current_line++;
        current_linepos = 0;
    } else if (current_char == '\0') {
        current.setContent('\0');
        current.setType(TokenType::ENDFILE);
    } else {

    }
    nextCharacter();
}
void Lexer::abortMission(string message) {
    cout << "Lexing error: " << message << endl;
    cout << "Occurred at: \t" << "Line " << current_line << ", Char " << current_linepos << endl;
    exit(EXIT_FAILURE);
}

