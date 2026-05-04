find_package(open62541 REQUIRED)

add_executable(app.out main.cpp)
target_link_libraries(app.out
        PRIVATE open62541::open62541
        PRIVATE ${PROJECT_NAME}
)