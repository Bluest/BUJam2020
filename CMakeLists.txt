cmake_minimum_required(VERSION 2.6)

project(Jam)

include_directories(
	contrib/include
	src/Engine
)

link_directories(
	${CMAKE_SOURCE_DIR}/contrib/lib
)

add_library(Engine
	src/Engine/Component.cpp
	src/Engine/Component.h
	src/Engine/Core.cpp
	src/Engine/Core.h
	src/Engine/Engine.h
	src/Engine/Entity.cpp
	src/Engine/Entity.h
	src/Engine/Input.cpp
	src/Engine/Input.h
	src/Engine/Time.cpp
	src/Engine/Time.h
)
target_link_libraries(Engine SDL2 SDL2main)

add_executable(Game
	src/Game/main.cpp
)
target_link_libraries(Game Engine)

add_custom_command(TARGET Game
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
		"${PROJECT_SOURCE_DIR}/contrib/lib/SDL2.dll"
		$<TARGET_FILE_DIR:Game>
)
