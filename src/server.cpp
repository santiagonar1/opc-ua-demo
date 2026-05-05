#include "server.hpp"

namespace demo {
    Server::Server() : server{UA_Server_new()} {}

    Server::~Server() { UA_Server_delete(server); }

    auto Server::get_server() const -> UA_Server * { return server; }

    auto Server::run_until_interrupt() const -> UA_StatusCode {
        return UA_Server_runUntilInterrupt(server);
    }

    auto Server::add_variable_node(const UA_NodeId &node_id, const UA_NodeId &parent_id,
                                   const UA_QualifiedName &browse_name,
                                   const UA_VariableAttributes &attributes) const -> UA_StatusCode {
        return UA_Server_addVariableNode(server, node_id, parent_id, UA_NS0ID(ORGANIZES),
                                         browse_name, UA_NODEID_NULL, attributes, nullptr, nullptr);
    }
}// namespace demo