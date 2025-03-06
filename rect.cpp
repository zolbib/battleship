
#include <iostream>
#include <assert.h>
#include <Windows.h>
#include "point.h"
#include "rect.h"

using namespace std;

Rect::Rect()
{
	_w = 0;
	_h = 0;
}

Rect::Rect(int x, int y, int w, int h)
{
	_coord.setPosition(x, y);
	_w = w;
	_h = h;
}

Rect::~Rect()
{
	_w = 0;
	_h = 0;
}

int Rect::getWidth() const
{
	return _w;
}

int Rect::getHeight() const
{
	return _h;
}

Point& Rect::getPositon()
{
	return _coord;
}

const Point& Rect::getPosition() const
{
	return _coord;
}

void Rect::setWidth(const int w)
{
	assert(w > 0);
	_w = w;
}

void Rect::setHeight(const int h)
{
	assert(h > 0);
	_h = h;
}

void Rect::setSize(const int w, const int h)
{
	setWidth(w);
	setHeight(h);
}

void Rect::setRectangle(const int x, const int y, const int w, const int h)
{
	_coord.setPosition(x, y);
	setSize(w, h);
}

void Rect::read(istream& entree)
{
	char skip;

	_coord.read(entree);
	entree >> _w >> skip >> _h;
}

void Rect::print(ostream& os)const
{
	_coord.print(os);
	os << " " << _w << " X " << _h;

}

void Rect::draw(std::ostream& os) const
{
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOuput, _coord.getColor());

	for (int i = 0; i < _w; i++) {

		goToXY(getPosition().getX() + i, getPosition().getY());
		os << "\xFE";

	}

	for (int i = 0; i < _h; i++) {

		goToXY(getPosition().getX(), getPosition().getY() + i);

		os << "\xFE" << endl;
	}

	for (int i = 0; i < _h; i++) {

		goToXY(getPosition().getX() + _w, getPosition().getY() + i);

		os << "\xFE" << endl;
	}

	for (int i = 0; i < _w + 1; i++) {

		goToXY(getPosition().getX() + i, getPosition().getY() + _h);

		os << "\xFE";
		
	}

}

int Rect::surface()const
{
	return _h * _w;
}

int Rect::perimetre()const
{
	return (_h * 2) + (_w * 2);
}

const Rect& Rect::operator=(const Rect& autreRect)
{
	_w = autreRect._w;
	_h = autreRect._h;
	_coord = autreRect._coord;

	return *this;
}

bool Rect::operator==(const Rect& autreRect)const
{
	return _w == autreRect._w &&
		_h == autreRect._h;
}

bool Rect::operator!=(const Rect& autreRect)const
{
	return !(_w == autreRect._w &&
		_h == autreRect._h);
}

bool Rect::operator<(Rect& autreRect)const
{
	return surface() < autreRect.surface();
}

bool Rect::operator>(Rect& autreRect)const
{
	return surface() > autreRect.surface();
}

bool Rect::operator>=(Rect& autreRect) const
{

	return surface() >= autreRect.surface();
}

bool Rect::operator<=(Rect& autreRect)const
{
	return surface() <= autreRect.surface();
}

std::istream& operator>>(std::istream& flux, Rect& autreRect)
{
	autreRect.read(flux);
	return flux;
}

std::ostream& operator<<(std::ostream& flux, const Rect& autreRect)
{
	autreRect.draw(flux);
	return flux;
}
