#include "parser.hpp"
#include "lexer.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;
int main(int argc, char** argv) {
    cout << "mangolang Compiler: v 1.0" << endl; 
    if (argc < 2) {
        cout << "Error: Compiler needs source file as argument." << endl;
        exit(EXIT_FAILURE);
    }
    char* path = argv[1];
    ifstream file(path);
    string source;
    if (file) {
        stringstream stream;
        stream << file.rdbuf();
        source = stream.str();
    } else {
        cout << "Invalid path." << endl;
        exit(EXIT_FAILURE);
    }
    Lexer lex = Lexer(source);
    Parser pars = Parser(lex); 
    //TODO: do stuff with this
}