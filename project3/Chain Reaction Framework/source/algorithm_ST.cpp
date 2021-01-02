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

//----------copy board
class Cell_c : public Cell
{
private:
    int orbs_num; // The number of the orbs on the cell
    int capacity; // The max number of the orbs of a cell
    char color;   // The color of the cell, 'w'(No one has placed the orbs), 'r'(Red Player) and 'b'(Blue player)
    bool explode;

public:
    Cell_c()
    {
        orbs_num = 0, capacity = 8, color = 'w', explode = false;
    }
};

class Board_c
{
private:
    Cell_c cells[ROW][COL];                 // The 5*6 board whose index (0,0) is start from the upper left corner
    void cell_reaction_marker();            // After the explosion, mark all the cell that  will explode in next iteration
    bool cell_is_full(Cell_c *cell);        // Check wether the cell is full of orbs and set the explosion variable to be true
    void add_orb(int i, int j, char color); // Add orb into the cell (i, j)
    void cell_reset(int i, int j);          // Reset the cell to the initial state (color = 'w', orb_num = 0)
    void cell_explode(int i, int j);        // The explosion of cell (i, j). It will add the orb into neighbor cells
    void cell_chain_reaction(char color);   // If there is aa explosion, check wether the chain reaction is active

public:
    Board_c(Board board);

    // The basic functions of the Board
    int get_orbs_num(int i, int j);
    int get_capacity(int i, int j);
    char get_cell_color(int i, int j);

    bool place_orb(int i, int j, char color);          // Use this function to place a orb into a cell
    void print_current_board(int i, int j, int round); // Print out the current state of the hole board

    bool win_the_game(char color); // The function that is used to check wether the player wins the game after his/her placemnet operation
};

bool Board_c::place_orb(int i, int j, char color)
{

    //if (index_range_illegal(i, j) || !placement_illegal(*player, cells[i][j]))
    //{
    int temp = cells[i][j].get_orbs_num();
    temp += 1;
    cells[i][j].set_orbs_num(temp);
    cells[i][j].set_color(color);
    /*}
    else
    {
        player->set_illegal();
        return false;
    }*/

    if (cell_is_full(&cells[i][j]))
    {
        cell_explode(i, j);
        cell_reaction_marker();
        cell_chain_reaction(color);
    }

    return true;
}

bool Board_c::cell_is_full(Cell_c *cell)
{
    if (cell->get_orbs_num() >= cell->get_capacity())
    {
        cell->set_explode(true);
        return true;
    }
    else
        return false;
}

void Board_c::add_orb(int i, int j, char color)
{
    int orb_num = cells[i][j].get_orbs_num();
    orb_num++;
    cells[i][j].set_orbs_num(orb_num);
    cells[i][j].set_color(color);
}

void Board_c::cell_reset(int i, int j)
{
    cells[i][j].set_orbs_num(0);
    cells[i][j].set_explode(false);
    cells[i][j].set_color('w');
}

void Board_c::cell_explode(int i, int j)
{

    int orb_num;
    char color = cells[i][j].get_color();

    cell_reset(i, j);

    if (i + 1 < ROW)
    {
        add_orb(i + 1, j, color);
    }
    if (j + 1 < COL)
    {
        add_orb(i, j + 1, color);
    }
    if (i - 1 >= 0)
    {
        add_orb(i - 1, j, color);
    }
    if (j - 1 >= 0)
    {
        add_orb(i, j - 1, color);
    }
    if (i + 1 < ROW && j - 1 >= 0)
    {
        add_orb(i + 1, j - 1, color);
    }
    if (i - 1 >= 0 && j - 1 >= 0)
    {
        add_orb(i - 1, j - 1, color);
    }
    if (i + 1 < ROW && j + 1 < COL)
    {
        add_orb(i + 1, j + 1, color);
    }
    if (i - 1 >= 0 && j + 1 < COL)
    {
        add_orb(i - 1, j + 1, color);
    }
}

void Board_c::cell_reaction_marker()
{

    // Mark the next cell whose number of orbs is equal to the capacity
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            cell_is_full(&cells[i][j]);
        }
    }
}

void Board_c::cell_chain_reaction(char color)
{

    bool chain_reac = true;

    while (chain_reac)
    {

        chain_reac = false;

        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COL; j++)
            {
                if (cells[i][j].get_explode())
                {
                    cell_explode(i, j);
                    chain_reac = true;
                }
            }
        }

        if (win_the_game(color))
        {
            return;
        }

        cell_reaction_marker();
    }
}

bool Board_c::win_the_game(char color)
{

    bool win = true;

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (cells[i][j].get_color() == color || cells[i][j].get_color() == 'w')
                continue;
            else
            {
                win = false;
                break;
            }
        }
        if (!win)
            break;
    }
    return win;
}

int Board_c::get_orbs_num(int i, int j)
{
    return cells[i][j].get_orbs_num();
}

int Board_c::get_capacity(int i, int j)
{
    return cells[i][j].get_capacity();
}

char Board_c::get_cell_color(int i, int j)
{
    return cells[i][j].get_color();
}

Board_c::Board_c(Board board)
{

    ////// Initialize the borad with correct capacity //////
    // The corners of the board
    cells[0][0].set_capacity(3), cells[0][5].set_capacity(3),
        cells[4][0].set_capacity(3), cells[4][5].set_capacity(3);

    // The edges of the board
    cells[0][1].set_capacity(5), cells[0][2].set_capacity(5), cells[0][3].set_capacity(5), cells[0][4].set_capacity(3),
        cells[1][0].set_capacity(5), cells[2][0].set_capacity(5), cells[3][0].set_capacity(5),
        cells[1][5].set_capacity(5), cells[2][5].set_capacity(5), cells[3][5].set_capacity(5),
        cells[4][1].set_capacity(5), cells[4][2].set_capacity(5), cells[4][3].set_capacity(5), cells[4][4].set_capacity(3);

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            cells[i][j].set_color(board.get_cell_color(i, j));
            cells[i][j].set_capacity(board.get_capacity(i, j));
            cells[i][j].set_orbs_num(board.get_orbs_num(i, j));
        }
    }
}

//----------

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
