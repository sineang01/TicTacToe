cmake_minimum_required (VERSION 3.1 FATAL_ERROR)
project (TicTacToe VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(WarningLevel)
include(WarningAsError)

set (SOURCES_DIR_GAME
	game/cell.hpp
	game/config.cpp
	game/config.hpp
	game/mapping.cpp
	game/mapping.hpp
	game/player.hpp
	game/symbols.hpp
	game/tictactoe.cpp 
	game/tictactoe.hpp
)

set (SOURCES_DIR_UTILS
	utils/console.cpp
	utils/console.hpp
	utils/console_abstract.hpp
	utils/console_windows.cpp
	utils/console_windows.hpp
	utils/console_linux.cpp
	utils/console_linux.hpp
	utils/point.hpp
	utils/random.cpp
	utils/random.hpp
	utils/utils.hpp
)

set (SOURCES_OTHERS
	main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES_OTHERS} ${SOURCES_DIR_GAME} ${SOURCES_DIR_UTILS}) 
source_group("src" FILES ${SOURCES_OTHERS})
source_group("src\\game" FILES ${SOURCES_DIR_GAME})
source_group("src\\utils" FILES ${SOURCES_DIR_UTILS})

# Compile options (warnings)
set_warning_level()
set_warning_as_error()
