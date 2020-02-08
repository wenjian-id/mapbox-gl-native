if(TARGET mbgl-vendor-imgui-glfw)
    return()
endif()

add_library(
    mbgl-vendor-imgui-glfw STATIC
    ${CMAKE_CURRENT_LIST_DIR}/imgui/examples/imgui_impl_opengl3.cpp
    ${CMAKE_CURRENT_LIST_DIR}/imgui/examples/imgui_impl_glfw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui.cpp
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_demo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_widgets.cpp
)

target_link_libraries(
    mbgl-shell
    PRIVATE mbgl-compiler-options
)

target_compile_definitions(
    mbgl-vendor-imgui-glfw
    PUBLIC IMGUI_IMPL_OPENGL_ES3 IMGUI_IMPL_OPENGL_LOADER_CUSTOM
)

target_include_directories(
    mbgl-vendor-imgui-glfw SYSTEM
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/imgui ${CMAKE_CURRENT_LIST_DIR}/imgui/examples
)

set_property(TARGET mbgl-vendor-imgui-glfw PROPERTY FOLDER Core)
