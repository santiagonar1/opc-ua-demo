#include "variant.hpp"

namespace demo {
    auto make_variant() -> UA_Variant {
        UA_Variant variant;
        UA_Variant_init(&variant);
        return variant;
    }

    auto make_variant(const int32_t value) -> UA_Variant {
        UA_Variant variant;
        UA_Variant_init(&variant);
        UA_Variant_setScalarCopy(&variant, &value, &UA_TYPES[UA_TYPES_INT32]);
        return variant;
    }

    Variant::Variant() { UA_Variant_init(&_variant); }

    Variant::Variant(const int32_t value) {
        UA_Variant_init(&_variant);
        UA_Variant_setScalarCopy(&_variant, &value, &UA_TYPES[UA_TYPES_INT32]);
    }

    Variant::~Variant() { UA_Variant_clear(&_variant); }

    auto Variant::extract() const -> std::expected<int32_t, ErrorType> {
        if (not UA_Variant_hasScalarType(&_variant, &UA_TYPES[UA_TYPES_INT32])) {
            return std::unexpected(ErrorType{"Variant is not an integer"});
        }

        return *static_cast<const int32_t *>(_variant.data);
    }
}// namespace demo