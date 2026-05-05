#include <open62541/client.h>
#include <open62541/client_highlevel.h>
#include <stdio.h>

#include <client.hpp>
#include <variant.hpp>

int main() {
    const auto client = demo::Client{};

    auto status = client.connect("opc.tcp://localhost:4840");
    if (status != UA_STATUSCODE_GOOD) { return static_cast<int>(status); }

    auto value = demo::make_variant(); /* Variants can hold scalar values and arrays of any type */
    status = UA_Client_readValueAttribute(client.get_client(), UA_NODEID_STRING(1, "the.answer"),
                                          &value);
    if (status == UA_STATUSCODE_GOOD &&
        UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_INT32])) {
        printf("the value is: %i\n", *(UA_Int32 *) value.data);
    }

    /* Clean up */
    UA_Variant_clear(&value);
    return status == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}