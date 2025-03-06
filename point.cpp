#include <assert.h>
#include <iostream>
#include <Windows.h>
#include "point.h"

using namespace std;

Point::Point() {
	_x = _y = 0;
	_color = 7;
}

Point::Point(int x, int y) {
	_x = x;
	_y = y;
	_color = 7;
}

Point::Point(const Point& p)
{
	_x = p._x;
	_y = p._y;
	_color = p._color;
}

Point::~Point()
{
	_x = _y = _color = 0;
}

int Point::getX() const
{
	return _x;
}

int Point::getY() const
{
	return _y;
}

int Point::getColor() const
{
	return _color;
}

Point Point::getPoint() const
{
	return *this;
}

void Point::setX(const int x)
{
	assert(x >= 0);
	_x = x;
}

void Point::setY(const int y)
{
	assert(y >= 0);
	_y = y;
}

void Point::setPosition(const int x, const int y)
{
	assert(x >= 0);
	assert(y >= 0);
	_x = x;
	_y = y;
}

void Point::setColor(const int color)
{
	assert(color >= 0);
	_color = color;
}

void Point::setPoint(const int x, const int y, const int color)
{
	assert(x >= 0);
	assert(y >= 0);
	assert(color >= 0);
	_x = x;
	_y = y;
	_color = color;
}

void Point::draw(ostream& os) const
{

	goToXY(_x, _y);

	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOuput, _color);

	cout << "\xFE";

}

void Point::print(ostream& os) const
{
	os << "(" << _x << "," << _y << ") " << _color << endl;
}

void Point::read(std::istream& entree)
{
	char skip;
	entree >> skip >> _x >> skip >> _y >> skip >> _color;

}

const Point& Point::operator=(const Point& autrePoint)
{
	_x = autrePoint._x;
	_y = autrePoint._y;
	_color = autrePoint._color;

	return *this;
}

bool Point::operator==(const Point& autrePoint)const
{
	return _x == autrePoint._x &&
		_y == autrePoint._y &&
		_color == autrePoint._color;
}

bool Point::operator!=(const Point& autrePoint)const
{
	return !(_x == autrePoint._x &&
		_y == autrePoint._y &&
		_color == autrePoint._color);
}

Point Point::operator+(const Point& autrePoint)
{
	Point p(*this);

	p._x = _x + autrePoint._x;
	p._y = _y + autrePoint._y;

	return p;
}

Point Point::operator-(const Point& autrePoint)
{
	Point p(*this);

	p._x = _x - autrePoint._x;
	p._y = _y - autrePoint._y;

	return p;
}

int distance(Point& p1, Point& p2)
{
	return sqrt(pow(p2._x - p1._x, 2) + pow(p2._y - p1._y, 2));
}

void goToXY(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos;
	scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);

}

std::ostream& operator<<(std::ostream& flux, const Point& autrePoint)
{
	autrePoint.print(flux);
	return flux;
}

std::istream& operator>>(std::istream& flux, Point& autrePoint)
{
	int x, y, color;

	flux >> x >> y >> color;

	autrePoint.setX(x);
	autrePoint.setY(y);
	autrePoint.setColor(color);

	return flux;

}
