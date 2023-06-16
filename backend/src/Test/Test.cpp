#include <gtest/gtest.h>
#include "src/Handler/TestHandler.hpp"
#include <sstream>

TEST(TEST_TEST, TestOfTest){
    EXPECT_EQ(1, 1);
}

TEST(Handler_Test, TestHandler){
    std::stringstream ss;
    using namespace  FruitsGroove;
    TestHandler th{ss};
    th.Handle("test");
    th.Handle("hoge");
    th.Handle("fuga");
    th.Handle("piyo");
    EXPECT_EQ(ss.str(), "testhogefugapiyo");
}
