
#include"cxxweb/file/staticfilereader.h"

namespace CxxWeb
{

    StaticFileReader::StaticFileReader()
    {
     
        stream = std::make_unique<std::ifstream>();
    }    
    StaticFileReader::StaticFileReader(std::string & file_path) : StaticFileReader()
    {
        this->file_path = file_path;
    }
    StaticFileReader::~StaticFileReader()
    {
        close();
    }
    
    StaticFileReader::StaticFileReader(StaticFileReader && other)
    {
        move(std::move(other));
    }
    
    StaticFileReader & StaticFileReader::operator=(StaticFileReader && other)
    {
         move(std::move(other));
         return *this;
    }
    void StaticFileReader::move(StaticFileReader&&  other)
    {
        pos   = other.pos;
        size_ = other.size_;
        file_path = std::move(other.file_path);
        stream    = std::move(other.stream);
        
        
        other.size_ = 0;
        other.pos   = 0;
    }
    bool StaticFileReader::open()
    {
        try 
        {
           
            if(file_path.empty())
            {
               throw std::runtime_error("StaticFileReader::open  file_path  empty ");

            }
            stream->open(file_path);
            if(!stream->is_open())
            {
               throw std::runtime_error("StaticFileReader::open  file: " + file_path +" dont open");
            }
            stream->seekg(0,std::ios::end);
            size_ = stream->tellg();
            stream->seekg(pos, std::ios::beg);
            return stream->is_open();
        }
        catch(std::exception & e)
        {
            std::cerr<<e.what()<<'\n';
            return false;
        }
    }
    bool StaticFileReader::open(const std::string  & file_path)
    {
        
        this->file_path =  file_path;
        return open();
    }
    bool StaticFileReader::close()
    {
        if(is_open())
        {
            stream->close();
        }
        return true;
    }
    ByteArray StaticFileReader::readAll()
    {
     
        return read(size_);
    } 
    
    ByteArray StaticFileReader::read(size_t size)
    {

        ByteArray tmp;
        if(!is_open())
        {
            return tmp;
        }
        size = std::min(size,size_-pos);
        tmp.resize(size);
        stream->read(const_cast<char*>(tmp.data()),size);
        tmp.resize(stream->gcount());
        pos =  pos+tmp.size();
        return tmp;
    } 

    void  StaticFileReader::reload()
    {
        pos = 0;
        if(is_open())
        {
            close();
            open();
        }
    }

    bool StaticFileReader::endread() 
    {
     
        return  !stream ||  pos >= size_;
    }
        
    

        
    bool StaticFileReader::is_open() const  
    {
        return stream&& stream->is_open();
    }
    bool StaticFileReader::empty() const 
    {
        return  size_ == 0;
    }
        
    size_t StaticFileReader::size() const 
    {
        return size_;
    }                 
    std::string  StaticFileReader::path()  const 
    {
        return file_path;
    }


}
