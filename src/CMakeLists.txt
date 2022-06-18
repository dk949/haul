link_compile_commands()

file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${CMAKE_SOURCE_DIR}/src/*.hpp")

add_executable(${EXE_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(
    ${EXE_NAME} PRIVATE "${CMAKE_BINARY_DIR}/project_config/include"
)

find_package(docopt CONFIG REQUIRED)
target_link_libraries(${EXE_NAME} PRIVATE docopt_s)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${EXE_NAME} PRIVATE fmt::fmt)

find_package(reproc++ CONFIG REQUIRED)
target_link_libraries(${EXE_NAME} PRIVATE reproc++)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(${EXE_NAME} PRIVATE nlohmann_json::nlohmann_json)

enable_sanitizers(${EXE_NAME})
set_target_warnings(${EXE_NAME})
