
#ifndef ICONNECTIONFACTORY
#define ICONNECTIONFACTORY

#include"iconnection.h"
namespace CxxWeb
{
    class IConnectionFactory {
    public:
        virtual ~IConnectionFactory() = default;    
        virtual std::shared_ptr<IConnection> create() = 0;
        virtual bool is_valid() = 0 ;
    };
}

#endif