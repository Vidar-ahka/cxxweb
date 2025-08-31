
#include"cxxweb/file/staticfilereader.h"

namespace CxxWeb
{

    StaticFileReader::StaticFileReader(std::string & file_path) : file_path(file_path)
    {

    }
    StaticFileReader::~StaticFileReader()
    {
        close();
    }

    bool StaticFileReader::open()
    {
        try 
        {
           
            if(file_path.empty())
            {
               throw std::runtime_error("StaticFileReader::open  file_path  empty ");

            }
            stream.open(file_path);
            if(!stream.is_open())
            {
               throw std::runtime_error("StaticFileReader::open  file" + file_path +" dont open");
            }
            stream.seekg(0,std::ios::end);
            size_ = stream.tellg();
            stream.seekg(0 , std::ios::beg);
            return stream.is_open();
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
            stream.close();
        }
        return true;
    }
        
    bool StaticFileReader::is_open() const  
    {
        return stream.is_open();
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
