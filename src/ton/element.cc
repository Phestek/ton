#include "ton/element.h"

namespace ton {

Object::Object(const std::vector<Element>& members)
        : _members{members} {
}

Object::Object(std::vector<Element>&& members)
        : _members{members} {
}

Element& Object::operator[](const std::string& name) {
    for(auto& member : _members) {
        if(member._name == name) {
            return member;
        }
    }
    _members.push_back({name, Type{}});
    return _members.back();
}

void Object::push_back(Element&& element) {
    _members.push_back(std::move(element));
}

void Object::push_back(const Element& element) {
    _members.push_back(element);
}

std::size_t Object::num_members() const {
    return _members.size();
}

Element::Element(const std::string& name, const Type& type)
        : _name{name}, _type{type} {
}

Element::Element(std::string&& name, const Type& type)
        : _name{std::move(name)}, _type{type} {
}

Element& Element::operator=(const Type& type) {
    _type = type;
    return *this;
}

Element& Element::operator=(Type&& type) {
    _type = std::move(type);
    return *this;
}

}

