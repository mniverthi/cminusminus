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
        current_pos = -1;
        current_char = 0;
        current_linechar = 0;
        current_line = 0;
        file_path = path;
        length = source.length();
        // cout << source << endl;
        nextCharacter();
    } else {
        exit(EXIT_FAILURE);
    }
}
void Lexer::nextCharacter() { // moves next character pointer
    if (++current_pos >= length) {
        current_char = '\0'; // reached the end of the file
    } else {
        current_char = source[current_pos];
    }
}
void Lexer::skipComment() {

}
char Lexer::peekCharacter() {
    return current_pos + 1 >= length ? '\0' : source[current_pos + 1];
}
void Lexer::skipSpace() {

}
string Lexer::getToken() {
    

}
void Lexer::abortMission(string message) {
    cout << "Lexing error: " << message << endl;
    cout << "Occurred at: \t" << "Line " << current_line + 1 << ", Char " << current_linechar << endl;
    exit(EXIT_FAILURE);
}

