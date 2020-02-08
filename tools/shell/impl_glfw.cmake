find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_search_module(GLFW glfw3 REQUIRED)

add_executable(
    mbgl-shell
    ${MBGL_SHELL_SOURCES}
    ${CMAKE_CURRENT_LIST_DIR}/imgui_backend_impl_glfw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/window_impl_glfw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/main_glfw.cpp
)

target_include_directories(
    mbgl-shell
    PRIVATE ${GLFW_INCLUDE_DIRS}
)

target_link_directories(mbgl-shell PRIVATE $<$<BOOL:${GLFW_LIBRARY_DIRS}>:${GLFW_LIBRARY_DIRS}>)

include(${PROJECT_SOURCE_DIR}/vendor/imgui-glfw.cmake)

target_link_libraries(
    mbgl-shell
    PRIVATE ${GLFW_LIBRARIES} OpenGL::GL mbgl-vendor-imgui-glfw
)

install(TARGETS mbgl-shell RUNTIME DESTINATION bin)
