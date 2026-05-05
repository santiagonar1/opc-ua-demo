#ifndef OPC_UA_DEMO_VARIANT_HPP
#define OPC_UA_DEMO_VARIANT_HPP

#include <expected>
#include <open62541/types.h>
#include <string>

namespace demo {
    using ErrorType = std::string;

    [[nodiscard]] auto make_variant() -> UA_Variant;
    [[nodiscard]] auto make_variant(int32_t value) -> UA_Variant;
    [[nodiscard]] auto make_variant(uint32_t value) -> UA_Variant;
    [[nodiscard]] auto make_variant(float value) -> UA_Variant;

    template<typename T>
    [[nodiscard]] auto extract_value(const UA_Variant &variant)
            -> std::expected<T, ErrorType> = delete;

    template<>
    [[nodiscard]] auto extract_value(const UA_Variant &variant)
            -> std::expected<int32_t, ErrorType>;

    template<>
    [[nodiscard]] auto extract_value(const UA_Variant &variant)
            -> std::expected<uint32_t, ErrorType>;

    template<>
    [[nodiscard]] auto extract_value(const UA_Variant &variant) -> std::expected<float, ErrorType>;
}// namespace demo

#endif//OPC_UA_DEMO_VARIANT_HPP
