#ifndef RECT_H
#define RECT_H

struct Rect
{
	float x;
	float y;

	float w;
	float h;

	float red;
	float green;
	float blue;

	bool selected;
	bool resizing;
	int num;

	Rect();

	Rect(float x, float y, float w, float h, float red, float green, float blue, int num);

	void draw();

	bool contains(float x, float y);

	void select();
	void deselect();
};

#endif
