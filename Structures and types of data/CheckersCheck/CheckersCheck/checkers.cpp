#include "checkers.h"

bool possibilityToMove(board * MyBoard)
{
	int width;
	if (!(width = MyBoard->field.size())) //if size of board is 0 
	{
		return false;
	}

	for (int i = 0; i <= width; ++i)
	{
		for (int j = 0; j <= width; ++j)
		{
			if ((MyBoard->field[i][j].is_correct) && (MyBoard->field[i][j].is_buisy) && (MyBoard->field[i][j].is_white))
			{
				if (i == width) //if man on top of board
				{
					if (MyBoard->field[i][j].is_king) //if man already a king 
					{
						if ((j != 0) && (j != width)) //if not near the border
						{
							if ((MyBoard->field[i - 1][j - 1].is_buisy && MyBoard->field[i - 1][j + 1].is_buisy)) //if neigbors not buisy
							{
								if (!(MyBoard->field[i - 2][j - 2].is_buisy && MyBoard->field[i - 2][j + 2].is_buisy) //if can chop
									&& (!(MyBoard->field[i - 1][j - 1].is_white && MyBoard->field[i - 1][j + 1].is_white)))
								{
									return true;
								}
								else return false;
							}
							else return true;
						}
						else if (j == 0)
						{
							if (MyBoard->field[i - 1][j + 1].is_buisy) //if neigbor are buisy
							{
								if (!(MyBoard->field[i - 2][j + 2].is_buisy) //if can chop
									&& (!MyBoard->field[i - 1][j + 1].is_white))
								{
									return true;
								}
								else return false;
							}
							else return true;
						}
						else if (j == width)
						{
							if (MyBoard->field[i - 1][j - 1].is_buisy) //if neigbor are buisy
							{
								if (!(MyBoard->field[i - 2][j - 2].is_buisy) //if can chop
									&& (!(MyBoard->field[i - 1][j - 1].is_white)))
								{
									return true;
								}
								else return false;
							}
							else return true;
						}
					}
					else return false;
				}
				else 
				{
					if ((j != 0) && (j != width)) //if not near the border
					{
						if ((MyBoard->field[i + 1][j - 1].is_buisy && MyBoard->field[i + 1][j + 1].is_buisy)) //if neigbors not buisy
						{
							if (!(MyBoard->field[i + 2][j - 2].is_buisy && MyBoard->field[i + 2][j + 2].is_buisy)  //if can chop forward
								&& (!(MyBoard->field[i + 1][j - 1].is_white && MyBoard->field[i + 1][j + 1].is_white)))
							{
								return true;
							}
							if (!(My))
							else return false;
						}
						else return true;
					}
					else if (j == 0)
					{
						if (MyBoard->field[i + 1][j + 1].is_buisy) //if neigbor are buisy
						{
							if (!(MyBoard->field[i + 2][j + 2].is_buisy) //if can chop
								&& (!MyBoard->field[i + 1][j + 1].is_white))
							{
								return true;
							}
							else return false;
						}
						else return true;
					}
					else if (j == width)
					{
						if (MyBoard->field[i + 1][j - 1].is_buisy) //if neigbor are buisy
						{
							if (!(MyBoard->field[i + 2][j - 2].is_buisy) //if can chop
								&& (!MyBoard->field[i + 1][j - 1].is_white))
							{
								return true;
							}
							else return false;
						}
						else return true;
					}
				}
				else
				{
					if ((j != 0) && (j != width)) //if not near the border
					{
						if ((MyBoard->field[i + 1][j - 1].is_buisy && MyBoard->field[i + 1][j + 1].is_buisy)) //if neigbors not buisy
						{
							if ( (!(MyBoard->field[i + 2][j - 2].is_buisy && MyBoard->field[i + 2][j + 2].is_buisy))  //if can chop
								&& (!(MyBoard->field[i + 1][j - 1].is_white && MyBoard->field[i + 1][j + 1].is_white)) )
							{
								return true;
							}
							else return false;
						}
						else return true;
					}
					else if (j == 0)
					{
						if (MyBoard->field[i + 1][j + 1].is_buisy) //if neigbor are buisy
						{
							if (!(MyBoard->field[i + 2][j + 2].is_buisy) //if can chop
								&& !(MyBoard->field[i + 1][j + 1].is_white))
							{
								return true;
							}
							else return false;
						}
						else return true;
					}
					else if (j == width)
					{
						if (MyBoard->field[i + 1][j - 1].is_buisy) //if neigbor are buisy
						{
							if (!(MyBoard->field[i + 2][j - 2].is_buisy) //if can chop
								&& !(MyBoard->field[i + 1][j - 1].is_white))
							{
								return true;
							}
							else return false;
						}
						else return true;
					}
				}
			}
		}
	}
	return false;
}
