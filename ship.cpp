#include <assert.h>
#include "ship.h"

using namespace std;

/********************************************/
/* NE MODIFIEZ PAS LA MÉTHODE QUI SUIT !    */
/* ELLE EST DÉJÀ PLEINEMENT FONCTIONNELLE ! */
/********************************************/
void Ship::updatePoints() {
	for (int i = 0; i < _length; i++) {
		if (_direction == HORIZONTAL) {
			_points[i].setX(_x + i);
			_points[i].setY(_y);
		}

		else {
			_points[i].setX(_x);
			_points[i].setY(_y + i);
		}
	}
}

void Ship::updateSunkStatus()
{
	int cpt = 0;
	for (int i = 0; i < _length; i++)
	{
		if (_points[i].getColor() == SHIP_SUNK_COLOR) {
			cpt++;
		}
	}

	if (cpt == _length) {
		_hasSunk = true;
	}

	else _hasSunk = false;
}

/******************************************************/
/* CODEZ ICI LES AUTRES MÉTHODES DE LA CLASSE "SHIP". */
/******************************************************/

Ship::Ship(const std::string& name, int length)
{
	_name = name;
	_length = length;
	_x = _y = 0;
	_direction = HORIZONTAL;
	_hasSunk = false;

	updatePoints();
}

Ship::~Ship()
{
	_name = "";
	_x = _y = 0;
	_direction = HORIZONTAL;
	_length = 0;
	_hasSunk = false;
}

int Ship::getLength() const
{
	return _length;
}

const Direction& Ship::getDirection() const
{
	return _direction;
}

bool Ship::getSunkStatus() const
{
	return _hasSunk;
}

void Ship::setPosition(int x, int y)
{
	assert(x > 0 && y > 0);

	_x = x;
	_y = y;

	updatePoints();
}

void Ship::setLength(int length)
{
	assert(length > 0 && length < SHIP_MAX_LENGTH);
	_length = length;

	updatePoints();
}

void Ship::setDirection(const Direction& direction)
{
	_direction = direction;
	updatePoints();
}

void Ship::rotate()
{
	if (_direction = HORIZONTAL) {
		_direction = VERTICAL;
	}

	else _direction = HORIZONTAL;

	updatePoints();
}

void Ship::hide()
{
	for (int i = 0; i < _length - 1; i++)
	{
		_points[i].setColor(SHIP_HIDDEN_COLOR);
	}
}

bool Ship::checkCollision(const Ship& otherShip) const
{
	for (int i = 0; i < _length; i++)
	{
		for (int j = 0; j < otherShip._length; j++)
		{
			if (_points[i] == otherShip._points[j]) {
				return true;
			}
		}
	}
	return false;
}

int Ship::placeHit(const Point& hitPosition)
{
	for (int i = 0; i < _length - 1; i++) {
		if (hitPosition.getX() != _points[i].getX() || hitPosition.getY() != _points[i].getY()) {
			return 0;
		}
	}

	for (int i = 0; i < _length - 1; i++) {
		if ((hitPosition.getX() == _points[i].getX() && hitPosition.getY() == _points[i].getY()) && _hasSunk == true) {
			return 1;
		}
	}

	for (int i = 0; i < _length - 1; i++) {
		if ((hitPosition.getX() == _points[i].getX() && hitPosition.getY() == _points[i].getY()) && (_hasSunk == false && _points[i].getColor() == SHIP_HIT_COLOR)) {
			return 2;
		}
	}

	for (int i = 0; i < _length - 1; i++) {
		if ((hitPosition.getX() == _points[i].getX() && hitPosition.getY() == _points[i].getY()) && (_hasSunk == false && _points[i].getColor() != SHIP_HIT_COLOR)) {
			_points[i].setColor(SHIP_HIT_COLOR);
			updateSunkStatus();
			return 3;
		}
	}	
}

void Ship::print(std::ostream& output) const
{
	output << _name << " (" << _length << " )";
}

void Ship::draw(std::ostream& output) const
{
	for (int i = 0; i < _length; i++)
	{
		_points[i].draw(output);
	}
}

void Ship::read(std::istream& input)
{
	string name;
	int length;
	char skip;

	input >> name >> skip >> length >> skip;

	_name = name;
	setLength(length);
}

std::ostream& operator<<(std::ostream& output, const Ship& ship)
{
	ship.draw(output);
	return output;
}

std::istream& operator>>(std::istream& input, Ship& ship)
{
	ship.read(input);
	return input;
}


