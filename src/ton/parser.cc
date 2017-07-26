#include "ton/parser.h"

#include <iostream>

// TODO: Really, these errors messages are mistake. I mean, happy little accidents. Change them to something with sense.

namespace ton {

Parser::Parser(Document& doc, Lexer& lexer)
        : _lexer{lexer} {
    while(_lexer.peek_token().type != Token_Type::END_OF_FILE) {
        doc.push_back(parse_element());
    }
}

bool Parser::errors_reported() const noexcept {
    return _errors_reported;
}

void Parser::report_error(const std::string& msg) {
    _errors_reported = true;
    auto token = _lexer.peek_token(-1);
    std::cerr << token.line << ':' << token.column << ": Error: " << msg << ".\n";
}

Token Parser::next_token() {
    return _lexer.next_token();
}

Token Parser::next_token(Token_Type type) {
    auto token = _lexer.next_token();
    if(token.type != type) {
        report_error("Token of unexpected type");
    }
    return token;
}

bool Parser::match_token(Token_Type type) {
    if(_lexer.peek_token(0).type == type) {
        next_token();
        return true;
    }
    return false;
}

Element Parser::parse_element() {
    auto name = next_token(Token_Type::IDENTIFIER).value;
    if(match_token(Token_Type::EQUALS)) {
        if(match_token(Token_Type::L_BRACKET)) {
            return parse_array(std::move(name));
        }
        return parse_primitive(std::move(name));
    }
    if(match_token(Token_Type::L_BRACE)) {
        return parse_object(std::move(name));
    }
    report_error("Unexpected token");
    return Element{name, 0};
}

Element Parser::parse_primitive(std::string&& name) {
    auto value = next_token();
    if(value.type == Token_Type::INTEGER) {
        return Element{name, std::stoi(value.value)};
    }
    if(value.type == Token_Type::FLOAT) {
        return Element{name, std::stod(value.value)};
    }
    if(value.type == Token_Type::STRING) {
        return Element{name, value.value};
    }
    report_error("Unexpected token");
    return Element{name, 0};
}

Element Parser::parse_object(std::string&& name) {
    std::vector<Element> members;
    while(!match_token(Token_Type::R_BRACE)) {
        members.push_back(parse_element());
    }
    return Element{name, std::move(members)};
}

Element Parser::parse_array(std::string&& name) {
    Array array;
    if(!match_token(Token_Type::R_BRACKET)) {
        do {
            array.push_back(parse_array_element());
        } while(match_token(Token_Type::COMMA));
        next_token(Token_Type::R_BRACKET);
    }
    return Element{name, array};
}

Type Parser::parse_array_element() {
    auto value = next_token();
    if(value.type == Token_Type::INTEGER) {
        return std::stoi(value.value);
    } else if(value.type == Token_Type::FLOAT) {
        return std::stod(value.value);
    } else if(value.type == Token_Type::STRING) {
        return value.value;
    } else if(value.type == Token_Type::L_BRACE) {
        return parse_anonymous_object();
    } else if(value.type == Token_Type::L_BRACKET) {
        return parse_nested_array();
    }
    report_error("Unexpected tokennnn");
    return 0;
}

Type Parser::parse_anonymous_object() {
    std::vector<Element> members;
    while(!match_token(Token_Type::R_BRACE)) {
        members.push_back(parse_element());
    }
    return Object{members};
}

Type Parser::parse_nested_array() {
    std::vector<Type> elements;
    if(!match_token(Token_Type::R_BRACKET)) {
        do {
            elements.push_back(parse_array_element());
        } while(match_token(Token_Type::COMMA));
        next_token(Token_Type::R_BRACKET);
    }
    return Array{elements};
}

}

