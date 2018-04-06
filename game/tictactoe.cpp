/****************************************************************************************
** Copyright (C) 2016-2018 Simone Angeloni
** This file is part of Tic Tac Toe.
**
** Tic Tac Toe is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Tic Tac Toe is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Tic Tac Toe. If not, see <http://www.gnu.org/licenses/>
**
****************************************************************************************/

#include "stdafx.h"

#include "tictactoe.hpp"
#include "mapping.hpp"

#include <sstream>
#include <string>
#include <thread>
#include <chrono>
#include <iostream>

namespace Game
{

	const unsigned int TicTacToe::BOARD_CELL_WIDTH = 5;
	const unsigned int TicTacToe::BOARD_CELL_HEIGHT = 3;
	const unsigned int TicTacToe::BOARD_CELL_SEPARATOR_H = 1;
	const unsigned int TicTacToe::BOARD_OFFSET_LEFT = 5;
	const unsigned int TicTacToe::BOARD_OFFSET_RIGHT = 2;
	const unsigned int TicTacToe::BOARD_OFFSET_TOP = 3;
	const unsigned int TicTacToe::BOARD_OFFSET_BOTTOM = 1;

	const unsigned int TicTacToe::TIMER_AI_THINKING_MSECS = 500;
	const unsigned int TicTacToe::TIMER_GAME_OVER_MSECS = 2500;

	TicTacToe::TicTacToe(const GameParams & gameParams) 
		:mGameParams(gameParams)
	{
	}

	TicTacToe::~TicTacToe()
	{
	}

	bool TicTacToe::init()
	{
		const size_t sizePlayers = mGameParams.players.size();
		game_fatal_assert(sizePlayers >= 2);

		mPlayers.resize(sizePlayers);
		for (size_t i = 0; i < sizePlayers; ++i)
		{
			mPlayers[i].setSymbolOwned(PlayerSymbolMapping::instance().player(i).mSymbol);
			mPlayers[i].setHuman(mGameParams.players.at(i));
		}

		game_fatal_assert(boardSize() > 0);
		mBoard.resize(boardSize());

		displayBoardEmpty();

		return reset();
	}

	bool TicTacToe::reset()
	{
		mCurrentPlayer = 0;

		unsigned i = 0;
		for (; i < boardSize(); ++i)
		{
			mBoard[i].setFree();
		}

		for (i = 0; i < mGameParams.unavailableCells; ++i)
		{
			const unsigned int id = Utils::Random::get(boardSize() - 1);
			if (!mBoard[id].locked())
			{
				mBoard[id].setLocked(true);
			}
			else
			{
				--i;
			}
		}

		return true;
	}

	void TicTacToe::displayBoardEmpty() const
	{
		auto fill = [](char c, unsigned int length) -> void
		{
			for (unsigned int i = 0; i < length; ++i)
				std::cout << c;
		};

		auto spacing = [=](bool drawVSeparator, bool drawHSeparator) -> void
		{
			const char symbolV = drawVSeparator ? '|' : ' ';
			const char symbolH = drawHSeparator ? '_' : ' ';

			fill(' ', BOARD_OFFSET_LEFT);

			for (unsigned int column = 0; column < mGameParams.boardWidth; ++column)
			{
				std::cout << symbolV;
				fill(symbolH, BOARD_CELL_WIDTH);
			}

			std::cout << symbolV << std::endl;
		};

		// BOARD_OFFSET_TOP
		std::cout << std::endl << std::endl;
		spacing(false, true);

		// BOARD_CELL_HEIGHT
		for (unsigned int row = 0; row < mGameParams.boardHeight; ++row)
		{
			spacing(true, false);
			spacing(true, false);
			spacing(true, true);
		}

		// Row numbers
		unsigned int coord = 0;
		for (unsigned int row = 0; row < mGameParams.boardHeight; ++row)
		{
			coord = 4 + row * 3;
			Utils::Console::instance()->write((char)(row + 49), Utils::PointUInt(2, coord));
		}

		// Column letters
		for (unsigned int column = 0; column < mGameParams.boardWidth; ++column)
		{
			coord = 8 + column * 6;
			Utils::Console::instance()->write((char)(column + 65), Utils::PointUInt(coord, 1));
		}
	}

	void TicTacToe::displayBoardCells() const
	{
		unsigned int x = 0, y = 0;
		for (unsigned int row = 0; row < mGameParams.boardHeight; ++row)
		{
			for (unsigned int column = 0; column < mGameParams.boardWidth; ++column)
			{
				x = BOARD_OFFSET_LEFT + BOARD_CELL_SEPARATOR_H + (BOARD_CELL_WIDTH / 2) + (column * BOARD_CELL_WIDTH) + column;
				y = BOARD_OFFSET_TOP + (BOARD_CELL_HEIGHT / 2) + (row * BOARD_CELL_HEIGHT);

				const Cell & c = cell(Utils::PointUInt(column, row));
				Utils::Console::instance()->write(printSymbol(c.symbol()), Utils::PointUInt(x, y));
			}
		}
	}

