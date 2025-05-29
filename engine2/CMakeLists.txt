# Define source files
set(SOURCES
    engine2.cpp
    engine2.h
)

# Create the executable
add_executable(engine2 ${SOURCES})

# Add PhysX include directory
target_include_directories(engine2 SYSTEM PRIVATE ${PROJECT_SOURCE_DIR}/libs/physx/include)
# PhysX libraries directory path
set(PHYSX_LIB_DIR ${PROJECT_SOURCE_DIR}/libs/physx/libs)

# Link PhysX libraries by full path (recommended to avoid "not found" issues)
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
