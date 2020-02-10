if(TARGET mbgl-vendor-glfm)
    return()
endif()

add_library(
    mbgl-vendor-glfm STATIC
    $<$<PLATFORM_ID:Android>:${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c>
    $<$<PLATFORM_ID:Android>:${CMAKE_CURRENT_LIST_DIR}/glfm/src/glfm_platform_android.c>
    $<$<PLATFORM_ID:iOS>:${CMAKE_CURRENT_LIST_DIR}/glfm/src/glfm_platform_ios.m>
)

target_include_directories(
    mbgl-vendor-glfm
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/glfm/include
    PRIVATE $<$<PLATFORM_ID:Android>:${ANDROID_NDK}/sources/android/native_app_glue>
)

target_link_libraries(
    mbgl-vendor-glfm
    PUBLIC $<$<PLATFORM_ID:Android>:GLESv3>
)
