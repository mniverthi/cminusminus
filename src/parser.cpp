/**
 * program ::= {statement}
 * statement ::= "PRINT" (expression | string) nl
 *      | "IF" comparison "THEN" nl {statement} "ENDIF" nl
 *      | "WHILE" comparison "REPEAT" nl {statement} "ENDWHILE" nl
 *      | "LABEL" ident nl
 *      | "GOTO" ident nl
 *      | "LET" ident "=" expression nl
 *      | "INPUT" ident nl
 * comparison ::= expression (("==" | "!=" | ">" | ">=" | "<" | "<=") expression) +
 * expression ::= term {( "-" | "+" ) term}
 * term ::= unary {( "/" | "*" ) unary}
 * unary ::= ["+" | "-"] primary
 * primary ::= number | ident
 * nl ::= '\n'+
*/
#include "parser.hpp"
using namespace std;

Parser::Parser(Lexer* lex, Emitter* emit) {
    lexer = lex;
    emitter = emit;
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
// TODO: make AST stuff
void Parser::newline() {
    matchToken(NEWLINE);
    while (checkToken(NEWLINE)) {
        nextToken();
    }
}
void Parser::comparison() {
    expression();
    if (curr -> isComparison()) {
        nextToken();
        expression();
    } else {
        abort("Expected comparison operator at: " + curr -> getContent());
    }
    while (curr -> isComparison()) {
        nextToken();
        expression();
    }
}
void Parser::expression() {
    term();
    while (checkToken(PLUS) || checkToken(MINUS)) {
        nextToken();
        term();
    }
}
void Parser::unary() {
    if (checkToken(PLUS) || checkToken(MINUS)) {
        nextToken();  
    }
    primary();
}
void Parser::term() {
    unary();
    while (checkToken(ASTERISK) || checkToken(SLASH)) {
        nextToken();
        unary();
    }
}
void Parser::primary() {
    if (checkToken(NUMBER)) {
        nextToken();
    } else if (checkToken(IDENT)) {
        nextToken();
    } else {
        abort("Unexpected token at " + curr -> getContent());
    }
}
void Parser::parse() {
    switch (curr -> getType()) {
        case PRINT:
            nextToken();
            if (checkToken(STRING)) {
                // print statement thing
                nextToken();
            } else {
                // expression expected
                expression();
            }
            break;
        case IF:
            nextToken();
            comparison();
            matchToken(THEN);
            while (!checkToken(ENDIF)) {
                parse();
            }
            matchToken(ENDIF);
            break;
        case WHILE:
            nextToken();
            comparison();
            matchToken(REPEAT);
            newline();
            while(!checkToken(ENDWHILE)) {
                parse();
            }
            matchToken(ENDWHILE);
            break;
        case GOTO:
        case INPUT:
        case LABEL:
            nextToken();
            matchToken(IDENT);
            break;
        case LET:
            nextToken();
            matchToken(IDENT);
            matchToken(EQ);
            expression();
            break;
        // case GOTO:
        //     nextToken();
        //     matchToken(IDENT);
        //     break;
        // case INPUT:
        //     nextToken();
        //     matchToken(IDENT);
        //     break;
        default:
            abort("Invalid statement at " + curr -> getContent() + " (" + to_string(curr -> getType()) + ")");
            break;
    }
    newline();
}
void Parser::run() {
    while (curr -> getType() != ENDFILE) {
        parse();
    }
}

