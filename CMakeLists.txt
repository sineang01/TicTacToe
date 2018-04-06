cmake_minimum_required (VERSION 3.2 FATAL_ERROR)
project (TicTacToe VERSION 1.0 LANGUAGES CXX)

set (HEADERS_DIR_GAME
	game/cell.hpp
	game/config.hpp
	game/mapping.hpp
	game/player.hpp
	game/symbols.hpp
	game/tictactoe.hpp
)

set (HEADERS_DIR_UTILS
	utils/console.hpp
	utils/console_abstract.hpp
	utils/console_windows.hpp
	utils/point.hpp
	utils/random.hpp
	utils/utils.hpp
)

set (HEADERS
	stdafx.h
	${HEADERS_DIR_GAME}
	${HEADERS_DIR_UTILS}
)

set (SOURCES_DIR_GAME
	game/config.cpp
	game/mapping.cpp
	game/tictactoe.cpp 
)

set (SOURCES_DIR_UTILS
	utils/console.cpp
	utils/console_windows.cpp
)

set (SOURCES
	main.cpp
	stdafx.cpp 
	${SOURCES_DIR_GAME}
	${SOURCES_DIR_UTILS}
)

add_executable(TicTacToe ${HEADERS} ${SOURCES}) 
source_group("Header Files\\game" FILES ${HEADERS_DIR_GAME})
source_group("Source Files\\game" FILES ${SOURCES_DIR_GAME})
source_group("Header Files\\utils" FILES ${HEADERS_DIR_UTILS})
source_group("Source Files\\utils" FILES ${SOURCES_DIR_UTILS})

target_include_directories(TicTacToe PUBLIC utils .)
