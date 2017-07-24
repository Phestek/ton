#include <gtest/gtest.h>

#include "ton/lexer.h"

TEST(Lexer, Skip_Whitespaces) {
    std::string src{" \n\t\n\v\f\r"};
    ton::Lexer lexer{};
    lexer.load_from_string(std::move(src));
    ASSERT_EQ(lexer.next_token().type, ton::Token_Type::END_OF_FILE);
}

TEST(Lexer, Comments) {
    std::string src{"#this is comment\n"};
    ton::Lexer lexer{};
    lexer.load_from_string(std::move(src));
    ASSERT_EQ(lexer.next_token().type, ton::Token_Type::END_OF_FILE);
}

TEST(Lexer, Braces) {
    std::string src{"{}"};
    ton::Lexer lexer{};
    lexer.load_from_string(std::move(src));
    ASSERT_EQ(lexer.next_token().type, ton::Token_Type::L_BRACE);
    ASSERT_EQ(lexer.next_token().type, ton::Token_Type::R_BRACE);
}

TEST(Lexer, Brackets) {
    std::string src{"[]"};
    ton::Lexer lexer{};
    lexer.load_from_string(std::move(src));
    ASSERT_EQ(lexer.next_token().type, ton::Token_Type::L_BRACKET);
    ASSERT_EQ(lexer.next_token().type, ton::Token_Type::R_BRACKET);
}

TEST(Lexer, Strings) {
    std::string src{"\"str\""};
    ton::Lexer lexer{};
    lexer.load_from_string(std::move(src));
    auto token = lexer.next_token();
    ASSERT_EQ(token.type, ton::Token_Type::STRING);
    ASSERT_STREQ(token.value.c_str(), "str");
}

TEST(Lexer, Integers) {
    std::string src{"200"};
    ton::Lexer lexer{};
    lexer.load_from_string(std::move(src));
    auto token = lexer.next_token();
    ASSERT_EQ(token.type, ton::Token_Type::INTEGER);
    ASSERT_STREQ(token.value.c_str(), "200");
}

TEST(Lexer, Floats) {
    std::string src{"3.4"};
    ton::Lexer lexer{};
    lexer.load_from_string(std::move(src));
    auto token = lexer.next_token();
    ASSERT_EQ(token.type, ton::Token_Type::FLOAT);
    ASSERT_STREQ(token.value.c_str(), "3.4");
}

TEST(Lexer, Identifiers) {
    std::string src{"Kappa"};
    ton::Lexer lexer{};
    lexer.load_from_string(std::move(src));
    auto token = lexer.next_token();
    ASSERT_EQ(token.type, ton::Token_Type::IDENTIFIER);
    ASSERT_STREQ(token.value.c_str(), "Kappa");
}

