#ifndef TON_LEXER_H
#define TON_LEXER_H

#include <string>
#include <vector>

namespace ton {

enum class Token_Type {
    L_BRACE,
    R_BRACE,
    L_BRACKET,
    R_BRACKET,
    EQUALS,
    INTEGER,
    FLOAT,
    STRING,
    IDENTIFIER,
    END_OF_FILE
};

struct Token {
    Token_Type  type;
    std::string value;
    std::size_t line;
    std::size_t column;
};

class Lexer {
public:
    void load_from_string(std::string&& source);
    bool load_from_file(const std::string& path);

    Token next_token();
    Token peek_token(int depth = 1) const;

private:
    void whitespace(char c);
    void comment(char c);
    void string(char c);
    void number(char c);
    void identifier(char c);

    //void hex_number(char c);
    //void dec_number(char c);

    std::size_t _current = 0;
    std::size_t _line = 1;
    std::size_t _last_newline = 0;

    std::string        _source;
    std::vector<Token> _tokens;
    std::size_t        _current_token = 0;
};

}

#endif //TON_LEXER_H

