set(MODULE_NAME algorithms)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(${MODULE_NAME} STATIC ${SOURCES})

target_link_libraries(${MODULE_NAME} PUBLIC pixel)
target_include_directories(${MODULE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
