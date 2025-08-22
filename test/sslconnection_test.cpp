#include <gtest/gtest.h>
#include "cxxweb/net/sslconnection.h"

using namespace CxxWeb;
using ::testing::Return;

// --- Mock обертка для OpenSSL ---
class MockSSL {
public:
    MOCK_METHOD(int, SSL_accept, (SSL*), ());
    MOCK_METHOD(int, SSL_write, (SSL*, const void*, int), ());
    MOCK_METHOD(int, SSL_read, (SSL*, void*, int), ());
};

static MockSSL* g_mockSSL = nullptr;

// Подменяем глобальные C-функции OpenSSL
extern "C" {
    SSL* SSL_new(SSL_CTX* ctx) {
        return reinterpret_cast<SSL*>(0x1234); // фейковый ptr
    }
    void SSL_set_fd(SSL* ssl, int fd) { (void)ssl; (void)fd; }
    int SSL_accept(SSL* ssl) { return g_mockSSL->SSL_accept(ssl); }
    int SSL_write(SSL* ssl, const void* buf, int num) { return g_mockSSL->SSL_write(ssl, buf, num); }
    int SSL_read(SSL* ssl, void* buf, int num) { return g_mockSSL->SSL_read(ssl, buf, num); }
}

// --- Fixture ---
class SSLConnectionTest : public ::testing::Test {
protected:
    SSL_CTX* ctx = reinterpret_cast<SSL_CTX*>(0x1111); // фейковый контекст

    void SetUp() override {
        g_mockSSL = new MockSSL();
    }
    void TearDown() override {
        delete g_mockSSL;
        g_mockSSL = nullptr;
    }
};

// --- Тесты ---

TEST_F(SSLConnectionTest, InvalidSocketOnAccept) {
    // accept() вернет -1 => объект должен быть невалидный
    int fakeServerSocket = -1;
    SSLConnection conn(fakeServerSocket, ctx);
    EXPECT_FALSE(conn.is_valid());
}

TEST_F(SSLConnectionTest, ValidConnection) {
    // эмулируем успешное SSL_accept
    EXPECT_CALL(*g_mockSSL, SSL_accept(::testing::_))
        .WillOnce(Return(1));

    // accept() должен вернуть socket>0 (тут фейкуем через dup(0))
    int fds[2];
    socketpair(AF_UNIX, SOCK_STREAM, 0, fds);
    int server_socket = fds[0];
    int client_socket = fds[1];

    SSLConnection conn(server_socket, ctx);

    EXPECT_TRUE(conn.is_valid());
    close(server_socket);
    close(client_socket);
}

TEST_F(SSLConnectionTest, SendWhenInvalid) {
    SSLConnection conn(-1, ctx);
    EXPECT_EQ(conn.send(ByteArray()), 0);
}

TEST_F(SSLConnectionTest, SendWorks) {
    EXPECT_CALL(*g_mockSSL, SSL_accept(::testing::_)).WillOnce(Return(1));
    EXPECT_CALL(*g_mockSSL, SSL_write(::testing::_, ::testing::_, ::testing::_))
        .WillOnce(Return(5));

    int fds[2];
    socketpair(AF_UNIX, SOCK_STREAM, 0, fds);
    SSLConnection conn(fds[0], ctx);

    ByteArray data;
    data.write("hello", 5);
    EXPECT_EQ(conn.send(data), 5);

    close(fds[0]);
    close(fds[1]);
}

TEST_F(SSLConnectionTest, ReadAllWorks) {
    EXPECT_CALL(*g_mockSSL, SSL_accept(::testing::_)).WillOnce(Return(1));
    EXPECT_CALL(*g_mockSSL, SSL_read(::testing::_, ::testing::_, 4096))
        .WillOnce(Return(3))
        .WillRepeatedly(Return(4096)); // завершить цикл

    int fds[2];
    socketpair(AF_UNIX, SOCK_STREAM, 0, fds);
    SSLConnection conn(fds[0], ctx);

    ByteArray result = conn.readall();
    EXPECT_FALSE(result.empty());

    close(fds[0]);
    close(fds[1]);

}
