#include"cxxweb/net/sslconnection.h"


namespace CxxWeb
{

    SSLConnection::SSLConnection()
    {
        ctx = nullptr;
        ssl_ = nullptr;
    }
    SSLConnection::SSLConnection(const int & server_socket , SSL_CTX *  ctx) :  
    server_socket(server_socket)  , ctx(ctx)
    {
        start();
    }
    SSLConnection::~SSLConnection()
    {
        stop();
    }
    bool SSLConnection::start(const int & server_socket , SSL_CTX *  ctx)
    {
        stop();
        this->ctx = ctx;
        this->server_socket  = server_socket;
        return  start();
    }   
    bool SSLConnection::start()
    {


        try
        {   
            if(!ctx )
            {
                  throw std::runtime_error("SSL context is null");
            }
            socket_ = accept(server_socket, nullptr, nullptr);
        
            if (socket_ < 0) 
            {
                 throw std::runtime_error("Accept failed, error code: " + std::to_string(errno));
            }

            ssl_ = SSL_new(ctx);
            SSL_set_fd(ssl_, socket_);
           
            if(!ssl_)
            {
                throw std::runtime_error("SSL_new failed");
            }
            if (SSL_accept(ssl_) <= 0) 
            {
                int ssl_error = SSL_get_error(ssl_, -1);
                throw std::runtime_error("SSL_accept failed, error code: " + std::to_string(ssl_error));
            } 
       
        
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
        return true;
        

    }  
    bool SSLConnection::stop()
    {
        if(ssl_)
        {
            SSL_shutdown(ssl_);
            SSL_free(ssl_);
        }
        close(socket_);
        return true;
    }


    ByteArray  SSLConnection::readAll() 
    {
        try
        {
            if(!ssl_)
            {
                throw std::runtime_error("SSLConnection::readAll called on invalid SSL connection\n");
            }
            ByteArray byte;
            byte.reserve(8193);
            int count = 0 ;
            do
            {
                char buffer[4096];
                count  = SSL_read(ssl_,buffer,4096);
                byte.append(buffer);

            }while(count>=4096);
            return byte;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return ByteArray();
        }
        
    }
    ByteArray  SSLConnection::read(size_t read_size) 
    {
        try
        {
            if(!ssl_)
            {
                throw std::runtime_error("SSLConnection::read called on invalid SSL connection\n");
            }
            if(read_size == 0)
            {
                return ByteArray();
            }
            ByteArray byte;
            byte.resize(read_size);
            int  count = SSL_read(ssl_,const_cast<char*>(byte.data()),read_size);
            byte.resize(count);        
            
            return byte;        
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return ByteArray();
        }
        
       
    }
    

   
   
}