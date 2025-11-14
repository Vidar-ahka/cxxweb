// tests/fileengine_realdata_fs_test.cpp
#include <gtest/gtest.h>
#include <string>
#include <unordered_map>
#include <filesystem>
#include "cxxweb/file/fileengine.h"
#include "cxxweb/data/bytearray.h"

using namespace CxxWeb;
namespace fs = std::filesystem;

class FileEngineRealDataFSTest : public ::testing::Test {
protected:
    fs::path path_template;
    fs::path path_static;
    std::unique_ptr<FileEngine> engine;

    void SetUp() override {
        path_template = fs::path("/home/tamer/cpp_project/server_http/template");
        path_static   = fs::path("/home/tamer/cpp_project/server_http/static");


        std::string tmpl_str = path_template.string();
        std::string static_str = path_static.string();
        engine = std::make_unique<FileEngine>(tmpl_str, static_str);
    }

    void TearDown() override {
        engine.reset();
    }
};

TEST_F(FileEngineRealDataFSTest, LoadPlainTemplate) {
    std::string rel = "/template1.html"; 
    ByteArray data = engine->getTemplate(rel);
    ASSERT_FALSE(data.empty()) << "template1.html не загружен";

    std::string html(data.data(), data.size());
    EXPECT_NE(html.find("<html"), std::string::npos);
    EXPECT_NE(html.find("</html>"), std::string::npos);
}

TEST_F(FileEngineRealDataFSTest, LoadTemplateWithKeys) {
    std::string rel = "/template2.html"; 

    std::unordered_map<std::string, std::string> keys;
    keys["name"] = "Tamer";
    keys["title"] = "Welcome";

    ByteArray data = engine->getTemlate(rel, keys); 
    ASSERT_FALSE(data.empty()) << "template2.html не загружен";

    std::string html(data.data(), data.size());
    EXPECT_NE(html.find("Tamer"), std::string::npos);
    EXPECT_NE(html.find("Welcome"), std::string::npos);
}

TEST_F(FileEngineRealDataFSTest, LoadStaticFile) {
    std::string rel =  "/images.png"; 
    ByteArray data = engine->getStatic(rel); 
    ASSERT_FALSE(data.empty()) << "images.png не найден или пуст";


    EXPECT_EQ(static_cast<unsigned char>(data[0]), 0x89);
    EXPECT_EQ(static_cast<unsigned char>(data[1]), 0x50);
    EXPECT_EQ(static_cast<unsigned char>(data[2]), 0x4E);
    EXPECT_EQ(static_cast<unsigned char>(data[3]), 0x47);
}
