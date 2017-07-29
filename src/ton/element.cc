#include "ton/element.h"

namespace ton {

Object::Object(const std::vector<Element>& members)
        : _members{members} {
}

Object::Object(std::vector<Element>&& members)
        : _members{members} {
}

Array_Element::Array_Element(const Type& type) {
    _type = type;
}

Array_Element(Type&& type) {
    _type = std::move(type);
}

Array_Element& Array_Element::operator=(const Type& type) {
    _type = type;
    return *this;
}

Array_Element& Array_Element::operator=(Type&& type) {
    _type = std::move(type);
    return *this;
}

Array::Array(const Array& other) {
    std::copy(other._elements.begin(), other._elements.end(), std::back_inserter(_elements));
}

//Array::Array(Array&& other) {
    //_elements = std::move(other._elements);
//}

Array::Array(const std::vector<Array_Element>& vec) {
    std::copy(vec.begin(), vec.end(), std::back_inserter(_elements));
}

//Array::Array(std::vector<Type>&& vec) {
    //_elements = std::move(vec);
//}

Array& Array::operator=(const Array& other) {
    std::copy(other._elements.begin(), other._elements.end(), std::back_inserter(_elements));
    return *this;
}

//Array& Array::operator=(Array&& other) {
    //_elements = std::move(other._elements);
    //return *this;
//}

void Array::push_back(const Type& type) {
    _elements.push_back(type);
}

void Array::push_back(Type&& type) {
    _elements.push_back(std::move(type));
}

void Array::pop_back() {
    _elements.pop_back();
}

Type& Array::at(std::size_t index) {
    return _elements.at(index);
}

const Type& Array::at(std::size_t index) const {
    return _elements.at(index);
}

Type& Array::operator[](std::size_t index) {
    return _elements[index];
}

const Type& Array::operator[](std::size_t index) const {
    return _elements[index];
}

Type& Array::back() {
    return _elements.back();
}

const Type& Array::back() const {
    return _elements.back();
}

void Array::reserve(std::size_t new_cap) {
    _elements.reserve(new_cap);
}

void Array::resize(std::size_t new_cap) {
    _elements.resize(new_cap);
}

bool Array::empty() const {
    return _elements.empty();
}

std::size_t Array::size() const {
    return _elements.size();
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

