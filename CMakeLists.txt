cmake_minimum_required(VERSION 3.13)
project(DTS_Ex2)

set(CMAKE_CXX_STANDARD 14)

add_executable(DTS_Ex2 avl.h node.h library2.h main2.cpp dataCenter.h dataCenter.cpp dataCenterGroup.cpp dataCenterGroup.h
        key.cpp key.h unionFind.cpp unionFind.h server.cpp server.h chainNode.h chainNode.cpp dynamicArr.cpp dynamicArr.h)
