#pragma once

#include "checkers.h"
#include <SFML/graphics.hpp>
#include <iostream>
#include "checkers.h"

class graphics
{
public:
	int draw();
private:
	int CoordToNumber(double coord);
};

