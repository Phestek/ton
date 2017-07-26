#include <iostream>

#include <ton/document.h>

int main() {
    ton::Document doc{};
    doc.load_from_file("hello.ton");

    const auto& integer = doc["int"].as<ton::Integer>();
    std::cout << "int: " << integer << '\n';

    return 0;
}

