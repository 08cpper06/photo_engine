cmake_minimum_required(VERSION 3.8)

project(photo_engine)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

if (MSVC)
	set(CMAKE_CXX_FLAGS "/std:c++20 /EHsc /DWIN64")
else()
	set(CMAKE_CXX_FLAGS "-std=c++20 -Wdeprecated-declarations")
endif()

add_executable(${PROJECT_NAME}
	./src/main.cpp
	./src/Core/BasicMain.cpp
	./src/Core/ThreadManager.cpp
	./src/Platform/OpenGL/Window.cpp
	./src/Platform/OpenGL/Main.cpp
)

target_link_directories(${PROJECT_NAME} PUBLIC ${GLFW3_DIR}/lib)
target_link_libraries(${PROJECT_NAME} glfw3)

target_include_directories(${PROJECT_NAME} PUBLIC ${GLFW3_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC include)