#ifndef OPC_UA_DEMO_OBJECT_BUILDER_HPP
#define OPC_UA_DEMO_OBJECT_BUILDER_HPP

#include <open62541/server.h>

#include <string>

namespace demo {
    class Server;

    class ObjectBuilder {
    public:
        ObjectBuilder();

        auto with_name(std::string_view name) -> ObjectBuilder &;
        auto with_custom_node(std::string_view id) -> ObjectBuilder &;
        auto under_parent(const UA_NodeId &parent) -> ObjectBuilder &;

        [[nodiscard]] auto add_to_server(const Server &server) const -> UA_StatusCode;
        [[nodiscard]] auto get_node_id() const -> UA_NodeId;

    private:
        UA_ObjectAttributes _attributes{UA_ObjectAttributes_default};
        UA_NodeId _node_id{UA_NODEID_NULL};
        UA_NodeId _parent_id{UA_NS0ID(OBJECTSFOLDER)};
        std::string _name{};
    };
}// namespace demo

#endif//OPC_UA_DEMO_OBJECT_BUILDER_HPP
