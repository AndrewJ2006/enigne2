set(SOURCES
    engine2.cpp
    engine2.h
)

add_executable(engine2 ${SOURCES})

#physx setup
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(engine2 PRIVATE _DEBUG)
else()
    target_compile_definitions(engine2 PRIVATE NDEBUG)
endif()

target_include_directories(engine2 SYSTEM PRIVATE ${PROJECT_SOURCE_DIR}/libs/physx/include)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(PHYSX_LIB_DIR ${PROJECT_SOURCE_DIR}/libs/physx/lib/debug)
else()
    set(PHYSX_LIB_DIR ${PROJECT_SOURCE_DIR}/libs/physx/lib/release)
    set(PHYSX_DLL_DIR ${PROJECT_SOURCE_DIR}/libs/DLL)

    file(GLOB PHYSX_DLLS "${PHYSX_DLL_DIR}/*.dll")

    foreach(dll ${PHYSX_DLLS})
        add_custom_command(TARGET engine2 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${dll}"
            $<TARGET_FILE_DIR:engine2>
            COMMENT "Copying PhysX DLL: ${dll}"
        )
    endforeach()
endif()

target_link_libraries(engine2 PRIVATE
    "${PHYSX_LIB_DIR}/PhysX_64.lib"
    "${PHYSX_LIB_DIR}/PhysXCommon_64.lib"
    "${PHYSX_LIB_DIR}/PhysXFoundation_64.lib"
    "${PHYSX_LIB_DIR}/PhysXCooking_64.lib"
    "${PHYSX_LIB_DIR}/PhysXExtensions_static_64.lib"
    "${PHYSX_LIB_DIR}/PhysXPvdSDK_static_64.lib"
)

# Add libraries (GLFW, GLAD, etc.)
add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/libs/glfw/lib-vc2022/glfw3.lib)
target_include_directories(glfw INTERFACE ${PROJECT_SOURCE_DIR}/libs/glfw/include)

add_library(glad ${PROJECT_SOURCE_DIR}/libs/glad/src/glad.c)
target_include_directories(glad PUBLIC ${PROJECT_SOURCE_DIR}/libs/glad/include)

target_include_directories(engine2 PRIVATE
    ${PROJECT_SOURCE_DIR}/libs/glm
)

target_link_libraries(engine2 PRIVATE glfw glad opengl32)
