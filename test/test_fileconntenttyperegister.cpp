#include <gtest/gtest.h>
#include "cxxweb/file/fileconntenttyperegister.h"
using namespace CxxWeb;

TEST(FileContentTypeRegisterTest, Html) {
   
    
    std::string path = "index.html";  
    EXPECT_EQ(FileConntentTypeRegister::instanse().get(path), "text/html");
}

TEST(FileContentTypeRegisterTest, BigPath) {
    
    std::string path_png = "index/image.png";
    std::string path_css =  "index/style.css";
    
    EXPECT_EQ(FileConntentTypeRegister::instanse().get(path_css), "text/css");
    EXPECT_EQ(FileConntentTypeRegister::instanse().get(path_png), "image/png");
}

TEST(FileContentTypeRegisterTest,js) {
    std::string ext = "script.js";
    EXPECT_EQ(FileConntentTypeRegister::instanse().get(ext), "application/javascript");
}

TEST(FileContentTypeRegisterTest, pdf) {
    std::string path = "document.pdf";
    EXPECT_NE(FileConntentTypeRegister::instanse().get(path), "text/html");
}


TEST(FileContentTypeRegisterTest, woff2) {
    std::string path = "document.woff2";
    EXPECT_EQ(FileConntentTypeRegister::instanse().get(path), "font/woff2");
}

