#!/bin/bash
protoc -I=./proto --cpp_out=./protocpp ./proto/*.proto
#cp -r ./protocpp/* ../LogicServer/protoc/ 