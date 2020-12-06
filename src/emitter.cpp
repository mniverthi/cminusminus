#include "emitter.hpp"
using namespace std;

Emitter::Emitter(string path) {
    output = path;
    header = "";
    code = "";
}

void Emitter::headerLine(string new_line) {
    header += new_line + "\n";
}

void Emitter::emitLine(string new_line) {
    code += new_line + "\n";
}

void Emitter::emit(string new_code) {
    code += new_code;
}

void Emitter::writeFile() {
    ofstream source;
    source.open(output);
    source << header << code;
    source.close();
}