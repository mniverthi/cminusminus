/*
    program ::= {statement}
    statement ::= "PRINT" (expression | string) nl
        | "IF" comparison "THEN" nl {statement} "ENDIF" nl
        | "WHILE" comparison "REPEAT" nl {statement} "ENDWHILE" nl
        | "LABEL" ident nl
        | "GOTO" ident nl
        | "LET" ident "=" expression nl
        | "INPUT" ident nl
    comparison ::= expression (("==" | "!=" | ">" | ">=" | "<" | "<=") expression) +
    expression ::= term {( "-" | "+" ) term}
    term ::= unary {( "/" | "*" ) unary}
    unary ::= ["+" | "-"] primary
    primary ::= number | ident
    nl ::= '\n'+
*/
#include "parser.hpp"
using namespace std;
Parser::Parser(Lexer* lex) {
    lexer = lex;
    curr = nullptr;
    peek = nullptr;
    nextToken();
    nextToken();
}
void Parser::abort(string message) {
    cout << "Parsing error: " << message << endl;
    cout << "Occurred at: \t" << "Line " << lexer -> getCurrentLine() << ", Character " << lexer -> getCurrentLinePos() << endl;
    exit(EXIT_FAILURE);
}
void Parser::nextToken() {
    if (curr) {
        delete curr;
    }
    curr = peek;
    peek = lexer -> getToken();
}
void Parser::matchToken(TokenType desired) {
    if (desired != curr -> getType()) {
        abort("Expected " + Token::tokens[desired] + ", got " + Token::tokens[curr -> getType()]);
    }
    nextToken();
}
bool Parser::checkPeek(TokenType desired) {
    return peek -> getType() == desired;
}
bool Parser::checkToken(TokenType desired) {
    return curr -> getType() == desired;
}
void Parser::parse() {

}
void Parser::run() {

}

//TODO: make AST stuff