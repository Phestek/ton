#include <gtest/gtest.h>

#include "ton/parser.h"

TEST(Parser, Simple_Integer) {
    std::string src{"int = 10"};
    ton::Document doc{};
    doc.load_from_string(std::move(src));
    ASSERT_NO_THROW(doc["int"].as<ton::Integer>());
    ASSERT_EQ(doc["int"].as<ton::Integer>(), 10);
}

TEST(Parser, Simple_Float) {
    std::string src{"float = 1.2"};
    ton::Document doc{};
    doc.load_from_string(std::move(src));
    ASSERT_NO_THROW(doc["float"].as<ton::Float>());
    ASSERT_EQ(doc["float"].as<ton::Float>(), 1.2);
}

TEST(Parser, Simple_String) {
    std::string src{"str = \"asdf\""};
    ton::Document doc{};
    doc.load_from_string(std::move(src));
    ASSERT_NO_THROW(doc["str"].as<ton::String>());
    ASSERT_STREQ(doc["str"].as<ton::String>().c_str(), "asdf");
}

TEST(Parser, Empty_Object) {
    std::string src{"obj {}"};
    ton::Document doc{};
    doc.load_from_string(std::move(src));
    ASSERT_NO_THROW(doc["obj"].as<ton::Object>());
    ASSERT_EQ(doc["obj"].as<ton::Object>().num_members(), 0);
}

TEST(Parser, Array_Of_Ints) {
    std::string src{"array = [ 10, 20, 30 ]"};
    ton::Document doc{};
    doc.load_from_string(std::move(src));
    ASSERT_NO_THROW(doc["array"].as<ton::Array>());
    ASSERT_EQ(doc["array"].as<ton::Array>().size(), 3);
    ASSERT_EQ(doc["array"].as<ton::Array>()[0], 10);
    ASSERT_EQ(doc["array"].as<ton::Array>()[1], 20);
    ASSERT_EQ(doc["array"].as<ton::Array>()[2], 30);
}

TEST(Parser, Nester_Array) {
    std::string src{"array = [ [ 10, 20, 30 ], [ 10, 20, 30, 40 ] ]"};
    ton::Document doc{};
    doc.load_from_string(std::move(src));
    ASSERT_NO_THROW(doc["array"].as<ton::Array>());
    ASSERT_EQ(doc["array"].as<ton::Array>().size(), 2);
    ASSERT_EQ(std::get<ton::Array>(doc["array"].as<ton::Array>()[0]).size(), 3);
    ASSERT_EQ(std::get<ton::Array>(doc["array"].as<ton::Array>()[1]).size(), 4);
}

