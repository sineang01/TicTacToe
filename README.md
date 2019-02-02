Tic Tac Toe
===========

Tic Tac Toe 1.0 is a C++11 console implementation of the classic game also known as noughts and crosses.

![Tic Tac Toe](https://i.ibb.co/V91gmQr/ttt.png)

Info
====

Tic Tac Toe provides a C++ implementation of the game where you can play using the Operative System console.
There are a few differences with the classical Tic Tac Toe game:
* The board can be rectangular
* The board width can vary between 3 and 9
* The board height can vary between 3 and 9
* Up to 6 players can play simultaneously
* Each of the 6 players can be an AI (thought I didn't write any intelligent algorithm for them)
* Some cells can be locked (no player can use these cells) 

Installation
============

Download the repository and compile on your local machine. You'll need CMake.
```
cd repository_folder
mkdir build
cd build
cmake ..
make
```

License
=======

Tic Tac Toe is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Tic Tac Toe is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Tic Tac Toe.  If not, see <http://www.gnu.org/licenses/>.
