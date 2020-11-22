#include <bits/stdc++.h>
#include "tokentype.h"
using namespace std;

class Lexer {
    private:
        int currentPosition;
        int currentCharacter;
        string filePath;
        string source;
        int length;
    public:
        Lexer(string path) { // initializes lexer class and sets up input string for parsing
            ifstream temp(path);
            if (temp) {
                stringstream ss;
                ss << temp.rdbuf();
                source = ss.str();
                currentPosition = -1;
                currentCharacter = 0;
                filePath = path;
                length = source.length();
                // cout << source << endl;
                nextToken();
            } else {
                exit(EXIT_FAILURE);
            }
        }
        void nextToken() { // moves next character pointer
            if (++currentPosition >= length) {
                currentCharacter = '\0'; // reached the end of the file
            } else {
                currentCharacter = source[currentPosition];
            }
        }
        void skipComment() {
            
        }
        char peekToken() {
            return currentPosition + 1 >= length ? '\0' : source[currentPosition + 1];
        }
        void skipSpace() {

        }
        void skipComment() {
            
        }
        char getToken() {

        }

};
