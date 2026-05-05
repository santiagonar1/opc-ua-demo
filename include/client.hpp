#ifndef OPC_UA_DEMO_CLIENT_HPP
#define OPC_UA_DEMO_CLIENT_HPP

#include <open62541/client.h>

namespace demo {
    class Client {
    public:
        Client();
        ~Client();

        [[nodiscard]] auto get_client() const -> UA_Client *;

    private:
        UA_Client *client;
    };
}// namespace demo

#endif//OPC_UA_DEMO_CLIENT_HPP
