add_library(
    mbgl-shell SHARED
    ${MBGL_SHELL_SOURCES}
    ${CMAKE_CURRENT_LIST_DIR}/imgui_backend_impl_glfm.cpp
    ${CMAKE_CURRENT_LIST_DIR}/window_impl_glfm.cpp
    ${CMAKE_CURRENT_LIST_DIR}/main_glfm.cpp
)

include(${PROJECT_SOURCE_DIR}/vendor/glfm.cmake)
include(${PROJECT_SOURCE_DIR}/vendor/imgui-glfm.cmake)

target_link_libraries(
    mbgl-shell
    PRIVATE mbgl-vendor-imgui-glfm mbgl-vendor-glfm
)

install(TARGETS mbgl-shell LIBRARY DESTINATION lib)
