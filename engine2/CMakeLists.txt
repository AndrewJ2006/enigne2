set(SOURCES
    src/Main.cpp
    src/Backend/Backend.cpp
    src/Backend/GLwindow.cpp
    src/Types/Mesh.cpp
    src/Types/Plane.cpp
    src/Renderer/Renderer.cpp
    src/Camera/Camera.cpp
    res/Shader/Shader.cpp

)

add_executable(Main ${SOURCES})

target_include_directories(Main PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Types
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Renderer
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Backend
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Camera

    ${CMAKE_CURRENT_SOURCE_DIR}/res/Shader

)

# Copy shader files to output directory
file(GLOB SHADERS "${CMAKE_CURRENT_SOURCE_DIR}/res/Shader/*.vert" "${CMAKE_CURRENT_SOURCE_DIR}/res/Shader/*.frag")

foreach(shader ${SHADERS})
    add_custom_command(TARGET Main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${shader}" $<TARGET_FILE_DIR:Main>
        COMMENT "Copying shader file: ${shader}"
    )
endforeach()




target_compile_definitions(Main PRIVATE 
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
)

target_include_directories(Main SYSTEM PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/physx/include
)

set(PHYSX_LIB_BASE ${CMAKE_CURRENT_SOURCE_DIR}/libs/physx/lib)
set(PHYSX_DLL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/DLL)

set(PHYSX_LIB_DIR $<$<CONFIG:Debug>:${PHYSX_LIB_BASE}/debug>$<$<NOT:$<CONFIG:Debug>>:${PHYSX_LIB_BASE}/release>)

target_link_libraries(Main PRIVATE
    "${PHYSX_LIB_DIR}/PhysX_64.lib"
    "${PHYSX_LIB_DIR}/PhysXCommon_64.lib"
    "${PHYSX_LIB_DIR}/PhysXFoundation_64.lib"
    "${PHYSX_LIB_DIR}/PhysXCooking_64.lib"
    "${PHYSX_LIB_DIR}/PhysXExtensions_static_64.lib"
    "${PHYSX_LIB_DIR}/PhysXPvdSDK_static_64.lib"
)

file(GLOB PHYSX_DLLS "${PHYSX_DLL_DIR}/*.dll")
foreach(dll ${PHYSX_DLLS})
    add_custom_command(TARGET Main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${dll}" $<TARGET_FILE_DIR:Main>
        COMMENT "Copying PhysX DLL: ${dll}"
    )
endforeach()

# GLFW 
set(GLFW_LIB_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/debug/glfw3.lib)
set(GLFW_LIB_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/release/glfw3.lib)

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
    IMPORTED_LOCATION_DEBUG           ${GLFW_LIB_DEBUG}
    IMPORTED_LOCATION_RELEASE         ${GLFW_LIB_RELEASE}
    IMPORTED_LOCATION_MINSIZEREL      ${GLFW_LIB_RELEASE}
    IMPORTED_LOCATION_RELWITHDEBINFO  ${GLFW_LIB_RELEASE}
)
target_include_directories(glfw INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/include)

# GLAD
add_library(glad ${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/include)

# GLM
target_include_directories(Main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs/glm)

target_link_libraries(Main PRIVATE glfw glad opengl32)
