#include <iostream>

#include <server.hpp>
#include <variable_builder.hpp>
#include <variant.hpp>

int main() {
    /* Create a server listening on port 4840 (default) */
    const auto server = demo::Server{};

    const auto status_creation = demo::VariableBuilder()
                                         .with_name("the answer")
                                         .with_custom_node("the.answer")
                                         .with_value(demo::make_variant(42))
                                         .add_to_server(server);

    if (status_creation != UA_STATUSCODE_GOOD) {
        std::cerr << "Failed to create the variable" << std::endl;
        return EXIT_FAILURE;
    }

    /* Run the server (until ctrl-c interrupt) */
    const auto status = server.run_until_interrupt();

    return status == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}