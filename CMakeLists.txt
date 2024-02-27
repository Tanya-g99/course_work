cmake_minimum_required(VERSION 3.15)

project("course_work")

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED True)

enable_testing()

add_subdirectory(lib)
add_subdirectory(tests)

add_compile_options(
    -Werror

    -Wall
    -Wextra
    -Wpedantic

    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
)

