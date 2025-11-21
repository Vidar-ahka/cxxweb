
#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <filesystem>

#include "cxxweb/router/router.h"
#include "cxxweb/file/fileengine.h"
#include "cxxweb/data/bytearray.h"
#include "cxxweb/request/httprequest.h"
#include "cxxweb/respone/httprespone.h"
#include"cxxweb/respone/httpresponerender.h"

using namespace CxxWeb;
namespace fs = std::filesystem;

class RouterRealDataFSTest : public ::testing::Test {
protected:
    fs::path path_template;
    fs::path path_static;
    std::shared_ptr<FileEngine> engine;
    std::unique_ptr<Router> router;
    std::shared_ptr<HTTPResponeRender> render_respone;

    void SetUp() override {
        path_template = fs::path("/home/tamer/cpp_project/server_http/template");
        path_static   = fs::path("/home/tamer/cpp_project/server_http/static");
        engine = std::make_shared<FileEngine>(path_template.string(), path_static.string());
        render_respone = std::make_shared<HTTPResponeRender>(engine);
        router = std::make_unique<Router>(render_respone);

    }

    void TearDown() override {
        router.reset();
        engine.reset();
    }
    std::shared_ptr<HTTPRespone> render(HTTPRequest & request,std::string path_file_template)
    {
        std::string path =  request.getPath();
        /*ByteArray data  =  engine->getTemplate(path_file_template);
        std::shared_ptr<HTTPRespone> respone = std::make_shared<HTTPRespone>();
        respone->setData(data);
        respone->setContentType(FileConntentTypeRegister::instanse().get(path_file_template));
        respone->setVersion(request.getVersion());
        respone->setStatusCode("200");
        respone->setStatusMessage("OK");      
        */
        return render_respone->renderTemplate(request,path_file_template);  
    }
  
};

// Тест на статический файл
TEST_F(RouterRealDataFSTest, RouteStaticFile) {
    HTTPRequest request(ByteArray("GET /images.png HTTP/1.1\r\n\r\n"));

    auto response = router->get(request);
    
    ByteArray data = response->getData();
    ASSERT_FALSE(data.empty());
    EXPECT_EQ(static_cast<unsigned char>(data[0]), 0x89); // PNG magic bytes
    EXPECT_EQ(static_cast<unsigned char>(data[1]), 0x50);
    EXPECT_EQ(static_cast<unsigned char>(data[2]), 0x4E);
    EXPECT_EQ(static_cast<unsigned char>(data[3]), 0x47);

    EXPECT_NE(response->getHeaders().find("Content-Type: image/png"), std::string::npos);
}

// Тест на добавление кастомного обработчика
TEST_F(RouterRealDataFSTest, RouteCustomHandler) {
    router->addHandler("/custom", [](HTTPRequest& req) {
        ByteArray data;
        data.write("Hello, Router!");
        return std::make_shared<HTTPRespone>(data, "text/plain");
    });

    HTTPRequest request;
    request.addData(ByteArray("GET /custom HTTP/1.1\r\n\r\n"));

    auto response = router->get(request);
    ASSERT_TRUE(response);

    std::string body(response->getData().data(), response->getData().size());
    EXPECT_EQ(body, "Hello, Router!");

    EXPECT_NE(response->getHeaders().find("Content-Type: text/plain"), std::string::npos);
}


TEST_F(RouterRealDataFSTest, RouteNotFoundReturnsEmpty) {
    HTTPRequest request;
    request.addData(ByteArray("GET /test.png HTTP/1.1\r\n\r\n"));
    auto response = router->get(request);
    ByteArray data  = response->getData();
    EXPECT_TRUE(data.empty());
}

TEST_F(RouterRealDataFSTest, RouterHandelUserRender) 
{
    HTTPRequest request;
    std::string test = "/test";
    request.addData(ByteArray("GET /test HTTP/1.1\r\nContent-Type: text/html\r\n\r\n"));
    router->addHandler(test,[&](HTTPRequest & requse ) ->std::shared_ptr<HTTPRespone>
    {
       return  render(request,"/template1.html");
    });
    std::string path = "/template1.html";
    std::shared_ptr <HTTPRespone> respone = router->get(request);
    ByteArray data_1 = respone->getData();
    ByteArray data_2 = engine->getTemplate(path);
    EXPECT_EQ(std::string(data_1.data(),data_1.size()), std::string(data_2.data(),data_2.size()));
    
    std::string type = FileConntentTypeRegister::instanse().get(path);
    std::string headers = respone->getHeaders(); 
    EXPECT_TRUE(headers.find(type) != std::string::npos);
    EXPECT_TRUE(headers.find("200") != std::string::npos);
    EXPECT_TRUE(headers.find("OK") != std::string::npos);
    EXPECT_TRUE(headers.find("HTTP/1.1") != std::string::npos);
}





