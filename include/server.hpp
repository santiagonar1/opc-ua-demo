#ifndef OPC_UA_DEMO_SERVER_HPP
#define OPC_UA_DEMO_SERVER_HPP

#include <open62541/server.h>

namespace demo {
    class Server {
    public:
        Server();
        ~Server();

        [[nodiscard]] auto get_server() const -> UA_Server *;
        [[nodiscard]] auto run_until_interrupt() const -> UA_StatusCode;
        [[nodiscard]] auto add_variable_node(const UA_NodeId &node_id, const UA_NodeId &parent_id,
                                             const UA_QualifiedName &browse_name,
                                             const UA_VariableAttributes &attributes) const
                -> UA_StatusCode;

    private:
        UA_Server *server;
    };
}// namespace demo

#endif//OPC_UA_DEMO_SERVER_HPP
