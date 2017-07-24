#include <gtest/gtest.h>

#include "ton/document.h"
#include <iostream>

TEST(Document, Add_New_Integer_Value) {
    ton::Document doc{};
    ASSERT_NO_THROW(doc["int"] = 10);
    ASSERT_EQ(doc["int"].as<ton::Integer>(), 10);
}

TEST(Document, Add_New_Float_Value) {
    ton::Document doc{};
    ASSERT_NO_THROW(doc["float"] = 2.1);
    ASSERT_EQ(doc["float"].as<ton::Float>(), 2.1);
}

TEST(Document, Add_New_String_Value) {
    ton::Document doc{};
    ASSERT_NO_THROW(doc["str"] = "asdf");
    ASSERT_STREQ(doc["str"].as<ton::String>().c_str(), "asdf");
}

TEST(Document, Add_New_Object_Value) {
    ton::Document doc{};
    ASSERT_NO_THROW(doc["obj"] = {});
}

