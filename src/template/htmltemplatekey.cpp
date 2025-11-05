#include"cxxweb/template/htmltemplatekey.h"

namespace CxxWeb
{
    HTMLTemplateKey::HTMLTemplateKey(ByteArray data_html)
    {
        
    }
    void HTMLTemplateKey::setDataHtml(ByteArray data_html)
    {
        if(data_html.empty())
        {
            return  ;
        }
        int  beg = 0;
        int  open  =  0;
        int  close = data_html.size();
        size_data = data_html.size();
        size_t i = 0;     
        std::string_view str(data_html.data(),data_html.size());
        std::string find_str = "{";
        while(i<str.size())
        {
            if((open = str.find("{{",i) ) == std::string::npos)
            {
                break;
            }
            else if((close = str.find("}}",open+2) ) == std::string::npos)
            {
                break;
            }
            std::pair<int,int> keys  = valid_key(str,open+2,close);
            if(keys.first > -1 && keys.second>-1)
            {
                Node html;
                html.data = data_html.copy(beg,open);
                html.is_key = false;
                nodes_list.push_back(html);

                Node key;
                ByteArray data_key = data_html.copy(keys.first,keys.second); 
                key.key =   std::string(data_key.data(),data_key.size());
                key.is_key  = true;
                nodes_list.push_back(key);  
                beg = close+2;
            }
            i = close +2;
        }
        if(beg<data_html.size())
        {
            Node html;
            html.data = data_html.copy(beg,data_html.size());
            html.is_key = false;
            nodes_list.push_back(html);
        }
        

        
        

    }
   
    std::pair<int,int> HTMLTemplateKey::valid_key(std::string_view & str, int open , int close)
    {
       int count = 0;
       int beg = open;
       int end = close;
       while(open < close)
       {    
         if(str[open] != ' ')
         {
            if(++count >=2)
            {
                return {-1,-1};
            }
            beg = open;
            while(open<close && str[open] !=' ')
            {
                ++open;
            }
            end = open;
         }
         else 
         {
            ++open;
         }
       }
       return {beg,end};
    }
                
  
}

       