#include <gtest/gtest.h>
#include "cxxweb/data/parserhttprequest.h"
#include "cxxweb/data/bytearray.h"

using namespace CxxWeb;

TEST(ParserHTTPRequestTest, ConstructorWithByteArray) {
    ByteArray request;
    request.write("GET /index.html?user=alice&lang=en HTTP/1.1\nHost: example.com\n");
    ParserHTTPRequest parser(request);

    EXPECT_EQ(parser.getMethod(), "GET");
    EXPECT_EQ(parser.getVersion(), "HTTP/1.1");

    auto args = parser.getArgument();
    ASSERT_EQ(args.size(), 2);
    EXPECT_EQ(std::string(args[0].first), "user");
    EXPECT_EQ(std::string(args[0].second), "alice");
    EXPECT_EQ(std::string(args[1].first), "lang");
    EXPECT_EQ(std::string(args[1].second), "en");
}

TEST(ParserHTTPRequestTest, ParseWithStdString) {
    ParserHTTPRequest parser;
    std::string request = "POST /submit?name=Bob&age=30 HTTP/2.0\nContent-Type: application/json\n";
    parser.parse(request);

    EXPECT_EQ(parser.getMethod(), "POST");
    EXPECT_EQ(parser.getVersion(), "HTTP/2.0");

    auto args = parser.getArgument();
    ASSERT_EQ(args.size(), 2);
    EXPECT_EQ(std::string(args[0].first), "name");
    EXPECT_EQ(std::string(args[0].second), "Bob");
    EXPECT_EQ(std::string(args[1].first), "age");
    EXPECT_EQ(std::string(args[1].second), "30");
}

TEST(ParserHTTPRequestTest, ParseWithByteArray) {
    ByteArray request;
    request.write("GET /status?check=yes HTTP/1.0\n");
    ParserHTTPRequest parser;
    parser.parse(request);

    EXPECT_EQ(parser.getMethod(), "GET");
    EXPECT_EQ(parser.getVersion(), "HTTP/1.0");

    auto args = parser.getArgument();
    ASSERT_EQ(args.size(), 1);
    EXPECT_EQ(std::string(args[0].first), "check");
    EXPECT_EQ(std::string(args[0].second), "yes");
}

TEST(ParserHTTPRequestTest, GetHeaderValue) {
    ParserHTTPRequest parser;
    std::string request = "GET / HTTP/1.1\nHost: localhost\nUser-Agent: TestAgent\n";
    parser.parse(request);

    auto host = parser.get("Host", ":");
    auto ua = parser.get("User-Agent", ":");

    EXPECT_EQ(std::string(host), "localhost");
    EXPECT_EQ(std::string(ua), "TestAgent");
}

TEST(ParserHTTPRequestTest, GetMissingHeaderReturnsEmpty) {
    ParserHTTPRequest parser;
    std::string request = "GET / HTTP/1.1\nHost: example.com\n";
    parser.parse(request);

    auto val = parser.get("Authorization", ":");
    EXPECT_TRUE(val.empty());
}

TEST(ParserHTTPRequestTest, GetHeaderWithoutSeparatorReturnsEmpty) {
    ParserHTTPRequest parser;
    std::string request = "X-Custom-Header value\n";
    parser.parse(request);

    auto val = parser.get("X-Custom-Header", ":"); 
    EXPECT_TRUE(val.empty());
}

TEST(ParserHTTPRequestTest, GetHeaderWithoutNewlineReturnsEmpty) {
    ParserHTTPRequest parser;
    std::string request = "Host: example.com";  
    parser.parse(request);

    auto val = parser.get("Host", ":");
    EXPECT_TRUE(val.empty());
}



