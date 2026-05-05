#include <client.hpp>

#include <iostream>
#include <ostream>

int main() {
    auto client = demo::Client{};

    if (const auto status = client.connect("opc.tcp://localhost:4840");
        status != UA_STATUSCODE_GOOD) {
        return static_cast<int>(status);
    }

    const auto scanner_progress =
            client.read_attribute_custom_node<int32_t>("mri.scanner.scanprogress");

    if (not scanner_progress.has_value()) {
        std::cerr << "Failed to read the scanner progress" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "The scanner progress is: " << scanner_progress.value() << std::endl;

    const auto field_strength =
            client.read_attribute_custom_node<float>("mri.scanner.magnet.fieldstrength");

    if (not field_strength.has_value()) {
        std::cerr << "Failed to read the field strength" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "The field strength is: " << field_strength.value() << std::endl;


    return EXIT_SUCCESS;
}