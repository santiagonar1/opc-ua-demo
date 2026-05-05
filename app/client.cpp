#include <client.hpp>

#include <iostream>
#include <ostream>

int main() {
    auto client = demo::Client{};

    if (const auto status = client.connect("opc.tcp://localhost:4840");
        status != UA_STATUSCODE_GOOD) {
        return static_cast<int>(status);
    }

    const auto value = client.read_attribute_custom_node<int32_t>("mri.scanner.scanprogress");

    if (not value.has_value()) {
        std::cerr << "Failed to read the value" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "the value is: " << value.value() << std::endl;

    return EXIT_SUCCESS;
}