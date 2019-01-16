
cmake_minimum_required(VERSION 3.1)

# Use directory name for this project's name. 
string(REGEX MATCH Problem.+ # Format: Project + Number
       ProjectName ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "${ProjectName}")

project(${ProjectName} LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)

if(MSVC)
    target_compile_options(${PROJECT_NAME}
    PRIVATE
        /std:c++latest
    )
else()
    target_compile_options(${PROJECT_NAME}
    PRIVATE
        -std=c++17
    )
endif()

target_include_directories(${PROJECT_NAME}
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${ROOT_DIR}/External/botan/build/include
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
    GSL
    ${ROOT_DIR}/External/botan/build/Debug/botan.lib
)

install(TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_PREFIX}
)
