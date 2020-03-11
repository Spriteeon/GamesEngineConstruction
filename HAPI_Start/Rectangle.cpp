#include "Rectangle.h"

Rectangle::Rectangle()
{
	
}

Rectangle::~Rectangle()
{

}

bool Rectangle::CompletelyOutside(const Rectangle& other) //Returns true if Rectangles dont overlap
{

	if (other.right < left)
	{
		return true;
	}
	if (other.left > right)
	{
		return true;
	}
	if (other.top > bottom)
	{
		return true;
	}
	if (other.bottom < top)
	{
		return true;
	}

	return false;

}

bool Rectangle::CompletelyInside(const Rectangle& other) //Returns true if one Rectangle is inside another
{

	if (left < other.left)
	{
		return false;
	}
	if (right > other.right)
	{
		return false;
	}
	if (top < other.top)
	{
		return false;
	}
	if (bottom > other.bottom)
	{
		return false;
	}

	return true;

}

void Rectangle::ClipTo(const Rectangle& other) //Function needed for clipping
{

	left = std::max(left, other.left);
	top = std::max(top, other.top);
	right = std::min(right, other.right);
	bottom = std::min(bottom, other.bottom);

}

void Rectangle::Translate(int dx, int dy) //Move Rectangle
{

	left += dx;
	right += dx;
	top += dy;
	bottom += dy;

}
