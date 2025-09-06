cmake_minimum_required(VERSION 3.15)
project(engine2)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")



# Optional: Enable Edit and Continue for MSVC if policy is available
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()


# Add your engine subdirectory
add_subdirectory(engine2)




#/MD = Release build with dynamic runtime

#/MDd = Debug build with dynamic runtime

#/MT = Release build with static runtime

#/MTd = Debug build with static runtime




#Defualt Visual studio Compiler

# cmake ..
# cmake --build .


# Ninja build setup (json file automatically take care of ninja in out folder)

# cmake -G Ninja ..
# ninja