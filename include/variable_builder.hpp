#ifndef OPC_UA_DEMO_VARIABLE_BUILDER_HPP
#define OPC_UA_DEMO_VARIABLE_BUILDER_HPP

#include "server.hpp"

#include <open62541/server.h>
#include <string>
#include <string_view>

namespace demo {
    class VariableBuilder {
    public:
        VariableBuilder();

        auto with_name(std::string_view name) -> VariableBuilder &;
        auto with_custom_node(std::string_view id) -> VariableBuilder &;
        auto under_parent(const UA_NodeId &parent) -> VariableBuilder &;
        auto with_value(const UA_Variant &value) -> VariableBuilder &;
        auto writable(bool isWritable) -> VariableBuilder &;

        [[nodiscard]] auto add_to_server(const Server &server) const -> UA_StatusCode;

    private:
        UA_VariableAttributes _attributes{UA_VariableAttributes_default};
        UA_NodeId _node_id{UA_NODEID_NULL};
        UA_NodeId _parent_id{UA_NS0ID(OBJECTSFOLDER)};
        std::string _name{};
    };
}// namespace demo

#endif//OPC_UA_DEMO_VARIABLE_BUILDER_HPP
