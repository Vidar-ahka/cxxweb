#ifndef IFILEREADER_H
#define IFILEREADER_H
#include"cxxweb/data/ireader.h"
namespace CxxWeb
{
    class IFileReader : public IReader
    {
    public:
        virtual ~IFileReader() = default;
        virtual bool open()    = 0; 
        virtual bool open(const std::string  & str)    = 0;
        virtual void  reload()    = 0 ;
        

        virtual bool close()   = 0;
        
        virtual bool is_open() const  = 0;
        virtual bool empty()   const = 0;
        virtual bool endread()    = 0 ;
        
      
        virtual size_t size() const = 0;                 
        virtual std::string  path() const  = 0;

    };

}

#endif