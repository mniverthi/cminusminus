#include <bits/stdc++.h>
#include "tokentype.h"
using namespace std;

class Lexer {
    private:
        int currentPosition;
        int currentCharacter;
        string filePath;
        string source;
    public:
        Lexer(string path) {
            ifstream temp(path);
            if (temp) {
                stringstream ss;
                ss << temp.rdbuf();
                source = ss.str();
                currentPosition = -1;
                currentCharacter = 0;
                filePath = path;
                cout << source << endl;
                nextCharacter();
            } else {
                exit(EXIT_FAILURE);
            }
        }
        void nextCharacter() {
            currentPosition++;
            currentCharacter = source[currentPosition];
        }
        void skipComment() {

        }
        char peekToken() {

        }
        void skipSpace() {

        }
        void skipComment() {
            
        }
        char getToken() {

        }

};
