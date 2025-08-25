#include <gtest/gtest.h>
#include "cxxweb/data/bytearray.h"

using namespace CxxWeb;

TEST(ByteArrayTest, DefaultConstructorCreatesEmpty) {
    ByteArray b;
    EXPECT_TRUE(b.empty());
    EXPECT_EQ(b.size(), 0u);
}


TEST(ByteArrayTest, ConstructFromCString) {
    const char* str = "hello";
    ByteArray b(str);
    EXPECT_FALSE(b.empty());
    EXPECT_EQ(b.size(), strlen(str));
    EXPECT_EQ(std::string(b.data(), b.size()), "hello");
}

 
TEST(ByteArrayTest, CopyConstructorSharesData) {
    ByteArray b1("abc");
    ByteArray b2(b1);
    EXPECT_EQ(b1.size(), b2.size());
    EXPECT_EQ(std::string(b1.data(), b1.size()), std::string(b2.data(), b2.size()));
}

TEST(ByteArrayTest, MoveConstructorTransfersData) {
    ByteArray b1("xyz");
    ByteArray b2(std::move(b1));
    EXPECT_EQ(std::string(b2.data(), b2.size()), "xyz");
    EXPECT_TRUE(b1.empty() || b1.data() == nullptr);  // b1 в "moved-from"
}

TEST(ByteArrayTest, CopyAssignmentCopiesContent) {
    ByteArray b1("123");
    ByteArray b2;
    b2 = b1;
    EXPECT_EQ(std::string(b2.data(), b2.size()), "123");
}

TEST(ByteArrayTest, MoveAssignmentTransfersOwnership) {
    ByteArray b1("qwe");
    ByteArray b2;
    b2 = std::move(b1);
    EXPECT_EQ(std::string(b2.data(), b2.size()), "qwe");
}

TEST(ByteArrayTest, WriteOverwritesData) {
    ByteArray b("first");
    b.write("second");
    EXPECT_EQ(std::string(b.data(), b.size()), "second");
}

TEST(ByteArrayTest, AppendAppendsData) {
    ByteArray b("hi");
    b.append(" there");
    EXPECT_EQ(std::string(b.data(), b.size()), "hi there");
}

TEST(ByteArrayTest, PushBackAddsOneChar) {
    ByteArray b("ab");
    b.push_back('c');
    EXPECT_EQ(std::string(b.data(), b.size()), "abc");
}

TEST(ByteArrayTest, ReserveIncreasesCapacity) {
    ByteArray b("foo");
    size_t oldCap = b.capacity();
    b.reserve(oldCap + 50);
    EXPECT_GE(b.capacity(), oldCap + 50);
}

TEST(ByteArrayTest, CopyOnWriteTriggered) {
    ByteArray b1("test");
    ByteArray b2(b1); // shared data
    b1.write("new");  // copy-on-write
    EXPECT_EQ(std::string(b1.data(), b1.size()), "new");
    EXPECT_EQ(std::string(b2.data(), b2.size()), "test");
}


