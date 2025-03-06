#include <iostream>
#include <fstream>
#include "grid.h"

using namespace std;


/***********************************************/
/* NE MODIFIEZ PAS LES MÉTHODES QUI SUIVENT !  */
/* ELLES SONT DÉJÀ PLEINEMENT FONCTIONNELLES ! */
/***********************************************/
bool Grid::placeShips() {
	bool collides;
	int maxX, maxY;

	for (int i = 0; i < _nbShips; i++) {
		do {
			if ((_ships[i].getLength() > (GRID_WIDTH - 2)) ||
				(_ships[i].getLength() > (GRID_HEIGHT - 2)))
				return false;

			collides = false;
			_ships[i].setDirection(Direction(rand() % 2));

			if (_ships[i].getDirection() == HORIZONTAL) {
				maxX = GRID_INNER_MAX_X - _ships[i].getLength();
				maxX = ((maxX < GRID_INNER_MIN_X) ? GRID_INNER_MIN_X : maxX);
				maxY = GRID_INNER_MAX_Y;
			}

			else {
				maxX = GRID_INNER_MAX_X;
				maxY = GRID_INNER_MAX_Y - _ships[i].getLength();
				maxY = ((maxY < GRID_INNER_MIN_Y) ? GRID_INNER_MIN_Y : maxY);
			}

			_ships[i].setPosition((rand() % (maxX - GRID_INNER_MIN_X + 1) + GRID_INNER_MIN_X),
				(rand() % (maxY - GRID_INNER_MIN_Y + 1) + GRID_INNER_MIN_Y));

			for (int j = 0; j < i; j++) {
				if ((i != j) && _ships[i].checkCollision(_ships[j])) {
					collides = true;
					break;
				}
			}
		} while (collides);
	}

	return true;
}





void Grid::printShipsStatus(ostream& output) const {
	goToXY(GRID_SHIPS_STATUS_X, GRID_SHIPS_STATUS_Y);
	output << "BATEAUX RESTANTS";

	goToXY((GRID_SHIPS_STATUS_X + 23), GRID_SHIPS_STATUS_Y);
	output << "BATEAUX COULES";

	for (int i = 1; i <= _nbShips; i++) {
		if (_ships[i - 1].getSunkStatus())
			goToXY((GRID_SHIPS_STATUS_X + 23), (GRID_SHIPS_STATUS_Y + i));

		else
			goToXY((GRID_SHIPS_STATUS_X), (GRID_SHIPS_STATUS_Y + i));

		_ships[i - 1].print(output);
	}
}



/******************************************************/
/* CODEZ ICI LES AUTRES MÉTHODES DE LA CLASSE "GRID". */
/******************************************************/

Grid::Grid() : _gridOutline(GRID_INNER_MIN_X - 1, GRID_INNER_MIN_Y - 1, GRID_WIDTH, GRID_HEIGHT), _nbShips(0), _nbMissedHits(0) {
	initShips();
}

Grid::~Grid()
{
	_nbShips = 0;
	_nbMissedHits = 0;
}

int Grid::getNbRemainingShips() const
{
	int count = 0;
	for (int i = 0; i < _nbShips; i++)
	{
		if (!_ships[i].getSunkStatus()) {
			count++;
		}
	}
	return count;
}

bool Grid::placeHit(const Point& hitPosition)
{

	if (hitPosition.getX() > GRID_INNER_MAX_X || hitPosition.getX() < GRID_INNER_MIN_X ||
		hitPosition.getY() > GRID_INNER_MAX_Y || hitPosition.getY() < GRID_INNER_MIN_Y)
	{
		return false;
	}


	for (int i = 0; i < _nbMissedHits; i++)
	{
		if (_missedHits[i] == hitPosition)
		{
			return false;
		}
	}


	for (int i = 0; i < _nbShips; i++)
	{
		if (_ships[i].placeHit(hitPosition))
		{

			if (_ships[i].getSunkStatus())
			{
				return false;
			}
			return true;
		}
	}


	_missedHits[_nbMissedHits++] = hitPosition;
	_missedHits[_nbMissedHits - 1].setColor(GRID_MISSED_HITS_COLOR);
	return false;
}




void Grid::draw(std::ostream& output) const
{
	output << _gridOutline << std::endl;


	for (int i = 0; i < _nbShips; i++) {
		const Ship& ship = _ships[i];
		ship.draw(output);  
	}


	for (int i = 0; i < _nbMissedHits; i++) {
		output << _missedHits[i] << std::endl;
	}
}


std::ostream& operator<<(std::ostream& output, const Grid& grid)
{
	grid.draw(output);
	return output;
}




void Grid::read(std::istream& input)
{
	string shipName;
	char ignoreIt;      
	int shipLength;
	_nbShips = 0;

	while (input >> shipName >> ignoreIt >> shipLength >> ignoreIt) {
		if (_nbShips >= SHIP_MAX_NB) {
			break;
		}
		_ships[_nbShips] = Ship(shipName, shipLength);
		_nbShips++;
	}
}

std::istream& operator>>(std::istream& input, Grid& grid)
{
	grid.read(input);
	return input;
}

bool Grid::initShips()
{
	ifstream File(GRID_SHIPS_FILENAME);
	if (!File) {
		cout << "Could not open file " << GRID_SHIPS_FILENAME << endl;
		return false;
	}

	cout << "File opened successfully!" << endl;  
	read(File);
	File.close();

	if (placeShips()) {
		hideShips();
		return true;
	}
	else {
		cout << "Could not place ships on the grid." << endl;
		exit(1);
	}
}


void Grid::hideShips()
{
	for (int i = 0; i < _nbShips; i++) {
		_ships[i].hide();
	}
}