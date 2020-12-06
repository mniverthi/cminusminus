#pragma once
#ifndef EMITTER
#define EMITTER
#include <string>
#include <iostream>
class Emitter {
    private:
        string desired_path;
        string header;
        string code;
    public:
        void emit(string new_code);
        void emitLine();
        void headerLine();
        void writeFile();
};
#endif