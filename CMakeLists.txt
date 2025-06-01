cmake_minimum_required(VERSION 3.15)
project(engine2)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")

# Optional: Enable Edit and Continue for MSVC if policy is available
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()


# Add your engine subdirectory
add_subdirectory(engine2)
