#include "parser.hpp"
#include "lexer.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;
int main(int argc, char** argv) {
    cout << "mangolang Compiler: v 1.0" << endl; 
    if (argc < 3) {
        cout << "Error: Compiler needs source file path and destination name as arguments" << endl;
        exit(EXIT_FAILURE);
    }
    char* path = argv[1];
    char* desired = argv[2];
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
    Lexer* lex = new Lexer(source);
    Emitter* emit = new Emitter(desired);
    Parser* pars = new Parser(lex, emit); 
    //TODO: do stuff with this
    delete lex;
    delete emit;
    delete pars;
}