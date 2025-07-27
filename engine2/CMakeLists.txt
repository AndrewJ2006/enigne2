set(SOURCES
    src/Main.cpp
    src/Backend/Backend.cpp
    src/Backend/GLwindow.cpp
    src/Backend/Camera.cpp
    src/Types/Mesh.cpp
    src/Types/Plane.cpp
    src/Renderer/Renderer.cpp
    src/Editor/CameraEditor.cpp
    src/Editor/Editor.cpp

    src/Game/Game.cpp
    src/AssetManager/AssetManager.cpp
    src/World/World.cpp
    src/World/TerrainGen.cpp
    src/Types/Cube.cpp
    res/Shader/Shader.cpp
    src/Types/Wall.cpp
    src/Types/Door.cpp
    src/Types/JSON.cpp 
    
    src/Player/Player.cpp
    src/Player/PlayerCamera.cpp

    src/Physics/ColliderPx.cpp
    src/Physics/CollisionPx.cpp
    src/Physics/ScenePx.cpp
    src/Physics/ManagerPx.cpp
    src/Physics/PlayerPx.cpp
    src/Physics/RaycastingPx.cpp

    src/Utils/UtilMesh.cpp
    src/Utils/UtilPhysics.cpp

)



add_executable(Main ${SOURCES})

target_include_directories(Main PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/res

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Renderer
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Backend
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Camera
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Game
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Base
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Types
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AssetManager
    ${CMAKE_CURRENT_SOURCE_DIR}/src/World
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Physics
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Player
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Utils
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Editor


    ${CMAKE_CURRENT_SOURCE_DIR}/res/Geometry
    ${CMAKE_CURRENT_SOURCE_DIR}/res/Shader

    ${CMAKE_CURRENT_SOURCE_DIR}/libs/physx/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/physx/include/characterkinematic
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/physx/include/collision
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/physx/include/common
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/physx/include/cooking
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/physx/include/cudamanger
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/physx/include/extensions
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/physx/include/filebuf
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/physx/include/foundation
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/physx/include/geometry
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/physx/include/geomutils
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/physx/include/gpu
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/physx/include/vehicle2



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


## JSON FILES - does not update automaitcally FIXXXXX
file(GLOB JSON_FILES "${CMAKE_CURRENT_SOURCE_DIR}/res/Geometry/*.json")

add_custom_command(TARGET Main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Copying JSON files..."
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:Main>
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/res/Geometry"
            $<TARGET_FILE_DIR:Main>
    COMMENT "Copying all JSON files to output directory"
)



## FAST NOISE 2

add_subdirectory(libs/FastNoise)



 ##nlohmann json FILE IN OUT FOLDER
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(libs/nlohmann_json)



# Physx

# Include PhysX headers
target_include_directories(Main SYSTEM PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/physx/include
)

# Paths
set(PHYSX_LIB_BASE ${CMAKE_CURRENT_SOURCE_DIR}/libs/physx/lib)
set(PHYSX_DLL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/DLL)
set(PHYSX_LIB_DIR $<$<CONFIG:Debug>:${PHYSX_LIB_BASE}/debug>$<$<NOT:$<CONFIG:Debug>>:${PHYSX_LIB_BASE}/release>)

# Link PhysX libraries (character kinematic lib moved up in order)
target_link_libraries(Main PRIVATE
    "${PHYSX_LIB_DIR}/PhysXFoundation_64.lib"
    "${PHYSX_LIB_DIR}/PhysXCommon_64.lib"
    "${PHYSX_LIB_DIR}/PhysX_64.lib"
    "${PHYSX_LIB_DIR}/PhysXCharacterKinematic_static_64.lib"  # Must link this BEFORE Extensions, Cooking, PVD, etc.
    "${PHYSX_LIB_DIR}/PhysXExtensions_static_64.lib"
    "${PHYSX_LIB_DIR}/PhysXCooking_64.lib"
    "${PHYSX_LIB_DIR}/PhysXPvdSDK_static_64.lib"
)

# Copy PhysX DLLs after build
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



target_link_libraries(Main PRIVATE FastNoise2 nlohmann_json::nlohmann_json glfw glad opengl32)