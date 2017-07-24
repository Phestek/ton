#ifndef TON_DOCUMENT_H
#define TON_DOCUMENT_H

#include "ton/element.h"

namespace ton {

class Document {
public:
    bool load_from_file(const std::string& path);
    bool reload_from_file();
    bool load_from_string(std::string&& source);

    Element& operator[](const std::string& name);

    void push_back(Element&& element);
    void push_back(const Element& element);

private:
    std::string _path;
    
    Object _root{{}};
};

}

#endif //TON_DOCUMENT_H

