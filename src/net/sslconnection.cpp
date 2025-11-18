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

    SSLConnection::SSLConnection(SSLConnection && other)
    {
        move_from(std::move(other));
    }   
    SSLConnection & SSLConnection::operator=(SSLConnection && other)
    {
        move_from(std::move(other));
        return *this;
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
 
            if(!ctx )
            {
                std::cout << "SSL context is null";
                return false;
            }
            
            len = sizeof(s_addr);
            socket_ = accept(server_socket,(sockaddr*)&s_addr,&len);
        
            if (socket_ < 0) 
            {
                std::cout <<"Accept failed, error code: " <<  std::to_string(errno)<<'\n';
                return false;
            }

            ssl_ = SSL_new(ctx);
            SSL_set_fd(ssl_, socket_);
           
            if(!ssl_)
            {
                std::cout <<"SSL_new failed";
                return false;
            }
            if (SSL_accept(ssl_) <= 0) 
            {
                int ssl_error = SSL_get_error(ssl_, -1);
                std::cout << "SSL_accept failed, error code: " << ssl_error <<'\n';
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
            ssl_ = nullptr;
        }
        close(socket_);
        return true;
    }


    ByteArray  SSLConnection::readAll() 
    {
        if(!check_fun_try("readAll"))
        {
            return ByteArray();
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
    ByteArray  SSLConnection::read(size_t read_size) 
    {
        
       
        if(!check_fun_try("read")&&read_size == 0)
        {
            return ByteArray();
        }
        ByteArray byte;
        byte.resize(read_size);
        int  count = SSL_read(ssl_,const_cast<char*>(byte.data()),read_size);
        byte.resize(count);        
            
        return byte;        
      
        
       
    }

    size_t  SSLConnection::write(ByteArray byte) 
    {    
        if(!check_fun_try("write")&&byte.empty())
        {
               return 0;
        }
        int count =   SSL_write(ssl_,byte.data(),byte.size());
        return count;
       
    }
    size_t  SSLConnection::write(const std::string & str)
    {
        if(!check_fun_try("write")&&str.empty())
        {
               return 0;
        }
        int count =   SSL_write(ssl_,str.c_str(),str.size());
        return count;        
    }
    
    int  SSLConnection::getSocket() const  
    {
        return socket_;
    }
    bool  SSLConnection::is_valid()  const  
    {
        return  socket_>-1 &&  ssl_valid();  
    }
    bool SSLConnection::ssl_valid() const
    {
        return ssl_ && SSL_get_current_cipher(ssl_) != nullptr 
        && SSL_get_fd(ssl_) > -1 && SSL_is_init_finished(ssl_);
    }

    bool SSLConnection::check_fun_try(std::string  name_fun)
    {
        if(socket_<0)
        {
            std::cout <<"SSLConnection::" + name_fun+ " called on invalid socket < 0 \n"; 
            return false;

        }
        if(!ssl_valid())
        {
            std::cout <<"SSLConnection::"+name_fun+" called on invalid SSL connection\n";
            return false;
        }
        return true;
    }
       
    void SSLConnection::move_from(SSLConnection&& other)
    {
        server_socket = other.server_socket;
        ctx = other.ctx;
        s_addr = other.s_addr;
        len = other.len;
        ssl_ = other.ssl_;

        other.server_socket = -1;
        other.socket_ = -1;
        other.ctx  = nullptr;
        other.ssl_ = nullptr;

    }
       

   
   
}