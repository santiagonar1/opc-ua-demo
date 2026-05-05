#include "object_builder.hpp"

#include "server.hpp"

namespace demo {
    ObjectBuilder::ObjectBuilder() = default;

    auto ObjectBuilder::with_name(const std::string_view name) -> ObjectBuilder & {
        _name = name;
        _attributes.displayName = UA_LOCALIZEDTEXT_ALLOC("en-US", name.data());

        return *this;
    }

    auto ObjectBuilder::with_custom_node(std::string_view id) -> ObjectBuilder & {
        // 1 is used for application's custom nodes
        constexpr auto namespace_index = 1;
        _node_id = UA_NODEID_STRING_ALLOC(namespace_index, id.data());

        return *this;
    }

    auto ObjectBuilder::under_parent(const UA_NodeId &parent) -> ObjectBuilder & {
        _parent_id = parent;
        return *this;
    }

    auto ObjectBuilder::add_to_server(const Server &server) const -> UA_StatusCode {
        const auto browse_name = UA_QUALIFIEDNAME_ALLOC(1, _name.c_str());
        return UA_Server_addObjectNode(server.get_server(), _node_id, _parent_id,
                                       UA_NS0ID(ORGANIZES), browse_name,
                                       UA_NS0ID(BASEOBJECTTYPE),// Default object type
                                       _attributes,
                                       nullptr,// No node context
                                       nullptr // Don't need the output NodeId
        );
    }

    auto ObjectBuilder::get_node_id() const -> UA_NodeId { return _node_id; }

}// namespace demo