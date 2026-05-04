#include "server.hpp"

namespace demo {
    Server::Server() : server{UA_Server_new()} {}

    Server::~Server() { UA_Server_delete(server); }

    auto Server::get_server() const -> UA_Server * { return server; }
}// namespace demo