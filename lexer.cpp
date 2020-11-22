#include <bits/stdc++.h>
#include "tokentype.h"
using namespace std;

class Lexer {
    private:
        int currentPosition;
        int currentCharacter;
        string filePath;
        string input;
    public:
        Lexer(string path) {
            ifstream temp(path);
            if (temp) {
                stringstream ss;
                ss << temp.rdbuf();
                input = ss.str();
                currentPosition = -1;
                currentCharacter = 0;
                filePath = path;
                cout << input << endl;
                nextCharacter();
            } else {
                exit(EXIT_FAILURE);
            }
        }
        void nextCharacter() {
            currentPosition++;
            currentCharacter = input[currentPosition];
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
