#Default setting
cmake_minimum_required(VERSION 3.20)
project(ToolingHelper)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#LLVM and Clang setting
find_package(LLVM 17 REQUIRED CONFIG)
find_package(Clang 17 REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
add_link_options("-fuse-ld=lld")

#When using the library, add the syntax below and link "${llvm_libs}" to your target.
#llvm_map_components_to_libnames(llvm_libs option)

set(
        LIBTOOLING_LIBS
        clangAST
        clangBasic
        clangDriver
        clangFrontend
        clangRewriteFrontend
        clangSerialization
        clangStaticAnalyzerFrontend
        clangTooling
        clangToolingSyntax
)

#Test setting
Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.1 # or a later release
)
FetchContent_MakeAvailable(Catch2)
set(CMAKE_CXX_FLAGS "-fcoverage-mapping -fprofile-instr-generate")

#Sources
set(
        LIBRARY_SOURCES
        src/opt/CommandOption.h
        src/opt/CommandLineHelper.cpp
        src/opt/CommandLineHelper.h
        src/detail/TypeSupport.h
)

#Lib Target
add_library(
        ToolingHelper
        ${LIBRARY_SOURCES}
)
target_link_libraries(ToolingHelper ${LIBTOOLING_LIBS})

#Test Target
add_executable(
        tests
        ${LIBRARY_SOURCES}
        test/helper-commandline-tests.cpp
)
target_link_libraries(tests Catch2::Catch2WithMain ${LIBTOOLING_LIBS})
enable_testing()
add_test(NAME tests COMMAND tests)

#Output Directory setting
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/lib)

#Install setting
install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/ DESTINATION ${CMAKE_SOURCE_DIR}/include/ToolingHelper FILES_MATCHING PATTERN "*.h")
install(TARGETS ToolingHelper ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/lib)