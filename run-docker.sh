#!/usr/bin/env bash

DOCKER_IMAGE=opc-ua-demo
FOLDER_NAME=code

docker build -t ${DOCKER_IMAGE} .
docker run --rm -it -v .:/${FOLDER_NAME} -w /${FOLDER_NAME} ${DOCKER_IMAGE} bash
