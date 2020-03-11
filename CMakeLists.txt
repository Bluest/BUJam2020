cmake_minimum_required(VERSION 2.6)

project(Jam)

include_directories(
	SDL2/include
	src/Engine
)

link_directories(
	${CMAKE_SOURCE_DIR}/SDL2/lib
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
	src/Engine/Sprite.h
	src/Engine/SpriteManager.cpp
	src/Engine/SpriteManager.h
	src/Engine/SpriteRenderer.cpp
	src/Engine/SpriteRenderer.h
	src/Engine/Time.cpp
	src/Engine/Time.h
)
target_link_libraries(Engine SDL2 SDL2main SDL2_image)

add_executable(Game
	src/Game/main.cpp
	src/Game/PlayerMovement.cpp
	src/Game/PlayerMovement.h
	src/Game/Game.h
	src/Game/Game.cpp
	src/Game/Map.cpp
	src/Game/Map.h
	src/Game/Patrol.h
	src/Game/Patrol.cpp
)
target_link_libraries(Game Engine)

add_custom_command(TARGET Game
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
		"${PROJECT_SOURCE_DIR}/SDL2/lib/SDL2.dll"
		$<TARGET_FILE_DIR:Game>
	COMMAND ${CMAKE_COMMAND} -E copy
		"${PROJECT_SOURCE_DIR}/SDL2/lib/SDL2_image.dll"
		$<TARGET_FILE_DIR:Game>
	COMMAND ${CMAKE_COMMAND} -E copy
		"${PROJECT_SOURCE_DIR}/SDL2/lib/zlib1.dll"
		$<TARGET_FILE_DIR:Game>
	COMMAND ${CMAKE_COMMAND} -E copy
		"${PROJECT_SOURCE_DIR}/SDL2/lib/libpng16-16.dll"
		$<TARGET_FILE_DIR:Game>
)
