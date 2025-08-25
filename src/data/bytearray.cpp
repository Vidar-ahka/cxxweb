#include"cxxweb/data/bytearray.h"

namespace CxxWeb
{
ByteArray::ByteArray() noexcept
{
   data_ptr = std::make_shared<bytes>();

}
ByteArray::ByteArray(const char * data) : ByteArray()   
{
    write(data);
}


ByteArray::ByteArray( const ByteArray & other) noexcept
{
 
    data_ptr = other.data_ptr;
    
}

ByteArray::ByteArray(ByteArray && byte) noexcept 
{
        data_ptr = byte.data_ptr;
        byte.data_ptr = NULL;
}

ByteArray::~ByteArray()
{

}

ByteArray &  ByteArray::operator=(const ByteArray & other) noexcept
{
    if(this !=  &other)
    {
        this->write( other);
    }
    return *this;
}

ByteArray &  ByteArray::operator=(ByteArray && other)noexcept
{
    if(this != &other )
    {
        data_ptr = std::move(other.data_ptr);
    }
    return *this;

}



void  ByteArray::write(const ByteArray &byte)
{
    if(!data_ptr||this==&byte)
    {
        return;
    }
    data_ptr  = byte.data_ptr;
}
void  ByteArray::write(const char *  byte)
{
    write(byte,strlen(byte));
}    

void  ByteArray::write(const char *  byte , size_t size)
{   
    if(!data_ptr||size == 0 )
    {
        return;
    }
    copy_write(size);
    data_ptr->assign(byte,byte+size);
}




void  ByteArray::append( const ByteArray & byte)
{ 
    if(!data_ptr||byte.empty())
    {
        return;
    }
    size_t s  = byte.size()+data_ptr->size();
    copy_append(s);
    data_ptr->insert(data_ptr->end(),byte.data_ptr->begin(),byte.data_ptr->end());
}

void  ByteArray::append(const char * byte)
{
    append(byte,strlen(byte));
}

void  ByteArray::append(const char * byte, size_t  size)
{

    if(!data_ptr||size==0)
    {
        return ;
    }
    size_t s = size+data_ptr->size();
    copy_append(s);
    data_ptr->insert(data_ptr->end(),byte,byte+size);
}

void  ByteArray::push_back(char val)
{
    if(data_ptr.use_count()>1)
    {
        size_t s  = data_ptr->size() + 1;
        copy_append(s);
    }
    data_ptr->push_back(val);
}





void  ByteArray::reserve(size_t new_capacity)
{
    if(!data_ptr)
    {
        return ;
    }
    if(new_capacity != data_ptr->capacity())
    {    
        if(data_ptr.use_count()>1)
        {
            std::shared_ptr<bytes> new_data_ptr  = std::make_shared<bytes>();
            new_data_ptr->reserve(new_capacity);
            new_data_ptr->assign(data_ptr->begin(), 
            (data_ptr->size()<=new_capacity ? data_ptr->end() : data_ptr->begin()+ new_capacity));
            data_ptr =  new_data_ptr ;
        }   
        else 
        {
            data_ptr->reserve(new_capacity);
        }
    }
    
}


bool  ByteArray::empty() const
{
    if(!data_ptr)
    {
        return false;
    }
    return  data_ptr->empty();
}
size_t ByteArray::size()const
{
    if(!data_ptr)
    {
        return 0;
    }
    return data_ptr->size();
}
size_t ByteArray::capacity()const
{
    if(!data_ptr)
    {
        return 0;
    }
    return  data_ptr->capacity();
}
const char * ByteArray::data()  const 
{
    if(!data_ptr)
    {
        return nullptr;
    }
    return data_ptr->data();
}

bool ByteArray::copy_write(size_t & size)
{
    if(data_ptr.use_count()>1)
    {
        std::shared_ptr<bytes> new_data_ptr = std::make_shared<bytes>();
        if(size<data_ptr->capacity())
        {
            new_data_ptr->reserve(data_ptr->capacity());    
        }
        
        data_ptr = new_data_ptr;
        return true;
    }
    return false;
}    

bool ByteArray::copy_append(size_t & size)
{
    
    if(data_ptr.use_count()>1)
    {
        std::shared_ptr<bytes> new_data_ptr = std::make_shared<bytes>();
        if(size<data_ptr->size())
        {
            new_data_ptr->reserve(data_ptr->capacity());     
        }
        else 
        {
            new_data_ptr->reserve(size+(size/2));
        }
        new_data_ptr->assign(data_ptr->begin(),data_ptr->end());
        data_ptr = new_data_ptr;
        return true;
    }
    return false;
}



}