#ifndef TON_ELEMENT_H
#define TON_ELEMENT_H

#include <string>
#include <variant>
#include <vector>

namespace ton {

using Integer = int;
using Float   = double;
using String  = std::string;

class Element;

class Object {
public:
    Object(const std::vector<Element>& members);
    Object(std::vector<Element>&& members);

    Element& operator[](const std::string& name);

    void push_back(const Element& element);
    void push_back(Element&& element);

    std::size_t num_members() const;

private:
    std::vector<Element> _members;
};

using Type = std::variant<Integer, Float, String, Object>;

class Element {
public:
    Element(const std::string& name, const Type& type);
    Element(std::string&& name, const Type& type);
    // This does not override default copy or move assignment operator.
    Element& operator=(const Type& type);

    template<typename T>
    T as();

private:
    friend class Object;
    friend class Document;
    std::string _name;
    Type        _type;
};

template <typename T>
T Element::as() {
    return std::get<T>(_type);
}

}

#endif //TON_ELEMENT_H
