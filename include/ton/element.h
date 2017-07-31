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

class Array;
using Type = std::variant<Integer, Float, String, Object, Array>;

template <typename T>
bool operator==(const Type& left, const T& right) {
    return std::get<T>(left) == right;
}

template <typename T>
bool operator!=(const Type& left, const T& right) {
    return std::get<T>(left) != right;
}

// This wrapper is necessary, because there is no way to forward declare std::vector<Type>.
// I should probably reimplement std::vector, but lets leave it as it is now.

class Array {
public:
    Array();

    // TODO: Move constructors are broken.


    Array(const Array& vec);
    //Array(Array&& vec);
    
    Array(const std::vector<Type>& vec);
    //Array(std::vector<Type>&& vec);
    
    Array& operator=(const Array& vec);
    //Array& operator=(Array&& vec);

    void push_back(const Type& type);
    void push_back(Type&& type);

    void pop_back();

    Type& at(std::size_t index);
    const Type& at(std::size_t index) const;
    Type& operator[](std::size_t index);
    const Type& operator[](std::size_t index) const;
    Type& back();
    const Type& back() const;

    void reserve(std::size_t new_cap);
    void resize(std::size_t new_cap);

    bool empty() const;
    std::size_t size() const;

private:
    std::vector<Type> _elements;
};

class Element {
public:
    Element(const std::string& name, const Type& type);
    Element(std::string&& name, const Type& type);  // TODO: This is bullshit.
    // This does not override default copy or move assignment operator.
    Element& operator=(const Type& type);
    Element& operator=(Type&& type);

    template<typename T>
    T& as();
    template<typename T>
    const T& as() const;

private:
    friend class Object;
    friend class Document;
    
    template <typename T>
    friend bool operator==(const Element& left, const T& right);
    template <typename T>
    friend bool operator!=(const Element& left, const T& right);
    
    // We need special corner case for comparing 'String' with 'const char*' (eg. "qwer").
    //friend bool operator==(const Element& left, const char* str);
    //friend bool operator!=(const Element& left, const char* str);
    
    std::string _name;
    Type        _type;
};

template <typename T>
bool operator==(const Element& left, const T& right);
template <typename T>
bool operator!=(const Element& left, const T& right);

template <typename T>
T& Element::as() {
    return std::get<T>(_type);
}

template <typename T>
const T& Element::as() const {
    return std::get<T>(_type);
}

template <typename T>
bool operator==(const Element& left, const T& right) {
    return std::get<T>(left._type) == right;
}

template <typename T>
bool operator!=(const Element& left, const T& right) {
    return std::get<T>(left._type) != right;
}

//bool operator==(const Element& left, const char* str) {
    //return std::get<String>(left._type) == str;
//}

//bool operator!=(const Element& left, const char* str) {
    //return std::get<String>(left._type) != str;
//}

}

#endif //TON_ELEMENT_H

