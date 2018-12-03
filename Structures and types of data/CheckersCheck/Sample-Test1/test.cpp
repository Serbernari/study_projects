#include "gtest/gtest.h"
#include "../CheckersCheck/checkers.h"

TEST(CorrectInput, EmptyField) {

	board MyBoard;
	bool a = possibilityToMove(&MyBoard);
    EXPECT_FALSE(a);
}
int main(int argc, char **argv) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}