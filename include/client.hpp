#ifndef OPC_UA_DEMO_CLIENT_HPP
#define OPC_UA_DEMO_CLIENT_HPP

#include <open62541/client.h>
#include <string_view>

namespace demo {
    class Client {
    public:
        Client();
        ~Client();

        [[nodiscard]] auto get_client() const -> UA_Client *;
        [[nodiscard]] auto connect(std::string_view url) const -> UA_StatusCode;

    private:
        UA_Client *_client;
    };
}// namespace demo

#endif//OPC_UA_DEMO_CLIENT_HPP
