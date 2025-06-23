cmake_minimum_required(VERSION 3.10)
project(lab5_main)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main_interfejs
    FabrykaSygnalu.cpp
    InterfejsUzytkownika.cpp
    KompozytRownolegl.cpp
    KompozytSzeregowy.cpp
    KrokPetliSprzezeniaZwrotnego.cpp
    main_interfejs.cpp
    ModelARX.cpp
    OgranicznikAmplitudy.cpp
    ProstokatGenerator.cpp
    RegulatorPID.cpp
    SinusGenerator.cpp
    SygnalDekorator.cpp
    SzumBialyGenerator.cpp
    TrojkatGenerator.cpp
    WartoscStalaGenerator.cpp
)
