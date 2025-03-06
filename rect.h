#pragma once
#include "point.h"

class Rect
{
public:

	Rect();
	Rect(int x, int y, int w = 0, int h = 0);
	~Rect();

	int getWidth() const;
	int getHeight() const;
	Point& getPositon();
	const Point& getPosition() const;

	void setWidth(const int w);
	void setHeight(const int h);
	void setSize(const int w, const int h);
	void setRectangle(const int x, const int y, const int w, const int h);

	void read(std::istream& entree);
	void print(std::ostream& os) const;
	void draw(std::ostream& os) const;

	int surface()const;
	int perimetre()const;

	const Rect& operator=(const Rect& autreRect);
	bool operator==(const Rect& autreRect)const;
	bool operator!=(const Rect& autreRect)const;
	bool operator<(Rect& autreRect)const;
	bool operator>(Rect& autreRect)const;
	bool operator>=(Rect& autreRect)const;
	bool operator<=(Rect& autreRect)const;

private:
	Point _coord;
	int _w;
	int _h;
};

std::istream& operator>>(std::istream& flux, Rect& autreRect);

std::ostream& operator<<(std::ostream& flux, const Rect& autreRect);