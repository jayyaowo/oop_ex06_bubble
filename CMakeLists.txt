cmake_minimum_required(VERSION 3.10)
project(OOP_Raylib_Lab CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(RAYLIB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(RAYLIB_LIB_DIR     "${CMAKE_SOURCE_DIR}/lib")
set(SRC_DIR            "${CMAKE_SOURCE_DIR}/src")

file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.h")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${RAYLIB_INCLUDE_DIR} ${SRC_DIR})

if(APPLE)
    message(STATUS "Platform: macOS")
    set(RAYLIB_LIB "${RAYLIB_LIB_DIR}/mac/libraylib.a")
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        ${RAYLIB_LIB}
        "-framework CoreVideo"
        "-framework IOKit"
        "-framework Cocoa"
        "-framework GLUT"
        "-framework OpenGL"
    )

elseif(WIN32)
    message(STATUS "Platform: Windows")
    set(RAYLIB_LIB "${RAYLIB_LIB_DIR}/win/libraylib.a")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${RAYLIB_LIB} gdi32 winmm)

else()
    message(STATUS "Platform: Linux")
    set(RAYLIB_LIB "${RAYLIB_LIB_DIR}/linux/libraylib.a")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${RAYLIB_LIB} m pthread dl rt X11)
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/resources")
    file(COPY "${CMAKE_SOURCE_DIR}/resources" DESTINATION "${CMAKE_BINARY_DIR}")
    message(STATUS "Assets have been copied to build directory")
endif()
