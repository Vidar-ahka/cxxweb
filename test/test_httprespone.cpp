#include <gtest/gtest.h>
#include "cxxweb/respone/httprespone.h"
#include "cxxweb/data/bytearray.h"

using namespace CxxWeb;

TEST(HTTPResponeTest, DefaultConstructorSetsDefaults) {
    HTTPRespone resp;

    EXPECT_EQ(resp.getData().size(), 0);
    const std::string& headers = resp.getHeaders();
    EXPECT_NE(headers.find("HTTP/1.1 200 OK"), std::string::npos);
    EXPECT_NE(headers.find("Content-Type:"), std::string::npos);
    EXPECT_NE(headers.find("Content-Length: 0"), std::string::npos);
}

TEST(HTTPResponeTest, ConstructorWithByteArray) {
    ByteArray body;
    body.write("Hello, world!");
    HTTPRespone resp(body);
    
    EXPECT_EQ(resp.getData().size(), 13);
    std::string headers = resp.getHeaders();
    EXPECT_NE(headers.find("HTTP/1.1 200 OK"), std::string::npos);
    EXPECT_NE(headers.find("Content-Length: 13"), std::string::npos);
}

TEST(HTTPResponeTest, ConstructorWithByteArrayAndContentType) {
    ByteArray body;
    body.write("Test Data");

    HTTPRespone resp(body, "application/json");

    std::string headers = resp.getHeaders();

    EXPECT_NE(headers.find("Content-Type: application/json"), std::string::npos);
    EXPECT_NE(headers.find("Content-Length: 9"), std::string::npos);
}

TEST(HTTPResponeTest, FullConstructorSetsAllFields) {
    ByteArray body;
    body.write("<html>OK</html>");
    HTTPRespone resp(body, "text/html", "HTTP/2.0", "404", "Not Found");
    
    std::string headers = resp.getHeaders();
    EXPECT_NE(headers.find("HTTP/2.0 404 Not Found"), std::string::npos);
    EXPECT_NE(headers.find("Content-Type: text/html"), std::string::npos);
    EXPECT_NE(headers.find("Content-Length: 15"), std::string::npos);
}

TEST(HTTPResponeTest, SettersUpdateHeadersProperly) {
    ByteArray body;
    body.write("Body");
    HTTPRespone resp(body, "text/plain");

    resp.setVersion("HTTP/3.0");
    resp.setStatusCode("500");
    resp.setStatusMessage("Internal Server Error");
    resp.setContentType("application/xml");

    std::string headers = resp.getHeaders();
    EXPECT_NE(headers.find("HTTP/3.0 500 Internal Server Error"), std::string::npos);
    EXPECT_NE(headers.find("Content-Type: application/xml"), std::string::npos);
    EXPECT_NE(headers.find("Content-Length: 4"), std::string::npos);
}

TEST(HTTPResponeTest, SetDataUpdatesContentLength) {
    ByteArray body;
    body.write("Short");
    HTTPRespone resp;
    resp.setData(body);

    std::string headers = resp.getHeaders();
    EXPECT_NE(headers.find("Content-Length: 5"), std::string::npos);

    ByteArray newBody;
    newBody.write("Longer body content");
    resp.setData(newBody);

    std::string updated = resp.getHeaders();
    EXPECT_NE(updated.find("Content-Length: 19"), std::string::npos);
}

TEST(HTTPResponeTest, GetHeadersCachesResultUntilModified) {
    ByteArray body;
    body.write("CacheTest");
    HTTPRespone resp(body);

    std::string first = resp.getHeaders();
    std::string second = resp.getHeaders();
    EXPECT_EQ(first, second) << "Header string should be cached until new_data = true";

    resp.setStatusCode("201");
    std::string third = resp.getHeaders();
    EXPECT_NE(first, third) << "After modification, header should rebuild";
}
