#include <gtest/gtest.h>

#include "ton/element.h"

TEST(Element, Integer) {
    ton::Element i{"integer", 10};
    ASSERT_EQ(i.as<ton::Integer>(), 10);
}

TEST(Element, Integer_Reassignment) {
    ton::Element i{"integer", 10};
    ASSERT_NO_THROW(i = 20);
    ASSERT_EQ(i.as<ton::Integer>(), 20);
}

TEST(Element, Float) {
    ton::Element f{"float", 10.5};
    ASSERT_EQ(f.as<ton::Float>(), 10.5);
}

TEST(Element, Float_Reassignment) {
    ton::Element f{"integer", 10.5};
    ASSERT_NO_THROW(f = 20.2);
    ASSERT_EQ(f.as<ton::Float>(), 20.2);
}

TEST(Element, String) {
    ton::Element s{"str", "test"};
    ASSERT_STREQ(s.as<ton::String>().c_str(), "test");
}

TEST(Element, String_Reassignment) {
    ton::Element s{"integer", "test"};
    ASSERT_NO_THROW(s = "tset");
    ASSERT_STREQ(s.as<ton::String>().c_str(), "tset");
}

TEST(Element, Object) {
    ton::Element o{"str", ton::Object{std::vector<ton::Element>{}}};
}

TEST(Element, Integer_Comparison_Equals) {
    ton::Element val{"val", 10};
    ASSERT_EQ(val, 10);
}

TEST(Element, Integer_Comparison_Not_Equals) {
    ton::Element val{"val", 10};
    ASSERT_NE(val, 20);
}

TEST(Element, Float_Comparison_Equals) {
    ton::Element val{"val", 1.0};
    ASSERT_EQ(val, 1.0);
}

TEST(Element, Float_Comparison_Not_Equals) {
    ton::Element val{"val", 1.0};
    ASSERT_NE(val, 2.0);
}

//TEST(Element, String_Comparison_Equals) {
    //ton::Element val{"val", "asdf"};
    //ASSERT_EQ(val, "asdf");
//}

//TEST(Element, String_Comparison_Not_Equals) {
    //ton::Element val{"val", "asdf"};
    //ASSERT_NE(val, "fdsa");
//}

