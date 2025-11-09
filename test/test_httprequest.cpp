#include <gtest/gtest.h>
#include "cxxweb/request/httprequest.h"
#include "cxxweb/data/bytearray.h"

using namespace CxxWeb;

TEST(HTTPRequestTest, ConstructorWithByteArray) {
    ByteArray request;
    request.write("GET /index.html?user=alice HTTP/1.1\nHost: example.com\n");
    HTTPRequest req(request);

    EXPECT_EQ(req.getMethod(), "GET");
    EXPECT_EQ(req.getPath(), "/index.html");
    EXPECT_EQ(req.getVersion(), "HTTP/1.1");
    EXPECT_EQ(req.getHeader("Host"), "example.com");
    EXPECT_TRUE(req.hasHeader("Host"));
    EXPECT_FALSE(req.hasHeader("Authorization"));
}
TEST(HTTPRequestTest, AddDataWithByteArray) {
    HTTPRequest req;
    ByteArray request;
    request.write("POST /submit?name=Bob HTTP/2.0\nContent-Type: text/plain\n");
    req.addData(request);

    EXPECT_EQ(req.getMethod(), "POST");
    EXPECT_EQ(req.getPath(), "/submit");
    EXPECT_EQ(req.getVersion(), "HTTP/2.0");
    EXPECT_EQ(req.getHeader("Content-Type"), "text/plain");
    }

TEST(HTTPRequestTest, AddDataWithStdString) {
    HTTPRequest req;
    std::string request = "HEAD /status?check=yes HTTP/1.0\nUser-Agent: TestAgent\n";
    req.addData(request);

    EXPECT_EQ(req.getMethod(), "HEAD");
    EXPECT_EQ(req.getPath(), "/status");
    EXPECT_EQ(req.getVersion(), "HTTP/1.0");
    EXPECT_EQ(req.getHeader("User-Agent"), "TestAgent");
}
    
TEST(HTTPRequestTest, EmptyKeyReturnsEmpty) {
    HTTPRequest req;
    std::string request = "GET / HTTP/1.1\nHost: test.com\n";
    req.addData(request);

    EXPECT_EQ(req.getHeader(""), "");
    EXPECT_FALSE(!req.hasHeader(""));
}
