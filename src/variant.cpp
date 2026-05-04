#include "variant.hpp"

namespace demo {
    auto make_variant(const int32_t value) -> UA_Variant {
        UA_Variant variant;
        UA_Variant_init(&variant);
        UA_Variant_setScalarCopy(&variant, &value, &UA_TYPES[UA_TYPES_INT32]);
        return variant;
    }
}// namespace demo