#include <gtest/gtest.h>
#include <fstream>
#include <cstdio> 
#include "cxxweb/file/staticfilereader.h"

using namespace CxxWeb;


static std::string createTempFile(const std::string& name, const std::string& content) {
    std::ofstream ofs(name, std::ios::trunc);
    ofs << content;
    ofs.close();
    return name;
}

TEST(StaticFileReaderTest, OpenNonexistentFileFails) {
    std::string path = "nonexistent_file_123456.txt";
    StaticFileReader reader(path);
    EXPECT_FALSE(reader.open());
    EXPECT_FALSE(reader.is_open());
    EXPECT_TRUE(reader.empty());
    EXPECT_EQ(reader.size(), 0);
}

TEST(StaticFileReaderTest, OpenValidFileSucceeds) {
    std::string filename = "temp_test_file.txt";
    std::string content = "Hello, StaticFileReader!";
    createTempFile(filename, content);

    StaticFileReader reader(filename);
    EXPECT_TRUE(reader.open());
    EXPECT_TRUE(reader.is_open());
    EXPECT_FALSE(reader.empty());
    EXPECT_EQ(reader.size(), content.size());
    EXPECT_EQ(reader.path(), filename);

    reader.close();
    EXPECT_FALSE(reader.is_open());

    std::remove(filename.c_str()); // очистка
}

TEST(StaticFileReaderTest, EmptyFileReportsEmpty) {
    std::string filename = "empty_file.txt";
    createTempFile(filename, "");

    StaticFileReader reader(filename);
    EXPECT_TRUE(reader.open());
    EXPECT_TRUE(reader.is_open());
    EXPECT_TRUE(reader.empty());
    EXPECT_EQ(reader.size(), 0);

    std::remove(filename.c_str());
}

TEST(StaticFileReaderTest, OpenViaOverloadedMethod) {
    std::string filename = "temp_test_file2.txt";
    std::string content = "12345";
    createTempFile(filename, content);

    StaticFileReader reader; // default constructor
    EXPECT_TRUE(reader.open(filename));
    EXPECT_TRUE(reader.is_open());
    EXPECT_EQ(reader.size(), content.size());
    EXPECT_EQ(reader.path(), filename);

    std::remove(filename.c_str());
}

TEST(StaticFileReaderTest, CloseClosesStream) {
    std::string filename = "temp_test_file3.txt";
    createTempFile(filename, "close test");

    StaticFileReader reader(filename);
    ASSERT_TRUE(reader.open());
    ASSERT_TRUE(reader.is_open());

    reader.close();
    EXPECT_FALSE(reader.is_open());

    std::remove(filename.c_str());
}



TEST(StaticFileReaderReadTest, ReadAllReadsWholeFile) {
    std::string filename = "readall_test.txt";
    std::string content = "Hello ReadAll!";
    createTempFile(filename, content);

    StaticFileReader reader(filename);
    ASSERT_TRUE(reader.open());

    ByteArray data = reader.readAll();
    EXPECT_EQ(std::string(data.data(), data.size()), content);

    // повторный вызов возвращает тот же буфер
    ByteArray data2 = reader.readAll();
    EXPECT_EQ(std::string(data2.data(), data2.size()), content);

    reader.close();
    std::remove(filename.c_str());
}

TEST(StaticFileReaderReadTest, ReadChunksSequentially) {
    std::string filename = "readchunk_test.txt";
    std::string content = "abcdefghij";
    createTempFile(filename, content);

    StaticFileReader reader(filename);
    ASSERT_TRUE(reader.open());

    ByteArray chunk1 = reader.read(4); // читаем первые 4 символа
    EXPECT_EQ(std::string(chunk1.data(), chunk1.size()), "abcd");

    ByteArray chunk2 = reader.read(3); // читаем следующие 3
    EXPECT_EQ(std::string(chunk2.data(), chunk2.size()), "efg");

    ByteArray chunk3 = reader.read(10); // пытаемся прочитать больше, чем осталось
    EXPECT_EQ(std::string(chunk3.data(), chunk3.size()), "hij");

    reader.close();
    std::remove(filename.c_str());
}

TEST(StaticFileReaderReadTest, ReadFromClosedFileReturnsEmpty) {
    std::string filename = "closedfile_test.txt";
    createTempFile(filename, "12345");

    StaticFileReader reader(filename);
    EXPECT_FALSE(reader.readAll().size()); // до открытия — пусто
    EXPECT_FALSE(reader.read(3).size());

    reader.open();
    reader.close();

    EXPECT_TRUE(reader.readAll().empty());
    EXPECT_TRUE(reader.read(5).empty());

    std::remove(filename.c_str());
}

TEST(StaticFileReaderReadTest, ReadAllAndRead) {
    std::string filename = "closedfile_test.txt";
    createTempFile(filename, "12345");
    StaticFileReader reader(filename);
    reader.open();
    ByteArray byte = reader.readAll();
    EXPECT_EQ(byte.data(), reader.read(5).data());
    reader.close();
    std::remove(filename.c_str());
}

TEST(StaticFileReaderReadTest, ReadAndReadAll) {
    std::string filename = "closedfile_test.txt";
    std::string content = "123455678";
    createTempFile(filename, content);
    StaticFileReader reader(filename);
    reader.open();
    
    ByteArray byte = reader.read(4);
    byte = reader.readAll();
    EXPECT_EQ(std::string(byte.data(),byte.size()),content);
    reader.close();
    std::remove(filename.c_str());
}

TEST(StaticFileReaderMoveSemantics, MoveConstructor) {
    std::string content = "abc123";
    std::string path = createTempFile("move_ctor.txt", content);

    StaticFileReader r1(path);
    ASSERT_TRUE(r1.open());
    EXPECT_TRUE(r1.is_open());
    EXPECT_EQ(r1.size(), content.size());

    // вызов конструктора перемещения
    StaticFileReader r2(std::move(r1));

    // r2 перенял все ресурсы
    EXPECT_EQ(r2.path(), path);
    EXPECT_TRUE(r2.is_open());
    EXPECT_EQ(r2.size(), content.size());
    EXPECT_EQ(std::string(r2.readAll().data(), r2.readAll().size()), content);

    // r1 сброшен
    EXPECT_EQ(r1.size(), 0);
    EXPECT_FALSE(r1.is_open());
    EXPECT_EQ(r1.path(), "");
}

TEST(StaticFileReaderMoveSemantics, MoveAssignment) {
    std::string content = "hello world";
    std::string path = createTempFile("move_assign.txt", content);

    StaticFileReader r1(path);
    ASSERT_TRUE(r1.open());

    StaticFileReader r2;
    r2 = std::move(r1); // оператор присваивания перемещением

    // r2 получил ресурсы
    EXPECT_EQ(r2.path(), path);
    EXPECT_TRUE(r2.is_open());
    EXPECT_EQ(r2.size(), content.size());
    EXPECT_EQ(std::string(r2.readAll().data(), r2.readAll().size()), content);

    // r1 очищен
    EXPECT_EQ(r1.size(), 0);
    EXPECT_FALSE(r1.is_open());
    EXPECT_EQ(r1.path(), "");
}

TEST(StaticFileReaderMoveSemantics, MoveEmptyReader) {
    StaticFileReader r1;
    StaticFileReader r2(std::move(r1));

    EXPECT_EQ(r2.size(), 0);
    EXPECT_FALSE(r2.is_open());
    EXPECT_EQ(r2.path(), "");
    EXPECT_EQ(r1.size(), 0);
}