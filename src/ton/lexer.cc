#include "lexer.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

namespace ton {

void Lexer::load_from_string(std::string&& source) {
    _source = std::move(source);
    while(_current < _source.length()) {
        char c = _source[_current];
        if(std::isspace(c)) {
            whitespace(c);
        }
        if(c == '#') {
            comment(c);
            continue;
        }
        if(c == '{') {
            _tokens.push_back({Token_Type::L_BRACE, "", _line, _current - _last_newline});
            ++_current;
            continue;
        }
        if(c == '}') {
            _tokens.push_back({Token_Type::R_BRACE, "", _line, _current - _last_newline});
            ++_current;
            continue;
        }
        if(c == '[') {
            _tokens.push_back({Token_Type::L_BRACKET, "", _line, _current - _last_newline});
            ++_current;
            continue;
        }
        if(c == ']') {
            _tokens.push_back({Token_Type::R_BRACKET, "", _line, _current - _last_newline});
            ++_current;
            continue;
        }
        if(c == '=') {
            _tokens.push_back({Token_Type::EQUALS, "", _line, _current - _last_newline});
            ++_current;
            continue;
        }
        if(c == ',') {
            _tokens.push_back({Token_Type::COMMA, "", _line, _current - _last_newline});
            ++_current;
            continue;
        }
        if(c == '"') {
            string(c);
            continue;
        }
        if(std::isdigit(c)) {
            number(c);
            continue;
        }
        if(std::isalpha(c) || c == '_') {
            identifier(c);
            continue;
        }
        // TODO: Handle invalid character.
    }
    _tokens.push_back({Token_Type::END_OF_FILE, "", _line, _current - _last_newline});
    // Source is no longer needed, so we can burn it.
    _source.clear();
    _source.reserve(0);
}

bool Lexer::load_from_file(const std::string& path) {
    std::ifstream file{path};
    if(!file.good()) {
        std::cerr << "Warning: Failed to open file " << std::quoted(path) << ".\n";
        return false;
    }
    std::stringstream source;
    source << file.rdbuf();
    load_from_string(source.str());
    return true;
}

Token Lexer::next_token() {
    if(_current_token < _tokens.size()) {
        return _tokens[_current_token++];
    }
    return _tokens.back();
}

Token Lexer::peek_token(int depth) const {
    if(_current_token + depth >= _tokens.size()) {
        return _tokens.back();
    }
    return _tokens.at(_current_token + depth);
}

void Lexer::whitespace(char c) {
    if(c == '\n') {
        ++_line;
        _last_newline = _current;
    }
    ++_current;
}

void Lexer::comment(char c) {
    while(c != '\n') {
        c = _source.at(_current++);
    }
}

void Lexer::string(char c) {
    std::string str;
    std::size_t begin = _current - _last_newline;
    c = _source[++_current];
    try {
        while(c != '"') {
            str += c;
            c = _source.at(++_current);
        }
    } catch(const std::out_of_range& e) {
        std::cerr << "Error: Unexpected end of file.\n";
    }
    ++_current; // Skip closing `"`.
    _tokens.push_back({Token_Type::STRING, str, _line, begin});
}

void Lexer::number(char c) {
    std::string num;
    std::size_t begin = _current - _last_newline;
    bool is_float = false;
    while(std::isdigit(c) || c == '.') {
        try {
            if(c == '.') {
                if(is_float) {
                    std::cerr << _line << ' ' << _current - _last_newline << ": "
                            << "Error: Too many decimal points.\n";
                } else {
                    is_float = true;
                }
            }
            num += c;
            c = _source.at(++_current);
        } catch(const std::out_of_range& e) {
            break;
        }
    }
    if(is_float) {
        _tokens.push_back({Token_Type::FLOAT, num, _line, begin});
    } else {
        _tokens.push_back({Token_Type::INTEGER, num, _line, begin});
    }
}

void Lexer::identifier(char c) {
    std::string id;
    std::size_t begin = _current - _last_newline;
    while(std::isalpha(c) || c == '_') {
        try {
            id += c;
            c = _source.at(++_current);
        } catch(const std::out_of_range& e) {
            break;
        }
    }
    _tokens.push_back({Token_Type::IDENTIFIER, id, _line, begin});
}

//void Lexer::hex_number(char c) {
//}

//void Lexer::dec_number(char c) {
//}

}

