#include "emitter.hpp"
using namespace std;

Emitter::Emitter(string path) {
    output = path;
    data = "";
    code = "";
}

void Emitter::dataLine(string new_line) {
    data += new_line + "\n";
}

void Emitter::bssLine(string new_line) {
    bss += new_line + "\n";
}

void Emitter::textLine(string new_line) {
    code += new_line + "\n";
}

void Emitter::emit(string new_code) {
    code += new_code;
}

void Emitter::headerLine(string new_line) {
    header += new_line + "\n";
}

void Emitter::writeFile() {
    ofstream source;
    source.open(output);
    source << data << code;
    source.close();
}