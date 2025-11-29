# CxxWeb

Простая библиотека для HTTPS серверов на C++.  

## Пример кода

```cpp

#include"iostream"
#include"unordered_map"
#include"cxxweb/app.h"
int main()
{

    CxxWeb::App app;
    uint16_t port = 1235;
    std::cout <<port;

    app.setPort(port);
    app.setPathCert("path/to/certificate.pem");
    app.setPathPrivateKey("path/to/private_key.pem");
    app.setPathTemplates("path/to/templates");
    app.setPathStaticFile("path/to/static/files");

    
    app.addHandler("/",[&](CxxWeb::HTTPRequest & request)->std::shared_ptr<CxxWeb::HTTPRespone> 
    {
        std::string path = "/template1.html";
        return app.render->renderTemplate(request,path);
    });
    app.addHandler("/context",[&](CxxWeb::HTTPRequest & request)->std::shared_ptr<CxxWeb::HTTPRespone> 
    {
        std::string path = "/template2.html";
        std::unordered_map<std::string , std::string > context{{"key_in_html", "value" }};
        return app.render->renderTemplate(request,path,context);
    });
    if(!app.start())
    {
        return 0;
    }
    while(true)
    {
        std::cout <<"poll \n";
        app.poll();
    }
    return 0;
}

```
## Пример CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.10)
project(meta)
set(CMAKE_CXX_STANDARD 17)

find_package(cxxweb REQUIRED)
find_package(OpenSSL REQUIRED)

add_executable(meta main.cpp)
target_link_libraries(meta PRIVATE cxxweb::cxxweb)
```

## Зависимости

-CMake

-OpenSSL

## Установка зависимостей

В дистрибутивах  Ubuntu/Debian необходимые зависимости можно установить командой:

```sh
sudo apt install g++ make cmake libssl-dev
```

## Установка библиотеки на Linux


Скомпилировать и установить библиотеку можно с помощью следующих команд:

```sh
git clone https://github.com/Vidar-ahka/cxxweb.git
cd cxxweb
mkdir build && cd build
cmake ..
make 
sudo make install
```




