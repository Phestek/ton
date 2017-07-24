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


