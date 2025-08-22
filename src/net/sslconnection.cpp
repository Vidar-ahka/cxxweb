#include"cxxweb/net/sslconnection.h"


namespace CxxWeb
{
    SSLConnection::SSLConnection(const int & server_socket ,  SSL_CTX  *   ctx)
    {
        
        valid = false;
        socket_ = accept(server_socket, nullptr, nullptr);
        
        if (socket_ < 0) {
            throw "socket_ < 0 \n";

        }
            
        ssl_ = SSL_new(ctx);
        SSL_set_fd(ssl_, socket_);
        if (SSL_accept(ssl_) <= 0) 
        {
         
            throw "ssl_ acceptr <= 0 \n";
                 
        } 
        
        valid = true;
    }
    SSLConnection::~SSLConnection()
    {
        if(ssl_)
        {
        SSL_shutdown(ssl_);
        SSL_free(ssl_);
        }
        close(socket_);    

    }
         
    size_t  SSLConnection :: send(const ByteArray & byte)  
    {
        if(!valid)
        {
            return 0;
        }
        std::cout <<"send "<< byte.data();
        return SSL_write(ssl_,byte.data(),byte.size());
    }
    ByteArray SSLConnection :: readall()  
    {
        
        if(!valid)
        {
            return ByteArray();
        }
        ByteArray result;
        result.reserve(8202);
        int count = 0;
        do
        {
           char buffer[4097];
           count = SSL_read(ssl_,buffer,4096);
           buffer[count] = '\0';
           result.append(buffer,4096);

        } while (count > 4096);
  
        return result;
        
    }

    ByteArray SSLConnection :: read(size_t read_size)
    {
        if(!valid)
        {
            return ByteArray();
        }
        ByteArray result;
        result.resize(read_size+1);
        int count = SSL_read(ssl_,const_cast<char*>(result.data()),read_size);
        
        return result;
    }

    int  SSLConnection :: getSocket()  
    {
        return socket_;
    }
    bool SSLConnection :: is_valid() 
    {
        return valid;
    }
}