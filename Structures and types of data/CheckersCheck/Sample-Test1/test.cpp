#include "gtest/gtest.h"
#include "../CheckersCheck/checkers.cpp"

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(CorrectInput, EmptyField) {
	board MyBoard;
    EXPECT_FALSE(possibilityToMove(&MyBoard));
}

TEST(CorrectInput, White_on_the_top) {
	board MyBoard;
	MyBoard.field[7][0].is_buisy = true;
	MyBoard.field[7][0].is_white = true;
	EXPECT_FALSE(possibilityToMove(&MyBoard));
}

TEST(CorrectInput, White_near_the_top) {
	board MyBoard;
	MyBoard.field[6][0].is_buisy = true;
	MyBoard.field[6][0].is_white = true;
	EXPECT_TRUE(possibilityToMove(&MyBoard));
}
