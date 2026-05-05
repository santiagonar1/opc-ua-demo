#!/usr/bin/env bash

DOCKER_IMAGE=opc-ua-demo
FOLDER_NAME=code

docker build -t ${DOCKER_IMAGE} .

docker run --rm \
  -v .:/${FOLDER_NAME} \
  -w /${FOLDER_NAME} \
  opc-ua-demo \
  bash -lc '
    set -e

    printf "\n**************** BUILDING DEMO AND DEPENDENCIES ****************\n\n"
    echo "This step might take a while..."

    sleep 2

    cmake -S . -B /tmp/opc-ua-demo-build -DCMAKE_BUILD_TYPE=Release -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES=conan_provider.cmake
    cmake --build /tmp/opc-ua-demo-build --parallel

    printf "\n**************** RUNNING THE SERVER ****************\n\n"

    /tmp/opc-ua-demo-build/app/server.out &
    SERVER_PID=$!

    sleep 2

    printf "\n**************** RUNNING THE CLIENT ****************\n\n"

    /tmp/opc-ua-demo-build/app/client.out
    CLIENT_STATUS=$?

    kill "$SERVER_PID" 2>/dev/null || true
    wait "$SERVER_PID" 2>/dev/null || true

    exit "$CLIENT_STATUS"
  '