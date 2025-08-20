#ifndef BYTEARRAY_H
#define BYTEARRAY_H

#include"algorithm"
#include"iostream"
#include"vector"
#include"cstring"
#include"memory"

namespace CxxWeb
{
    
    class ByteArray
    {

    public:
        ByteArray() noexcept;
        ~ByteArray();

        void  write(const ByteArray &byte);
        void  write(const char *  byte);
        void  write(const char *  byte , size_t size);


        void  reserve(size_t new_capacity);
        void  resize(size_t new_size);
        bool  empty() const;
        size_t size() const;
        size_t capacity()    const;
        const  char * data() const;
        
    private:
        bool copy_write (size_t & size);
        using bytes  = std::vector<char>;
        std::shared_ptr<bytes> data_ptr;
    };
    
}
#endif
