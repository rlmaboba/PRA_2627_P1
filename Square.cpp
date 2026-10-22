#include "Square.h"
#include <stdexcept>

Square::Square() : Rectangle(){
	Point2D vertices[4] = {Point2D(-1,1), Point2D(1,1), Point2D(1,-1), Point2D(-1,-1)};
	Rectangle::set_vertices(vertices);
}

Square::Square(std::string color, Point2D* vertices) : Rectangle(color, vertices){
	if (!check(vertices)) {
		throw std::invalid_argument("Provided vertices do not build a valid square!");
	}
}

bool Square::check(Point2D* vertices){
	double d01 = Point2D::distance(vertices[0], vertices[1]);
	double d12 = Point2D::distance(vertices[1], vertices[2]);
	double d23 = Point2D::distance(vertices[2], vertices[3]);
	double d30 = Point2D::distance(vertices[3], vertices[0]);
	
	return d01 > 0 && d01 == d12 && d12 == d23 && d23 == d30;
}

void Square::set_vertices(Point2D* vertices){
	if (!check(vertices)) {
		throw std::invalid_argument("Provided vertices do not build a valid square!");
	}
	
	Rectangle::set_vertices(vertices);
}

void Square::print(){
	std::cout << *this;
}

std::ostream& operator<<(std::ostream& out, const Square& square){ 
	out << "[Square: color = " << square.color;
	
	for (int i = 0; i < 4; i++) {
		out << "; v" << i << " = " << square.vs[i];
	}
	
	out << "]";
	return out;
}

