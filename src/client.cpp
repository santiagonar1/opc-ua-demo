#include "client.hpp"

#include <open62541/client_config_default.h>
#include <open62541/client_highlevel.h>

namespace demo {
    Client::Client() : client(UA_Client_new()) {
        UA_ClientConfig_setDefault(UA_Client_getConfig(client));
    }

    Client::~Client() { UA_Client_delete(client); }

    auto Client::get_client() const -> UA_Client * { return client; }
}// namespace demo