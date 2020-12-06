#pragma once
#ifndef EMITTER
#define EMITTER
#include <string>
#include <fstream>
#include <sstream>
class Emitter {
    private:
        string output;
        string header;
        string code;
    public:
        Emitter(string path);
        void emit(string new_code);
        void emitLine(string new_line);
        void headerLine(string new_line);
        void writeFile();
};
#endif