#ifndef SQUARE_H
#define SQUARE_H

#include <ostream>
#include <string>
#include "Rectangle.h"
#include "Point2D.h"

class Square : public Rectangle {
	public:
		Square();
		Square(std::string color, Point2D* vertices);
		
		void print() override;
		void set_vertices(Point2D* vertices) override;
		
		friend std::ostream& operator<<(std::ostream& out, const Square& square);
	
	private:
		static bool check(Point2D* vertices);
};

#endif

