#include "token.hpp"
#include "lexer.hpp"
using namespace std;
Lexer::Lexer(string input) { // initializes lexer class and sets up input string for parsing
    source = input;
    current_sourcepos = -1;
    current_char = 0;
    current_linepos = 1;
    current_line = 1;
    length = source.length();
    // Extras
    // file_path = path;
    // cout << source << endl;
    nextCharacter();
}
void Lexer::nextCharacter() { // moves next character pointer
    if (++current_sourcepos >= length) {
        current_char = '\0'; // reached the end of the file
    } else {
        current_char = source[current_sourcepos];
    }
}
void Lexer::skipComment() {
    if (current_char == '#') {
        while (current_char != '\n') {
            nextCharacter();
        }
    }
}
char Lexer::peekCharacter() {
    return current_sourcepos + 1 >= length ? '\0' : source[current_sourcepos + 1];
}
void Lexer::skipSpace() {
    while (current_char == ' ' || current_char == '\t' || current_char == '\r') {
        nextCharacter();
    }
}
Token* Lexer::getToken() { // next token logic
    skipSpace();
    skipComment();
    Token* current = new Token();
    int start_pos = current_sourcepos;
    switch (current_char) {
        case '+':
            current -> setContent('+');
            current -> setType(TokenType::PLUS);
            break;
        case '-':
            current -> setContent('-');
            current -> setType(TokenType::MINUS);
            break;
        case '/':
            current -> setContent('/');
            current -> setType(TokenType::SLASH);
            break;
        case '*':
            current -> setContent('*');
            current -> setType(TokenType::ASTERISK);
            break;
        case '\n':
            current -> setContent('\n');
            current -> setType(TokenType::NEWLINE);
            current_line++;
            current_linepos = 0;
            break;
        case '\0':
            current -> setContent('\0');
            current -> setType(TokenType::ENDFILE);
            break;
        case '=':
            if (peekCharacter() == '=') {
                current -> setContent("==");
                current -> setType(TokenType::EQEQ);
            } else {
                current -> setContent("=");
                current -> setType(TokenType::EQ);
            }
            break;
        case '<':
            if (peekCharacter() == '=') {
                current -> setContent("<=");
                current -> setType(TokenType::LTEQ);
            } else {
                current -> setContent("<");
                current -> setType(TokenType::LT);
            }
            break;
        case '>':
            if (peekCharacter() == '=') {
                current -> setContent(">=");
                current -> setType(TokenType::GTEQ);
            } else {
                current -> setContent(">");
                current -> setType(TokenType::GT);
            }
            break;
        case '!':
            if (peekCharacter() == '=') {
                current -> setContent("!=");
                current -> setType(TokenType::NOTEQ);
            } else {
                abort("Invalid token detected");
            }
            break;
        case '\"':
            nextCharacter();
            while (current_char != '\"') {
                if (current_char == '\r' || current_char == '\n' || current_char == '\t' || current_char == '\\' || current_char == '%')
                    abort("Illegal character in string");
                nextCharacter();
            }
            current -> setContent(source.substr(start_pos + 1, current_sourcepos - (start_pos + 1)));
            current -> setType(TokenType::STRING);
            break;
        default:
            if (isdigit(current_char)) {
                while (isdigit(peekCharacter())) {
                    nextCharacter();
                }
                if (peekCharacter() == '.') {
                    nextCharacter();
                    if (!isdigit(peekCharacter())) {
                        abort("Invalid numeric literal");
                    }
                    while (isdigit(peekCharacter())) {
                        nextCharacter();
                    }
                    current -> setContent(source.substr(start_pos, current_sourcepos - start_pos + 1));
                    current -> setType(TokenType::NUMBER);
                }
            } else if (isalpha(current_char)) {
                while (isalpha(peekCharacter()) || isdigit(peekCharacter())) {
                    nextCharacter();
                }
                string content = source.substr(start_pos, current_sourcepos - start_pos + 1);
                TokenType actual = Token::isKeyword(content);
                current -> setContent(content);
                current -> setType(actual);
            } else {
                // should it be freed here?
                delete current;
                // free previously allocated and check it actually works lmao
                abort("Invalid token detected");
            }
        }
    nextCharacter();
    return current;
}
void Lexer::abort(string message) {
    cout << "Lexing error: " << message << endl;
    cout << "Occurred at: \t" << "Line " << current_line << ", Character " << current_linepos << endl;
    exit(EXIT_FAILURE);
}

