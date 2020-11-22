#include <bits/stdc++.h>
#include "tokentype.h"
using namespace std;

class Lexer {
    private:
        int current_pos;
        int current_char;
        string file_path;
        string source;
        int length;
        int current_line;
        int current_char;
    public:
        Lexer(string path) { // initializes lexer class and sets up input string for parsing
            ifstream temp(path);
            if (temp) {
                stringstream ss;
                ss << temp.rdbuf();
                source = ss.str();
                current_pos = -1;
                current_char = 0;
                file_path = path;
                length = source.length();
                // cout << source << endl;
                nextCharacter();
            } else {
                exit(EXIT_FAILURE);
            }
        }
        void nextCharacter() { // moves next character pointer
            if (++current_pos >= length) {
                current_char = '\0'; // reached the end of the file
            } else {
                current_char = source[current_pos];
            }
        }
        void skipComment() {

        }
        char peekCharacter() {
            return current_pos + 1 >= length ? '\0' : source[current_pos + 1];
        }
        void skipSpace() {

        }
        void skipComment() {
            
        }
        char getToken() {
            if ()
        }

};
