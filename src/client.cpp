#include "client.hpp"

#include <open62541/client_config_default.h>
#include <open62541/client_highlevel.h>

namespace demo {
    Client::Client() : _client(UA_Client_new()) {
        UA_ClientConfig_setDefault(UA_Client_getConfig(_client));
    }

    Client::~Client() { UA_Client_delete(_client); }

    auto Client::get_client() const -> UA_Client * { return _client; }

    auto Client::connect(const std::string_view url) const -> UA_StatusCode {
        return UA_Client_connect(_client, url.data());
    }
}// namespace demo