#ifndef OPC_UA_DEMO_CLIENT_HPP
#define OPC_UA_DEMO_CLIENT_HPP

#include <open62541/client.h>
#include <open62541/client_highlevel.h>

#include <expected>
#include <string>
#include <string_view>

#include "variant.hpp"

namespace demo {
    class Client {
    public:
        Client();
        ~Client();

        [[nodiscard]] auto get_client() const -> UA_Client *;
        [[nodiscard]] auto connect(std::string_view url) const -> UA_StatusCode;

        template<typename T>
        [[nodiscard]] auto read_attribute_custom_node(std::string id)
                -> std::expected<T, UA_StatusCode>;

    private:
        UA_Client *_client;
    };

    template<typename T>
    [[nodiscard]] auto Client::read_attribute_custom_node(std::string id)
            -> std::expected<T, UA_StatusCode> {
        auto variant = make_variant();
        constexpr auto namespace_index = 1;
        if (const auto status = UA_Client_readValueAttribute(
                    _client, UA_NODEID_STRING(namespace_index, id.data()), &variant);
            status != UA_STATUSCODE_GOOD or
            not UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_INT32])) {
            return std::unexpected(status);
        }

        const auto data = extract_value<int32_t>(variant).value();
        UA_Variant_clear(&variant);

        return data;
    }
}// namespace demo

#endif//OPC_UA_DEMO_CLIENT_HPP
