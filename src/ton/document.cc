#include "ton/document.h"

#include "ton/parser.h"

namespace ton {

bool Document::load_from_file(const std::string& path) {
    Lexer lexer{};
    if(!lexer.load_from_file(path)) {
        return false;
    }
    Parser parser{*this, lexer};
    return parser.errors_reported();
}

bool Document::reload_from_file() {
    if(_path == "") {
        return false;
    }
    return load_from_file(_path);
}

bool Document::load_from_string(std::string&& source) {
    Lexer lexer{};
    lexer.load_from_string(std::move(source));
    Parser parser{*this, lexer};
    return parser.errors_reported();
}

Element& Document::operator[](const std::string& name) {
    return _root[name];
}

void Document::push_back(Element&& element) {
    _root.push_back(std::move(element));
}

void Document::push_back(const Element& element) {
    _root.push_back(element);
}

}

