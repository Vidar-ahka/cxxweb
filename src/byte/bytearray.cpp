#include"cxxweb/byte/bytearray.h"

namespace CxxWeb
{
    
void  ByteArray::reserve(size_t new_capacity)
{
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
    return  data_ptr->empty();
}
size_t ByteArray::size()const
{
    return data_ptr->size();
}
size_t ByteArray::capacity()const
{
    return  data_ptr->capacity();
}
const char * ByteArray::data()  const 
{
    return data_ptr->data();
}


}