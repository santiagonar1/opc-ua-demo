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

    auto make_variant(const uint32_t value) -> UA_Variant {
        UA_Variant variant;
        UA_Variant_init(&variant);
        UA_Variant_setScalarCopy(&variant, &value, &UA_TYPES[UA_TYPES_UINT32]);
        return variant;
    }

    auto make_variant(const float value) -> UA_Variant {
        UA_Variant variant;
        UA_Variant_init(&variant);
        UA_Variant_setScalarCopy(&variant, &value, &UA_TYPES[UA_TYPES_FLOAT]);
        return variant;
    }

    template<>
    [[nodiscard]] auto extract_value<int32_t>(const UA_Variant &variant)
            -> std::expected<int32_t, std::string> {
        if (not UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_INT32])) {
            return std::unexpected("Variant does not contain int32_t");
        }

        return *static_cast<const int32_t *>(variant.data);
    }

    template<>
    [[nodiscard]] auto extract_value<uint32_t>(const UA_Variant &variant)
            -> std::expected<uint32_t, std::string> {
        if (not UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_UINT32])) {
            return std::unexpected("Variant does not contain uint32_t");
        }

        return *static_cast<const uint32_t *>(variant.data);
    }

    template<>
    [[nodiscard]] auto extract_value<float>(const UA_Variant &variant)
            -> std::expected<float, std::string> {
        if (not UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_FLOAT])) {
            return std::unexpected("Variant does not contain float");
        }

        return *static_cast<const float *>(variant.data);
    }

}// namespace demo