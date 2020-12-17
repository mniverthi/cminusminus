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
        string data;
        string bss;
        string code;
    public:
        Emitter(string path);
        void emit(string new_code);
        void textLine(string new_line);
        void dataLine(string new_line);
        void bssLine(string new_line);
        void headerLine(string new_line);
        void writeFile();
};
#endif