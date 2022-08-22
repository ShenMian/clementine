
# 输出基本信息
if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.22.0")
    cmake_host_system_information(RESULT OS_PRETTY_NAME QUERY DISTRIB_PRETTY_NAME)
endif()
message(STATUS "OS")
message(STATUS "|- Name   : ${CMAKE_SYSTEM_NAME}(${OS_PRETTY_NAME})")
message(STATUS "`- Version: ${CMAKE_SYSTEM_VERSION}")
message(STATUS "Compiler")
message(STATUS "|- ID     : ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "`- Version: ${CMAKE_CXX_COMPILER_VERSION}")
