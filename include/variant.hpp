#ifndef OPC_UA_DEMO_VARIANT_HPP
#define OPC_UA_DEMO_VARIANT_HPP

#include <open62541/types.h>

namespace demo {
    [[nodiscard]] auto make_variant() -> UA_Variant;
    [[nodiscard]] auto make_variant(int32_t value) -> UA_Variant;
}

#endif//OPC_UA_DEMO_VARIANT_HPP
