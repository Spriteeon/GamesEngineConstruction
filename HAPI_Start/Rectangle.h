#pragma once
#include <algorithm>

class Rectangle
{
public:
	int left{ 0 }; //X value for left hand side
	int right{ 0 }; //X value for right hand side
	int top{ 0 }; //Y value for Top
	int bottom{ 0 }; //Y value for bottom 

	Rectangle();
	~Rectangle();
	bool CompletelyOutside(const Rectangle& other);
	bool CompletelyInside(const Rectangle& other);
	void ClipTo(const Rectangle& other);
	void Translate(int dx, int dy);

	//Returns width and height of Rectangles
	int Width() const { return right - left; }
	int Height() const { return bottom - top; }

};

