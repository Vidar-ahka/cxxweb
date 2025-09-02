#include <gtest/gtest.h>
#include "cxxweb/file/staticfilereader.h"
#include <fstream>

using namespace CxxWeb;


static std::string createTempFile(const std::string& name, const std::string& content) {
    std::ofstream ofs(name, std::ios::binary);
    ofs << content;
    return name;
}

TEST(StaticFileReaderTest, OpenNonexistentFileFails) {
    std::string path = "nonexistent.txt";
    StaticFileReader reader(path);
    EXPECT_FALSE(reader.open());
    EXPECT_FALSE(reader.is_open());
    EXPECT_TRUE(reader.empty());

    std::remove(path.c_str());

}

TEST(StaticFileReaderTest, OpenAndReadAll) {
    std::string content = "HelloWorld";
    std::string path = createTempFile("test_readall.txt", content);

    StaticFileReader reader(path);
    ASSERT_TRUE(reader.open());
    EXPECT_TRUE(reader.is_open());
    EXPECT_EQ(reader.size(), content.size());

    ByteArray data = reader.readAll();
    EXPECT_EQ(std::string(data.data(), data.size()), content);
    EXPECT_TRUE(reader.endread());

    std::remove(path.c_str());

}

TEST(StaticFileReaderTest, ReadInChunks) {
    std::string content = "ABCDEFGH";
    std::string path = createTempFile("test_chunks.txt", content);

    StaticFileReader reader(path);
    ASSERT_TRUE(reader.open());

    ByteArray chunk1 = reader.read(3);
    EXPECT_EQ(std::string(chunk1.data(), chunk1.size()), "ABC");
    EXPECT_FALSE(reader.endread());

    ByteArray chunk2 = reader.read(3);
    EXPECT_EQ(std::string(chunk2.data(), chunk2.size()), "DEF");
    EXPECT_FALSE(reader.endread());

    ByteArray chunk3 = reader.read(3);
    EXPECT_EQ(std::string(chunk3.data(), chunk3.size()), "GH");
    EXPECT_TRUE(reader.endread());

    std::remove(path.c_str());

}




TEST(StaticFileReaderTest, ReloadResetsPosition) {
    std::string content = "XYZ";
    std::string path = createTempFile("test_reload.txt", content);

    StaticFileReader reader(path);
    ASSERT_TRUE(reader.open());

    ByteArray first = reader.read(2);
    EXPECT_EQ(std::string(first.data(), first.size()), "XY");
    EXPECT_FALSE(reader.endread());

    reader.reload();
    EXPECT_FALSE(reader.endread());  // после reload pos == 0, но файл открыт

    ByteArray again = reader.readAll();
    EXPECT_EQ(std::string(again.data(), again.size()), "XYZ");
    EXPECT_TRUE(reader.endread());
    
    std::remove(path.c_str());

}

TEST(StaticFileReaderTest, MoveConstructorTransfersOwnership) {
    std::string content = "MOVE";
    std::string path = createTempFile("test_move_ctor.txt", content);

    StaticFileReader r1(path);
    ASSERT_TRUE(r1.open());

    StaticFileReader r2(std::move(r1));
    EXPECT_TRUE(r2.is_open());
    EXPECT_EQ(r2.size(), content.size());
    ByteArray byte = r2.readAll() ;
    EXPECT_EQ(std::string(byte.data(), byte.size()), content);
    EXPECT_EQ(r1.size(), 0);
    EXPECT_FALSE(r1.is_open());

    std::remove(path.c_str());


}

TEST(StaticFileReaderTest, MoveAssignmentTransfersOwnership) {
    std::string content = "ASSIGN";
    std::string path = createTempFile("test_move_assign.txt", content);

    StaticFileReader r1(path);
    ASSERT_TRUE(r1.open());

    StaticFileReader r2;
    r2 = std::move(r1);

    EXPECT_TRUE(r2.is_open());
    EXPECT_EQ(r2.size(), content.size());
    EXPECT_EQ(std::string(r2.readAll().data(), r2.size()), content);

    EXPECT_EQ(r1.size(), 0);
    EXPECT_FALSE(r1.is_open());
    
    std::remove(path.c_str());

}



TEST(StaticFileReaderTest, ReadThenReadAll) {
    std::string content = "ABCDEFGHIJ";
    std::string path = createTempFile("test_read_then_readall.txt", content);
    
    StaticFileReader reader(path);
    ASSERT_TRUE(reader.open());


    ByteArray part = reader.read(4);

    EXPECT_EQ(std::string(part.data(), part.size()), "ABCD");
    EXPECT_FALSE(reader.endread());
    
    ByteArray part2 = reader.read(2);
    
    EXPECT_EQ(std::string(part2.data(), part2.size()), "EF");
    EXPECT_FALSE(reader.endread());
    
    
    ByteArray all = reader.readAll();
    EXPECT_EQ(std::string(all.data(), all.size()), "GHIJ");
    EXPECT_TRUE(reader.endread());
    
    
    std::remove(path.c_str());
    
}

TEST(StaticFileReaderTest, OpenAndReadAllCleanup) {
    std::string content = "12345";
    std::string path = createTempFile("test_cleanup.txt", content);
    
    StaticFileReader reader(path);
    ASSERT_TRUE(reader.open());
    
    ByteArray data = reader.readAll();
    EXPECT_EQ(std::string(data.data(), data.size()), content);
    EXPECT_TRUE(reader.endread());
    
    std::remove(path.c_str());
}
    