	void TicTacToe::displayPlayerInfo() const
	{
		const PlayerList::size_type playersSize = mPlayers.size();
		for (PlayerList::size_type i = 0; i < playersSize; ++i)
		{
			std::ostringstream ss;
			ss << "Player" << i + 1 << " (" << printSymbol(mPlayers.at(i).symbolOwned()) << ") - Score: " << mPlayers.at(i).score();

			Utils::Console::instance()->write(ss.str(), Utils::PointUInt(consoleBoardRight() + BOARD_OFFSET_RIGHT, BOARD_OFFSET_TOP + static_cast<unsigned int>(i)));
		}
	}

	void TicTacToe::displayTurn() const
	{
		std::ostringstream ss;
		ss << "Player" << mCurrentPlayer + 1 << " playing...";

		Utils::Console::instance()->write(ss.str(), Utils::PointUInt(consoleBoardRight() + BOARD_OFFSET_RIGHT, BOARD_OFFSET_TOP + static_cast<unsigned int>(mPlayers.size()) + 1));
	}

	bool TicTacToe::update()
	{
		displayBoardCells();
		displayPlayerInfo();
		displayTurn();

		const Utils::PointUInt coordScreen(BOARD_OFFSET_LEFT, consoleBoardBottom() + BOARD_OFFSET_BOTTOM);
		Utils::Console::instance()->clear(coordScreen);

		Player & currentPlayer = mPlayers.at(mCurrentPlayer);
		Utils::PointUInt playerMovePos;
		if (currentPlayer.ai())
		{
			playerMovePos = playingAI(currentPlayer);
		}
		else
			if (currentPlayer.human())
			{
				playerMovePos = playingHuman(currentPlayer);
			}

		const bool gameOverPlayerWon = playerWon(playerMovePos, currentPlayer);
		const bool gameOverBoardFull = boardFull();
		if (gameOverPlayerWon || gameOverBoardFull)
		{
			displayBoardCells();

			if (gameOverPlayerWon)
			{
				currentPlayer.increaseScore();

				std::ostringstream ss;
				ss << "Player" << mCurrentPlayer + 1 << " WON!!!!!";

				Utils::Console::instance()->write(ss.str(), Utils::PointUInt(consoleBoardRight() + BOARD_OFFSET_RIGHT, BOARD_OFFSET_TOP + static_cast<unsigned int>(mPlayers.size()) + 1));
			}
			else
			{
				Utils::Console::instance()->write("No Winner :(", Utils::PointUInt(consoleBoardRight() + BOARD_OFFSET_RIGHT, BOARD_OFFSET_TOP + static_cast<unsigned int>(mPlayers.size()) + 1));
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(TIMER_GAME_OVER_MSECS));
			reset();
		}
		else
		{
			changeToNextPlayer();
		}

		return true;
	}

	bool TicTacToe::playerWon(const Utils::PointUInt & lastMovePos, const Player & currentPlayer) const
	{
		const Symbol winCellType = currentPlayer.symbolOwned();

		auto checkWinConditionH = [=](Symbol winCellType) -> bool
		{
			unsigned int counter = 0;

			for (unsigned int column = 0; column < mGameParams.boardWidth; ++column)
			{
				const Cell & c = cell(Utils::PointUInt(column, lastMovePos.y()));
				if (c.owner() && c.owner()->symbolOwned() == winCellType)
				{
					++counter;
					if (counter >= mGameParams.winConditionCells)
						return true;
				}
				else
				{
					counter = 0;
				}
			}

			return false;
		};

		auto checkWinConditionV = [=](Symbol winCellType) -> bool
		{
			unsigned int counter = 0;

			for (unsigned int row = 0; row < mGameParams.boardHeight; ++row)
			{
				const Cell & c = cell(Utils::PointUInt(lastMovePos.x(), row));
				if (c.owner() && c.owner()->symbolOwned() == winCellType)
				{
					++counter;
					if (counter >= mGameParams.winConditionCells)
						return true;
				}
				else
				{
					counter = 0;
				}
			}

			return false;
		};

		if (checkWinConditionH(winCellType))
			return true;

		if (checkWinConditionV(winCellType))
			return true;

		return false;
	}

