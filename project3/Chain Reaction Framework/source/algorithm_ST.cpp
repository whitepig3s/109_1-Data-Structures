#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"

using namespace std;

/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions 
 * 1. ~ 4. are listed in next block)
 * 
 * The STL library functions is not allowed to use.
******************************************************/

/*************************************************************************
 * 1. int board.get_orbs_num(int row_index, int col_index)
 * 2. int board.get_capacity(int row_index, int col_index)
 * 3. char board.get_cell_color(int row_index, int col_index)
 * 4. void board.print_current_board(int row_index, int col_index, int round)
 * 
 * 1. The function that return the number of orbs in cell(row, col)
 * 2. The function that return the orb capacity of the cell(row, col)
 * 3. The function that return the color fo the cell(row, col)
 * 4. The function that print out the current board statement
*************************************************************************/

void algorithm_A(Board board, Player player, int index[])
{

	//////your algorithm design///////////
	srand(time(NULL) * time(NULL));
	int row, col;
	int color = player.get_color();

	while (1)
	{
		/*if (board.get_cell_color(0, 0) == color || board.get_cell_color(0, 0) == 'w')
		{
			row = 0;
			col = 0;
			break;
		}
		else if (board.get_cell_color(0, 5) == color || board.get_cell_color(0, 5) == 'w')
		{
			row = 0;
			col = 5;
			break;
		}
		else if (board.get_cell_color(4, 0) == color || board.get_cell_color(4, 0) == 'w')
		{
			row = 4;
			col = 0;
			break;
		}
		else if (board.get_cell_color(4, 5) == color || board.get_cell_color(4, 5) == 'w')
		{
			row = 4;
			col = 5;
			break;
		}*/

		row = rand() % 5;
		col = rand() % 6;
		if (board.get_cell_color(row, col) == color || board.get_cell_color(row, col) == 'w')
			break;
	}

	index[0] = row;
	index[1] = col;
}
