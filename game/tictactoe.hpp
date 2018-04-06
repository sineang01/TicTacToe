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

#pragma once
#include "cell.hpp"
#include "player.hpp"
#include <utils.hpp>
#include <vector>
#include <algorithm>

namespace Game
{

	class TicTacToe final
	{
	public:
		struct GameParams
		{
			GameParams() :boardWidth(0), boardHeight(0), unavailableCells(0), winConditionCells(0) {}

			unsigned int boardWidth; /** number of columns */
			unsigned int boardHeight; /** number of rows */
			unsigned int unavailableCells;
			std::vector<bool> players; /** true = human, false = ai */
			unsigned int winConditionCells; /** number of consecutive cells with the same type to win a match */
		};

	public:
		TicTacToe(const GameParams & gameParams);
		~TicTacToe();

		bool init();
		bool reset();
		bool update();

		inline unsigned int consoleBoardRight() const { return BOARD_OFFSET_LEFT + ((BOARD_CELL_WIDTH + 1) * mGameParams.boardWidth) + 1; }
		inline unsigned int consoleBoardBottom() const { return BOARD_OFFSET_TOP + (BOARD_CELL_HEIGHT * mGameParams.boardHeight); }

	private:
		inline unsigned int boardSize() const { return mGameParams.boardHeight * mGameParams.boardWidth; }

		const Cell & cell(const Utils::PointUInt & point) const;
		Cell & cell(const Utils::PointUInt & point);

		Utils::PointUInt findFreeCellPosition() const;

		void displayBoardEmpty() const;
		void displayBoardCells() const;
		void displayPlayerInfo() const;
		void displayTurn() const;

		bool keepWaitingForValidRow(unsigned int & row) const;
		bool keepWaitingForValidColumn(unsigned int & column) const;

		Utils::PointUInt playingAI(const Player & player);
		Utils::PointUInt playingHuman(const Player & player);

		unsigned int changeToNextPlayer();

		bool playerWon(const Utils::PointUInt &lastMovePos, const Player &currentPlayer) const;
		bool boardFull() const;

	private:
		const GameParams & mGameParams;

		using CellList = std::vector<Cell>;
		CellList mBoard;

		using PlayerList = std::vector<Player>;
		PlayerList mPlayers;

		unsigned int mCurrentPlayer = 0;

	private:
		static const unsigned int BOARD_CELL_WIDTH;
		static const unsigned int BOARD_CELL_HEIGHT;
		static const unsigned int BOARD_CELL_SEPARATOR_H;
		static const unsigned int BOARD_OFFSET_LEFT;
		static const unsigned int BOARD_OFFSET_RIGHT;
		static const unsigned int BOARD_OFFSET_TOP;
		static const unsigned int BOARD_OFFSET_BOTTOM;

		static const unsigned int TIMER_AI_THINKING_MSECS;
		static const unsigned int TIMER_GAME_OVER_MSECS;
	};

} // namespace Game
