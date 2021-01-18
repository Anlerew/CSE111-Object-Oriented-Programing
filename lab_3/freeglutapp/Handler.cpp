#include "Handler.h"
#include <math.h>
#include <time.h>
#include <iostream>

Handler::Handler(int numRects, bool random)
{
	srand(time(NULL));

	for (int i = 0; i < numRects; i++)
	{
		float w = (rand() % 30 + 40) / 100.0;
		float h = (rand() % 30 + 40) / 100.0;
		float x = xBounds(((rand() % 90) / 100.0) * negOrPos(), w);
		float y = yBounds(((rand() % 90) / 100.0) * negOrPos(), h);

		if (!random)
		{
			if (i % 5 == 0)
				rects.push_back(new Rect(x, y, w, h, 1, 0, 0, i));
			if (i % 5 == 1)
				rects.push_back(new Rect(x, y, w, h, 0, 1, 0, i));
			if (i % 5 == 2)
				rects.push_back(new Rect(x, y, w, h, 0, 0, 1, i));
			if (i % 5 == 3)
				rects.push_back(new Rect(x, y, w, h, 0, 1, 1, i));
			if (i % 5 == 4)
				rects.push_back(new Rect(x, y, w, h, 1, 1, 0, i));
		}

		if (random)
			rects.push_back(new Rect(x, y, w, h, rand() % 256 / 255.0, rand() % 256 / 255.0, rand() % 256 / 255.0, i));
	}
}

void Handler::draw()
{
	for (Rect *r : rects)
	{
		r->draw();
	}
}

void Handler::mouseFunc(float mx, float my, int s)
{

	if (s)
		for (Rect *r : rects)
			r->resizing = false;

	if (!s)
	{
		for (auto r = rects.begin(); r != rects.end(); r++)
		{
			if ((*r)->contains(mx, my))
			{

				(*r)->select();
				xO = mx - (*r)->x;
				yO = (*r)->y - my;

				grabLeeway = .0150;

				if (xO > (*r)->w - grabLeeway && xO < (*r)->w + grabLeeway && yO > (*r)->h - grabLeeway && yO < (*r)->h + grabLeeway)
				{
					(*r)->resizing = true;
				}

				Rect *temp = *r;

				rects.erase(r);

				rects.push_front(temp);

				break;
			}
			else
				(*r)->deselect();
		}
	}
}

void Handler::drag(float mx, float my)
{
	for (auto r = rects.begin(); r != rects.end(); r++)
	{
		if ((*r)->selected)
		{
			if ((*r)->resizing)
			{

				if ((mx - (*r)->x) > grabLeeway)
				{
					(*r)->w = mx - (*r)->x;
				}

				if (-my + (*r)->y > grabLeeway)
				{
					(*r)->h = -my + (*r)->y;
				}
			}
			else
			{

				(*r)->x = mx - xO;
				(*r)->y = my + yO;
			}
		}
	}
}

int Handler::negOrPos()
{
	if (rand() % 2)
		return 1;
	return -1;
}

float Handler::xBounds(float x, float w)
{
	if (x + w > 1)
	{
		return .99 - w;
	}
	return x;
}

float Handler::yBounds(float y, float h)
{
	if (y - h < -1)
	{
		return -.99 + h;
	}
	return y;
}