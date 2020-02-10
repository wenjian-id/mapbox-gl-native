set(
    MBGL_SHELL_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/demo_widget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/fps_widget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/imgui_backend.cpp
    ${CMAKE_CURRENT_LIST_DIR}/map_widget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/widget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/window.cpp
)

if(CMAKE_SYSTEM_NAME STREQUAL Android)
    include(${CMAKE_CURRENT_LIST_DIR}/impl_glfm.cmake)
elseif(CMAKE_SYSTEM_NAME STREQUAL iOS)
    include(${CMAKE_CURRENT_LIST_DIR}/impl_glfm.cmake)
elseif(CMAKE_SYSTEM_NAME STREQUAL Linux)
    include(${CMAKE_CURRENT_LIST_DIR}/impl_glfw.cmake)
elseif(CMAKE_SYSTEM_NAME STREQUAL Darwin)
    include(${CMAKE_CURRENT_LIST_DIR}/impl_glfw.cmake)
else()
    message(FATAL_ERROR "Unsupported target platform: " ${CMAKE_SYSTEM_NAME})
endif()

target_include_directories(
    mbgl-shell
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(
    mbgl-shell
    PRIVATE Mapbox::Map Mapbox::Base::Extras::expected-lite mbgl-compiler-options
)
