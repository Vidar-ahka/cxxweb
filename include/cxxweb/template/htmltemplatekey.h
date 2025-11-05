#ifndef HTMLTEMPLATEKEY_H
#define HTMLTEMPLATEKEY_H
#include"unordered_map"
#include"cxxweb/data/bytearray.h"
#include"stack"
#include"list"

namespace CxxWeb
{
    struct Node
    {
        ByteArray data;
        std::string key;
        bool is_key;
    };
    class HTMLTemplateKey
    {   
    public:
        HTMLTemplateKey() = default;
        HTMLTemplateKey(ByteArray data_html);
        ByteArray get(std::unordered_map<std::string , std::string > & keys);
        void setDataHtml(ByteArray data_html);


    private:
      
        std::list<Node> nodes_list;
        std::pair<int,int> valid_key(std::string_view & str, int open , int close);
        void    add_to_bytearray(ByteArray  & byte, int open , int close);
        size_t  size_data{0};
        

    };
}

#endif