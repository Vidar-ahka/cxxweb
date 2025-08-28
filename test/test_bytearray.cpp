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


TEST(ByteArrayResizeTest, ResizeNoOpWhenSameSize) {
    ByteArray b("hello");
    size_t old_size = b.size();
    b.resize(old_size);
    EXPECT_EQ(b.size(), old_size);
    EXPECT_EQ(std::string(b.data(), b.size()), "hello");
    }
    
TEST(ByteArrayResizeTest, ResizeShorterTruncatesData) {
        ByteArray b("abcdef");
        b.resize(3);
        EXPECT_EQ(b.size(), 3);
        EXPECT_EQ(std::string(b.data(), b.size()), "abc");
        }

        
TEST(ByteArrayResizeTest, ResizeLongerAddsZeros) {
    ByteArray b("xyz");
    b.resize(6);
    EXPECT_EQ(b.size(), 6);
    // первые 3 символа "xyz", остальные нули
    EXPECT_EQ(std::string(b.data(), 3), "xyz");
    EXPECT_EQ(b.data()[3], '\0');
    EXPECT_EQ(b.data()[4], '\0');
    EXPECT_EQ(b.data()[5], '\0');
}

TEST(ByteArrayResizeTest, ResizeTriggersCopyOnWrite) {
    ByteArray b1("copyme");
    ByteArray b2(b1);  // shared data
    b1.resize(3);      // b1 обрезается, b2 должен остаться нетронутым
    EXPECT_EQ(std::string(b1.data(), b1.size()), "cop");
    EXPECT_EQ(std::string(b2.data(), b2.size()), "copyme");
}


TEST(ByteArrayOperatorIndexTest, ModifyUniqueData) {
    ByteArray b("abc");
    b[0] = 'x';
    b[1] = 'y';
    b[2] = 'z';

    EXPECT_EQ(std::string(b.data(), b.size()), "xyz");
}

TEST(ByteArrayOperatorIndexTest, CopyOnWriteSharedData) {
    ByteArray b1("abc");
    ByteArray b2(b1);  // use_count() > 1

    b1[0] = 'x';  // должен создать копию
    b1[1] = 'y';
    b1[2] = 'z';

    // b1 изменён
    EXPECT_EQ(std::string(b1.data(), b1.size()), "xyz");

    // b2 остался нетронутым
    EXPECT_EQ(std::string(b2.data(), b2.size()), "abc");
}

TEST(ByteArrayOperatorIndexTest, NoChangeOnOtherSharedData) {
    ByteArray b1("hello");
    ByteArray b2(b1);
    ByteArray b3(b1);

    b2[0] = 'H';  // copy-on-write триггерится для b2
    b3[1] = 'E';  // copy-on-write триггерится для b3

    // b1 не должен измениться
    EXPECT_EQ(std::string(b1.data(), b1.size()), "hello");

    // b2 и b3 независимы
    EXPECT_EQ(std::string(b2.data(), b2.size()), "Hello");
    EXPECT_EQ(std::string(b3.data(), b3.size()), "hEllo");
}

TEST(ByteArrayOperatorIndexTest, AccessOutOfBounds) {
    ByteArray b("abc");

    // Проверка границ – здесь UB, но можем проверить чтение/запись в пределах size
    EXPECT_NO_THROW({
        char c = b[0];
        b[2] = 'z';
    });
}