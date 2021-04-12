################################################################################
# Macros
################################################################################


macro(DownloadAndPopulateCatch2)
    set(CATCH_BUILD_TESTING OFF CACHE BOOL "Internal Catch2's option to disable Catch2 self-test")
    set(BUILD_TESTING OFF CACHE BOOL "Internal Catch2's option to disable Catch2 self-test")

    include(FetchContent)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG 0fa133a0c5e065065ef96ac2b6c0284cf5da265d
    )
    FetchContent_MakeAvailable(Catch2)
endmacro()


macro(CreateTests)
    add_executable(jungles_cpp_utils_tests test_callback.cpp)
    target_link_libraries(jungles_cpp_utils_tests PRIVATE Catch2::Catch2WithMain jungles::cpp_utils)
    target_compile_options(jungles_cpp_utils_tests PRIVATE -Wall -Wextra)
    add_test(NAME native_helpers COMMAND valgrind --leak-check=full $<TARGET_FILE:jungles_cpp_utils_tests>)
endmacro()


################################################################################
# Main script
################################################################################


DownloadAndPopulateCatch2()
CreateTests()
