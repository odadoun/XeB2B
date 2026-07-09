cmake_minimum_required(VERSION 3.10)

project(XeB2B)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})

find_package(ROOT REQUIRED COMPONENTS Core RIO Hist Tree)
include(${ROOT_USE_FILE})

add_executable(xeb2b
    xeb2b.cc
    src/XeB2BDetectorConstruction.cc
    src/XeB2BPrimaryGeneratorAction.cc
    src/XeB2BPhysicsList.cc
)

target_include_directories(xeb2b PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${ROOT_INCLUDE_DIRS}
)

target_link_libraries(xeb2b
    ${Geant4_LIBRARIES}
    ${ROOT_LIBRARIES}
)

set_target_properties(xeb2b PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin
)
