#ifndef TON_PARSER_H
#define TON_PARSER_H

#include "ton/document.h"
#include "ton/lexer.h"

namespace ton {

class Parser {
public:
    Parser(Document& doc, Lexer& lexer);

    bool errors_reported() const noexcept;

private:
    void report_error(const std::string& msg);

    Token next_token();
    Token next_token(Token_Type type);
    
    bool match_token(Token_Type type);

    Element parse_element();
    Element parse_primitive(std::string&& name);
    Element parse_object(std::string&& name);

    Lexer&    _lexer;

    bool _errors_reported = false;
};

}

#endif //TON_PARSER_H

