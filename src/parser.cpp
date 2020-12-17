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
    if (curr) {
        delete curr;
    }
    if (peek) {
        delete peek;
    }
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

void Parser::newline() {
    matchToken(NEWLINE);
    while (checkToken(NEWLINE)) {
        nextToken();
    }
}

void Parser::comparison() {
    expression();
    if (curr -> isComparison()) {
        emitter -> emit(curr -> getContent());
        nextToken();
        expression();
    } else {
        abort("Expected comparison operator at: " + curr -> getContent());
    }
    while (curr -> isComparison()) {
        emitter -> emit(curr -> getContent());
        nextToken();
        expression();
    }
}

void Parser::expression() {
    term();
    while (checkToken(PLUS) || checkToken(MINUS)) {
        emitter -> emit(curr -> getContent());
        nextToken();
        term();
    }
}

void Parser::unary() {
    if (checkToken(PLUS) || checkToken(MINUS)) {
        emitter -> emit(curr -> getContent());
        nextToken();  
    }
    primary();
}

void Parser::term() {
    unary();
    while (checkToken(ASTERISK) || checkToken(SLASH)) {
        emitter -> emit(curr -> getContent());
        nextToken();
        unary();
    }
}

void Parser::primary() {
    if (checkToken(NUMBER)) {
        emitter -> emit(curr -> getContent());
        nextToken();
    } else if (checkToken(IDENT)) {
        if (!symbols.count(curr -> getContent())) {
            abort("Referencing variable before assignment: " + curr -> getContent());
        }
        emitter -> emit(curr -> getContent());
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
                // emitter -> textLine("printf(\"" + curr -> getContent() + "\\n\");");
                emitter -> textLine("mov rax, " + curr -> getContent());
                emitter -> textLine("call puts");
                nextToken();
            } else {
                // expression expected
                // emitter -> emit("printf(\"%.2f\\n\", (float)(");
                expression();
                // emitter -> emit("));");
            }
            break;
        case IF:
            nextToken();
            // emitter -> emit("if (");
            comparison();
            matchToken(THEN);
            newline();
            // emitter -> emit(") {");
            while (!checkToken(ENDIF)) {
                parse();
            }
            matchToken(ENDIF);
            // emitter -> emit("}");
            break;
        case WHILE:
            nextToken();
            // emitter -> emit("while (");
            comparison();
            matchToken(REPEAT);
            newline();
            // emitter -> emit(") {");
            while(!checkToken(ENDWHILE)) {
                parse();
            }
            matchToken(ENDWHILE);
            // emitter -> emit("}");
            break;
        case GOTO:
            nextToken();
            jumped_labels.insert(curr -> getContent());
            // emitter -> textLine("goto: " + curr -> getContent() + ";");
            matchToken(IDENT);
            emitter -> textLine("jmp: " + curr -> getContent());
            break;
        case INPUT:
            nextToken();
            if (!symbols.count(curr -> getContent())) {
                symbols.insert(curr -> getContent());
                // emitter -> dataLine("float " + curr -> getContent() + ";");
                emitter -> dataLine(curr -> getContent() + ": resq 1"); 
            }
            // emitter -> textLine("if(0 == scanf(\"%" + "f\", &" + curr -> getContent() + ")) {");
            // emitter -> textLine(curr -> getContent() + " = 0;");
            // emitter -> emit("scanf(\"%");
            // emitter -> textLine("*s\");");
            // emitter -> textLine("}");

            matchToken(IDENT);
            break;
        case LABEL:
            nextToken();
            if (declared_labels.count(curr -> getContent())) {
                abort("Label already exists: " + curr -> getContent());
            }
            declared_labels.insert(curr -> getContent());
            emitter -> textLine(curr -> getContent() + ":");
            matchToken(IDENT);
            break;
        case LET:
            nextToken();
            if (!symbols.count(curr -> getContent())) {
                symbols.insert(curr -> getContent());
                // emitter -> dataLine("float " + curr -> getContent() + ";");
                emitter -> bssLine(curr -> getContent() + ": resq 1");
            }
            emitter -> textLine("mov rax, " + curr -> getContent());
            // emitter -> emit(curr -> getContent() + "=");
            matchToken(IDENT);
            matchToken(EQ);
            expression();
            // emitter -> textLine(";");
            emitter -> textLine("mov [" + curr -> getContent() + "], rbx");
            break;
        default:
            abort("Invalid statement at " + curr -> getContent() + " (" + to_string(curr -> getType()) + ")");
            break;
    }
    newline();
}
void Parser::run() {
    // emitter -> dataLine("#include <stdio.h>");
    // emitter -> dataLine("");
    // emitter -> dataLine("int main(void) {");

    emitter -> headerLine("global _start");
    emitter -> headerLine("extern puts");

    emitter -> dataLine("section .data");
    emitter -> textLine("section .text");
    emitter -> bssLine("section .bss");

    emitter -> textLine("_start:");

    while (checkToken(NEWLINE)) {
        nextToken();
    }

    while (curr -> getType() != ENDFILE) {
        parse();
    }

    // emitter -> textLine("return 0;");
    // emitter -> textLine("}");

    for (auto i : jumped_labels) {
        if (!declared_labels.count(i)) {
            abort("Attempting to GOTO an undeclared label: " + i);
        }
    }    
}

