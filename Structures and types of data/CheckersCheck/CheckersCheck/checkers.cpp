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
			//��� ������ �� ������� ����� ������? ��� ����� ������?
			if ((MyBoard->field[i][j].is_correct) && (MyBoard->field[i][j].is_buisy) && (MyBoard->field[i][j].is_white))
			{
				if (i == width - 1)// ���� ����������� ������?
				{
					if (MyBoard->field[i][j].is_king) //������ ������?
					{
						if (!(j >= 1 ? MyBoard->field[i - 1][j - 1].is_buisy : true && j < width - 1 ? MyBoard->field[i - 1][j + 1].is_buisy : true))// ������ ���� ��������?
						{
							return true;
						}
						else continue;
					}

					if ((j >= 1 ? (MyBoard->field[i - 1][j - 1].is_buisy && !(MyBoard->field[i - 1][j - 1].is_white)) : false)
						&& (!(j >= 2 ? MyBoard->field[i - 2][j - 2].is_buisy : true)) //�� ���� ���� ��������� ���� ����� ������?

						|| ( (j < width - 1 ? (MyBoard->field[i - 1][j + 1].is_buisy && !(MyBoard->field[i - 1][j + 1].is_white)) : false)
						&& (!(j < width - 2 ? MyBoard->field[i - 2][j + 2].is_buisy : true)) ))
					
					{
						return true;
					}
					else continue;					
				}
				else
				{
					if (!( ((j > 0) ? MyBoard->field[i + 1][j - 1].is_buisy : true) && ((j < width - 1) ? MyBoard->field[i + 1][j + 1].is_buisy : true)))//�������� ������ ������ ��������?
					{
						return true;
					}
					else
					{
						if (!((j > 0 ? MyBoard->field[i + 1][j - 1].is_white : true) && ((j < width - 1 ? MyBoard->field[i + 1][j + 1].is_white : true))))//������ ���� ������ �������?
						{
							if (!((j > 1 ? MyBoard->field[i + 2][j - 2].is_buisy : true) && (j < (width - 1) ? MyBoard->field[i + 2][j + 2].is_buisy : true))) //�� ���� ���� ���� ��������� ������?
							{
								return true;
							}
							else 
							{
								if ((j >= 1 ? (MyBoard->field[i - 1][j - 1].is_buisy && !(MyBoard->field[i - 1][j - 1].is_white)) : false)
									&& (!(j >= 2 ? MyBoard->field[i - 2][j - 2].is_buisy : true)) //�� ���� ���� ��������� ���� ����� ������?

									|| ((j < width - 1 ? (MyBoard->field[i - 1][j + 1].is_buisy && !(MyBoard->field[i - 1][j + 1].is_white)) : false)
									&& (!(j < width - 2 ? MyBoard->field[i - 2][j + 2].is_buisy : true)) ))
								{
									return true;
								}
								else continue;
							}
							continue;
						}
						else if (MyBoard->field[i][j].is_king) //������ ������?
						{
							if (!(((j > 0)&&(i > 0) ? MyBoard->field[i - 1][j - 1].is_buisy : true) && ((j < width - 1) && (i > 0) ? MyBoard->field[i - 1][j + 1].is_buisy : true)))//�������� ������ ����� ��������?
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