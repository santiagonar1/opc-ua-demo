#ifndef OPC_UA_DEMO_SERVER_HPP
#define OPC_UA_DEMO_SERVER_HPP

#include <open62541/server.h>

namespace demo {
    class Server {
    public:
        Server();
        ~Server();

        [[nodiscard]] auto get_server() const -> UA_Server *;

    private:
        UA_Server *server;
    };
}// namespace demo

#endif//OPC_UA_DEMO_SERVER_HPP
