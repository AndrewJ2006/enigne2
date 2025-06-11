set(SOURCES
    src/engine2.cpp
    src/Backend/Backend.cpp
    src/Backend/GLwindow.cpp
    src/Types/Mesh.cpp
    src/Renderer/Renderer.cpp
)

add_executable(engine2 ${SOURCES})

target_include_directories(engine2 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Types
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Renderer
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Backend
)

# Preprocessor macros
target_compile_definitions(engine2 PRIVATE 
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
)

# PhysX
target_include_directories(engine2 SYSTEM PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/physx/include
)

set(PHYSX_LIB_BASE ${CMAKE_CURRENT_SOURCE_DIR}/libs/physx/lib)
set(PHYSX_DLL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/DLL)

set(PHYSX_LIB_DIR $<$<CONFIG:Debug>:${PHYSX_LIB_BASE}/debug>$<$<NOT:$<CONFIG:Debug>>:${PHYSX_LIB_BASE}/release>)

target_link_libraries(engine2 PRIVATE
    "${PHYSX_LIB_DIR}/PhysX_64.lib"
    "${PHYSX_LIB_DIR}/PhysXCommon_64.lib"
    "${PHYSX_LIB_DIR}/PhysXFoundation_64.lib"
    "${PHYSX_LIB_DIR}/PhysXCooking_64.lib"
    "${PHYSX_LIB_DIR}/PhysXExtensions_static_64.lib"
    "${PHYSX_LIB_DIR}/PhysXPvdSDK_static_64.lib"
)

# Copy PhysX DLLs after build
file(GLOB PHYSX_DLLS "${PHYSX_DLL_DIR}/*.dll")
foreach(dll ${PHYSX_DLLS})
    add_custom_command(TARGET engine2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${dll}" $<TARGET_FILE_DIR:engine2>
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
target_include_directories(engine2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs/glm)

target_link_libraries(engine2 PRIVATE glfw glad opengl32)
