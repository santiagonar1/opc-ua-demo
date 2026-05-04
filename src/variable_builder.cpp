#include "variable_builder.hpp"

namespace demo {
    VariableBuilder::VariableBuilder() = default;

    auto VariableBuilder::with_name(const std::string_view name) -> VariableBuilder & {
        _name = name;
        _attributes.displayName = UA_LOCALIZEDTEXT_ALLOC("", name.data());

        return *this;
    }

    auto VariableBuilder::with_custom_node(const std::string_view id) -> VariableBuilder & {
        // 1 is used for application's custom nodes
        constexpr auto namespace_index = 1;
        _node_id = UA_NODEID_STRING_ALLOC(namespace_index, id.data());

        return *this;
    }

    auto VariableBuilder::under_parent(const UA_NodeId &parent) -> VariableBuilder & {
        _parent_id = parent;

        return *this;
    }

    auto VariableBuilder::with_value(const UA_Variant &value) -> VariableBuilder & {
        _attributes.value = value;

        return *this;
    }

    auto VariableBuilder::writable(const bool isWritable) -> VariableBuilder & {
        _attributes.accessLevel = isWritable ? UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE
                                             : UA_ACCESSLEVELMASK_READ;

        return *this;
    }

    auto VariableBuilder::add_to_server(const Server &server) const -> UA_StatusCode {
        const UA_QualifiedName browseName = UA_QUALIFIEDNAME_ALLOC(1, _name.c_str());

        return UA_Server_addVariableNode(server.get_server(), _node_id, _parent_id,
                                         UA_NS0ID(ORGANIZES), browseName, UA_NODEID_NULL,
                                         _attributes, nullptr, nullptr);
    }

}// namespace demo