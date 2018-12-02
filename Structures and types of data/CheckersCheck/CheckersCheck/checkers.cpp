#include "checkers.h"

bool possibilityToMove(board * MyBoard)
{
	const size_t width = MyBoard->field.size();
	if (width == 0) //if size of board is 0 
		return false;

	for (int i = 0; i < width; ++i) //
	{
		for (int j = 0; j < width; ++j)
		{
			//Это клетка по которой можно ходить? Это белая фигура?
			if ((MyBoard->field[i][j].is_correct) && (MyBoard->field[i][j].is_buisy) && (MyBoard->field[i][j].is_white))
			{
				if (i >= width - 1)// Выше отсутствуют клетки?
				{
					if (!((  j >= 1 ? MyBoard->field[i - 1][j - 1].is_buisy: true )&&( j < width - 1 ? MyBoard->field[i - 1][j + 1].is_buisy : true)))// клетки ниже свободны?
					{
						if (MyBoard->field[i][j].is_king) //Играем дамкой?
						{
							return true;
						}
						else continue;
					}
					if (!( ((j >= 2) ? MyBoard->field[i - 2][j - 2].is_buisy : true) 
						&& ((i >= 2) && (j < width - 2) ? MyBoard->field[i - 2][j + 2].is_buisy : true) //Клетки ниже заняты черными и за ними есть свободные?
						&& ((j > 1) && (j < width - 1) ? ( MyBoard->field[i - 1][j - 1].is_white && MyBoard->field[i - 1][j + 1].is_white) : true) ))
					{
						return true;
					}
					else continue;
				}
				else
				{
					if (!( ((j > 0) ? MyBoard->field[i + 1][j - 1].is_buisy : true) && ((j < width - 1) ? MyBoard->field[i + 1][j + 1].is_buisy : true)))//Соседние клетки сверху свободны?
					{
						return true;
					}
					else
					{
						if (!((j > 0 ? MyBoard->field[i + 1][j - 1].is_white : true) && ((j < width - 1 ? MyBoard->field[i + 1][j + 1].is_white : true))))//клетки выше заняты черными?
						{
							if (!((j > 1 ? MyBoard->field[i + 2][j - 2].is_buisy : true) && (j < (width - 1) ? MyBoard->field[i + 2][j + 2].is_buisy : true))) //За ними выше есть свободные клетки?
							{
								return true;
							}
							else if (i > 2)
							{
								if (!((j > 1 ? MyBoard->field[i - 2][j - 2].is_buisy : true) && (j < (width - 1) ? MyBoard->field[i - 2][j + 2].is_buisy : true)) //Клетки ниже заняты черными и за ними есть свободные?
									&& (!(j > 0 ? MyBoard->field[i - 1][j - 1].is_white: true) && (j < width - 1 ? MyBoard->field[i - 1][j + 1].is_white : true)))
								{
									return true;
								}
								else continue;
							}
							else continue;
						}
						else if (MyBoard->field[i][j].is_king) //Играем дамкой?
						{
							if (!(((j > 0)&&(i > 0) ? MyBoard->field[i - 1][j - 1].is_buisy : true) && ((j < width - 1) && (i > 0) ? MyBoard->field[i - 1][j + 1].is_buisy : true)))//Соседние клетки снизу свободны?
							{
								return true;
							}
							else continue;
						}
						else continue;
					}
				}
			}
			else continue;
		}
	}
	return false;
}