#ifndef FILETYPEREGISTER_H
#define FILETYPEREGISTER_H
#include"cxxweb/file/fileconntenttyperegister.h"
namespace CxxWeb
{



std::string FileConntentTypeRegister::get(std::string & path) const 
{
    if(path.empty())
    {
        return "*/*";
    }
    size_t pos = path.find('.',  path.size() < max_size_exeption  ? 0 : path.size() - max_size_exeption ); 
    if(pos==std::string::npos)
    {
        return "*/*";
    }
    auto  it = types.find(path.substr(pos+1));
    if(it==types.end())
    {
        return "*/*";
    }
    return (*it).second;

}
   
   

FileConntentTypeRegister::FileConntentTypeRegister()
{
    
      types = {
        {"html", "text/html"},
        {"htm",  "text/html"},
        {"css",  "text/css"},
        {"js",   "application/javascript"},
        {"json", "application/json"},
        {"xml",  "application/xml"},

        {"png",  "image/png"},
        {"jpg",  "image/jpeg"},
        {"jpeg", "image/jpeg"},
        {"gif",  "image/gif"},
        {"webp", "image/webp"},
        {"svg",  "image/svg+xml"},
        {"bmp",  "image/bmp"},
        {"ico",  "image/x-icon"},

        {"mp4",  "video/mp4"},
        {"webm", "video/webm"},
        {"avi",  "video/x-msvideo"},
        {"mov",  "video/quicktime"},

        {"mp3",  "audio/mpeg"},
        {"wav",  "audio/wav"},
        {"ogg",  "audio/ogg"},

        {"zip",  "application/zip"},
        {"gz",   "application/gzip"},
        {"rar",  "application/vnd.rar"},
        {"7z",   "application/x-7z-compressed"},

        {"pdf",  "application/pdf"},
        {"txt",  "text/plain"},
        {"csv",  "text/csv"},
        {"md",   "text/markdown"},

        {"doc",  "application/msword"},
        {"docx","application/vnd.openxmlformats-officedocument.wordprocessingml.document"},
        {"xls", "application/vnd.ms-excel"},
        {"xlsx","application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"},

        {"ttf",  "font/ttf"},
        {"otf",  "font/otf"},
        {"woff", "font/woff"},
        {"woff2","font/woff2"}
    };
    max_size_exeption = 6;
}

}
#endif
