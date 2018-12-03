#include "gtest/gtest.h"
#include "../CheckersCheck/checkers.cpp"

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(CheckerTest, EmptyField) {
	board MyBoard;
    EXPECT_FALSE(possibilityToMove(&MyBoard));
}
TEST(CheckerTest, White_on_the_top) {
	board MyBoard;
	MyBoard.field[7][0].is_buisy = true;
	MyBoard.field[7][0].is_white = true;
	EXPECT_FALSE(possibilityToMove(&MyBoard));
}
TEST(CheckerTest, White_near_the_top) {
	board MyBoard;
	MyBoard.field[6][0].is_buisy = true;
	MyBoard.field[6][0].is_white = true;
	EXPECT_TRUE(possibilityToMove(&MyBoard));
}
TEST(CheckerTest, White_near_the_black_and_border) {
	board MyBoard;
	MyBoard.field[6][1].is_buisy = true;
	MyBoard.field[5][0].is_buisy = true;
	MyBoard.field[5][0].is_white = true;
	EXPECT_TRUE(possibilityToMove(&MyBoard));
}
TEST(CheckerTest, White_must_take_back_right) {
	board MyBoard;
	MyBoard.field[6][4].is_buisy = true;
	MyBoard.field[7][3].is_buisy = true;
	MyBoard.field[7][3].is_white = true;
	EXPECT_TRUE(possibilityToMove(&MyBoard));
}
TEST(CheckerTest, White_must_take_back_left) {
	board MyBoard;
	MyBoard.field[6][2].is_buisy = true;
	MyBoard.field[7][3].is_buisy = true;
	MyBoard.field[7][3].is_white = true;
	EXPECT_TRUE(possibilityToMove(&MyBoard));
}
TEST(CheckerTest, White_must_take_forward_right) {
	board MyBoard;
	MyBoard.field[6][3].is_buisy = true;
	MyBoard.field[5][2].is_buisy = true;
	MyBoard.field[5][2].is_white = true;
	EXPECT_TRUE(possibilityToMove(&MyBoard));
}
TEST(CheckerTest, White_must_take_forward_left) {
	board MyBoard;
	MyBoard.field[6][1].is_buisy = true;
	MyBoard.field[5][2].is_buisy = true;
	MyBoard.field[5][2].is_white = true;
	EXPECT_TRUE(possibilityToMove(&MyBoard));
}
TEST(CheckerTest, White_cannot_take_forward) {
	board MyBoard;
	MyBoard.field[7][0].is_buisy = true;
	MyBoard.field[7][4].is_buisy = true;
	MyBoard.field[6][3].is_buisy = true;
	MyBoard.field[6][1].is_buisy = true;
	MyBoard.field[5][2].is_buisy = true;
	MyBoard.field[5][2].is_white = true;
	EXPECT_FALSE(possibilityToMove(&MyBoard));
}
TEST(CheckerTest, White_cannot_take_backward) {
	board MyBoard;
	MyBoard.field[7][0].is_buisy = true;
	MyBoard.field[7][4].is_buisy = true;
	MyBoard.field[6][3].is_buisy = true;
	MyBoard.field[6][1].is_buisy = true;
	MyBoard.field[3][0].is_buisy = true;
	MyBoard.field[3][4].is_buisy = true;
	MyBoard.field[4][3].is_buisy = true;
	MyBoard.field[4][1].is_buisy = true;
	MyBoard.field[5][2].is_buisy = true;
	MyBoard.field[5][2].is_white = true;
	EXPECT_FALSE(possibilityToMove(&MyBoard));
}
TEST(CheckerTest, White_in_centre) {
	board MyBoard;
	MyBoard.field[5][4].is_buisy = true;
	MyBoard.field[5][4].is_white = true;
	EXPECT_TRUE(possibilityToMove(&MyBoard));
}
TEST(CheckerTest, King_can_go_back) {
	board MyBoard;
	MyBoard.field[7][4].is_buisy = true;
	MyBoard.field[7][4].is_white = true;
	MyBoard.field[7][4].is_king = true;
	EXPECT_TRUE(possibilityToMove(&MyBoard));
}


