#ifndef OPC_UA_DEMO_VARIANT_HPP
#define OPC_UA_DEMO_VARIANT_HPP

#include <expected>
#include <open62541/types.h>
#include <string>

namespace demo {
    [[nodiscard]] auto make_variant() -> UA_Variant;
    [[nodiscard]] auto make_variant(int32_t value) -> UA_Variant;

    class Variant {
    public:
        using ErrorType = std::string;

        Variant();
        explicit Variant(int32_t value);

        ~Variant();

        [[nodiscard]] auto extract() const -> std::expected<int32_t, ErrorType>;

    private:
        UA_Variant _variant{};
    };
}// namespace demo

#endif//OPC_UA_DEMO_VARIANT_HPP
