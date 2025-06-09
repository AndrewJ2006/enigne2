cmake_minimum_required(VERSION 3.15)
project(engine2)

set(SOURCES
    src/engine2.cpp
    src/Camera/Camera.cpp
)

add_executable(engine2 ${SOURCES})

target_include_directories(engine2 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

#third party
target_include_directories(engine2 SYSTEM PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/physx/include
)

################# PhysX Setup

target_compile_definitions(engine2 PRIVATE 
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
)

set(PHYSX_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/physx/lib/$<CONFIG>)
set(PHYSX_DLL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/DLL)

file(GLOB PHYSX_DLLS "${PHYSX_DLL_DIR}/*.dll")
foreach(dll ${PHYSX_DLLS})
    add_custom_command(TARGET engine2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${dll}"
        "$<TARGET_FILE_DIR:engine2>"
        COMMENT "Copying PhysX DLL: ${dll}"
    )
endforeach()

target_link_libraries(engine2 PRIVATE
    "${PHYSX_LIB_DIR}/PhysX_64.lib"
    "${PHYSX_LIB_DIR}/PhysXCommon_64.lib"
    "${PHYSX_LIB_DIR}/PhysXFoundation_64.lib"
    "${PHYSX_LIB_DIR}/PhysXCooking_64.lib"
    "${PHYSX_LIB_DIR}/PhysXExtensions_static_64.lib"
    "${PHYSX_LIB_DIR}/PhysXPvdSDK_static_64.lib"
)

############## GLFW (precompiled) & GLAD (source) Setup

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/lib-vc2022/glfw3.lib
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/include
)

add_library(glad ${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/include)

target_link_libraries(engine2 PRIVATE glfw glad opengl32)
