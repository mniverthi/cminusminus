#pragma ONCE
#ifndef PARSER
#define PARSER
#include "lexer.hpp"
#include <string>
class Parser {
    private:
        
    public:
        void abort(string message);
        bool checkToken();
        bool checkPeek();

};
#endif