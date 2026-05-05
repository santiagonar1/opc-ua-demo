#include <iostream>

#include <object_builder.hpp>
#include <server.hpp>
#include <variable_builder.hpp>
#include <variant.hpp>

int main() {
    /* Create a server listening on port 4840 (default) */
    const auto server = demo::Server{};

    // I am modeling the following hierarchy
    // Objects/
    // MRI_Scanner/
    //     Magnet/
    //         Temperature     <- Variable (float, 4.2 K)
    //         FieldStrength   <- Variable (float, 3.0 T)
    //     Status              <- Variable (string, "Idle")
    //     ScanProgress        <- Variable (int, 0-100%)

    // Create MRI_Scanner object
    auto scanner = demo::ObjectBuilder{};
    const auto status_scanner = scanner.with_name("MRI_Scanner")
                                        .with_custom_node("mri.scanner")
                                        .under_parent(UA_NS0ID(OBJECTSFOLDER))
                                        .add_to_server(server);

    if (status_scanner != UA_STATUSCODE_GOOD) {
        std::cerr << "Failed to create the scanner" << std::endl;
        return EXIT_FAILURE;
    }

    // Create Magnet object under MRI_Scanner
    auto magnet = demo::ObjectBuilder{};
    const auto status_magnet = magnet.with_name("Magnet")
                                       .with_custom_node("mri.scanner.magnet")
                                       .under_parent(scanner.get_node_id())
                                       .add_to_server(server);

    if (status_magnet != UA_STATUSCODE_GOOD) {
        std::cerr << "Failed to create the magnet" << std::endl;
        return EXIT_FAILURE;
    }

    // Variables under Magnet
    const auto status_temperature = demo::VariableBuilder{}
                                            .with_name("Temperature")
                                            .with_custom_node("mri.scanner.magnet.temperature")
                                            .under_parent(magnet.get_node_id())
                                            .with_value(demo::make_variant(4.2f))
                                            .add_to_server(server);

    if (status_temperature != UA_STATUSCODE_GOOD) {
        std::cerr << "Failed to create the Temperature" << std::endl;
        return EXIT_FAILURE;
    }

    const auto status_field_strength = demo::VariableBuilder{}
                                               .with_name("FieldStrength")
                                               .with_custom_node("mri.scanner.magnet.fieldstrength")
                                               .under_parent(magnet.get_node_id())
                                               .with_value(demo::make_variant(3.0f))
                                               .add_to_server(server);

    if (status_field_strength != UA_STATUSCODE_GOOD) {
        std::cerr << "Failed to create the FieldStrength" << std::endl;
        return EXIT_FAILURE;
    }

    // Variables directly under MRI_Scanner
    const auto status_mri_scanner = demo::VariableBuilder{}
                                            .with_name("Status")
                                            .with_custom_node("mri.scanner.status")
                                            .under_parent(scanner.get_node_id())
                                            .with_value(demo::make_variant(std::string("Idle")))
                                            .add_to_server(server);

    if (status_mri_scanner != UA_STATUSCODE_GOOD) {
        std::cerr << "Failed to create the Scanner Status" << std::endl;
        return EXIT_FAILURE;
    }

    const auto status_scan_progress = demo::VariableBuilder{}
                                              .with_name("ScanProgress")
                                              .with_custom_node("mri.scanner.scanprogress")
                                              .under_parent(scanner.get_node_id())
                                              .with_value(demo::make_variant(20))
                                              .add_to_server(server);

    if (status_scan_progress != UA_STATUSCODE_GOOD) {
        std::cerr << "Failed to create the ScanProgress" << std::endl;
        return EXIT_FAILURE;
    }

    /* Run the server (until ctrl-c interrupt) */
    const auto status = server.run_until_interrupt();

    return status == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}