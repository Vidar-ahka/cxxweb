#include <gtest/gtest.h>
#include <fstream>
#include <cstdio> // std::remove
#include "cxxweb/file/staticfilereader.h"

using namespace CxxWeb;

// вспомогательная функция для создания временного файла
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
