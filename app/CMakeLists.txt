find_package(open62541 REQUIRED)

add_executable(server.out server.cpp)
target_link_libraries(server.out
        PRIVATE open62541::open62541
        PRIVATE ${PROJECT_NAME}
)

add_executable(client.out client.cpp)
target_link_libraries(client.out
        PRIVATE open62541::open62541
        PRIVATE ${PROJECT_NAME}
)