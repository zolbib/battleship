#pragma once

class Point
{

private:
	int _x, _y;
	int _color;

public:
	Point();
	Point(int x, int y);
	Point(const Point& p);
	~Point();

	int getX() const;
	int getY() const;
	int getColor() const;
	Point getPoint() const;

	void setX(const int x);
	void setY(const int y);
	void setPosition(const int x, const int y);
	void setColor(const int color);
	void setPoint(const int x, const int y, const int color);

	void draw(std::ostream& os) const;
	void print(std::ostream& os) const;
	void read(std::istream& entree);

	const Point& operator=(const Point& autrePoint);
	bool operator==(const Point& autrePoint)const;
	bool operator!=(const Point& autrePoint)const;
	Point operator+(const Point& autrePoint);
	Point operator-(const Point& autrePoint);

	friend int distance(Point& p1, Point& p2);

};

void goToXY(int xpos, int ypos);

std::ostream& operator<<(std::ostream& flux, const Point& autrePoint);

std::istream& operator>>(std::istream& flux, Point& autrePoint);