	bool TicTacToe::boardFull() const
	{
		CellList::const_iterator itEnd = mBoard.end();
		for (CellList::const_iterator it = mBoard.begin(); it != itEnd; ++it)
		{
			if (it->free())
				return false;
		}

		return true;
	}

	Utils::PointUInt TicTacToe::findFreeCellPosition() const
	{
		game_fatal_assert(!boardFull());

		Utils::PointUInt point;

		do
		{
			point.ry() = Utils::Random::get(mGameParams.boardHeight - 1);
			point.rx() = Utils::Random::get(mGameParams.boardWidth - 1);
		} while (!cell(point).free());

		return point;
	}

	Utils::PointUInt TicTacToe::playingAI(const Player & player)
	{
		game_fatal_assert(!boardFull());

		auto writeTimedMessage = [](const std::string & text, const Utils::PointUInt & coordinate) -> void
		{
			Utils::Console::instance()->write(text, coordinate);
			std::this_thread::sleep_for(std::chrono::milliseconds(TIMER_AI_THINKING_MSECS));
		};

		static const std::string s = "AI doing its best";

		Utils::PointUInt coordinate(BOARD_OFFSET_LEFT, consoleBoardBottom() + BOARD_OFFSET_BOTTOM);
		Utils::Console::instance()->cursorAt(coordinate);

		writeTimedMessage(s, coordinate);
		coordinate.rx() += static_cast<unsigned int>(s.length());
		writeTimedMessage(".", coordinate);
		coordinate.rx() += 1;
		writeTimedMessage(".", coordinate);
		coordinate.rx() += 1;
		writeTimedMessage(".", coordinate);

		const Utils::PointUInt point = findFreeCellPosition();
		cell(point).setOwner(&player);
		return point;
	}

	Utils::PointUInt TicTacToe::playingHuman(const Player & player)
	{
		game_fatal_assert(!boardFull());

		Utils::PointUInt point;

		do
		{
			while (keepWaitingForValidRow(point.ry())) { /* do nothing */ }
			while (keepWaitingForValidColumn(point.rx())) { /* do nothing */ }
		} while (!cell(point).free());

		cell(point).setOwner(&player);
		return point;
	}

	bool TicTacToe::keepWaitingForValidRow(unsigned int & row) const
	{
		static const std::string s("Please insert row and press ENTER: ");

		Utils::PointUInt coordScreen(BOARD_OFFSET_LEFT, consoleBoardBottom() + BOARD_OFFSET_BOTTOM);
		Utils::Console::instance()->write(s, coordScreen);

		Utils::PointUInt coordCursor(BOARD_OFFSET_LEFT + static_cast<unsigned int>(s.length()), consoleBoardBottom() + BOARD_OFFSET_BOTTOM);
		Utils::Console::instance()->cursorAt(coordCursor);

		std::string input;
		std::cin >> input;

		char rowStr = input.at(0);

		if (!isdigit(rowStr))
			return true;

		row = rowStr - '0' - 1;
		if (row >= mGameParams.boardHeight)
			return true;

		return false;
	}

	bool TicTacToe::keepWaitingForValidColumn(unsigned int & column) const
	{
		static const std::string s("Please insert column and press ENTER: ");

		Utils::PointUInt coordScreen(BOARD_OFFSET_LEFT, consoleBoardBottom() + BOARD_OFFSET_BOTTOM);
		Utils::Console::instance()->write(s, coordScreen);

		Utils::PointUInt coordCursor(BOARD_OFFSET_LEFT + static_cast<unsigned int>(s.length()), consoleBoardBottom() + BOARD_OFFSET_BOTTOM);
		Utils::Console::instance()->cursorAt(coordCursor);

		std::string input;
		std::cin >> input;

		char columnStr = input.at(0);

		if (!isalpha(columnStr))
			return true;

		columnStr = static_cast<char>(tolower(columnStr));
		column = columnStr - 'a';
		if (column >= mGameParams.boardWidth)
			return true;

		return false;
	}

	unsigned int TicTacToe::changeToNextPlayer()
	{
		++mCurrentPlayer;
		if (mCurrentPlayer >= mPlayers.size())
			mCurrentPlayer = 0;

		return mCurrentPlayer;
	}

	const Cell & TicTacToe::cell(const Utils::PointUInt & point) const
	{
		const unsigned int id = point.y() * mGameParams.boardWidth + point.x();
		game_fatal_assert(id <= boardSize() - 1);

		return mBoard[id];
	}

	Cell & TicTacToe::cell(const Utils::PointUInt & point)
	{
		const unsigned int id = point.y() * mGameParams.boardWidth + point.x();
		game_fatal_assert(id <= boardSize() - 1);

		return mBoard[id];
	}

} // namespace Game
