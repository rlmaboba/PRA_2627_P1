#include "Rectangle.h"
#include <cmath>
#include <stdexcept>

Rectangle::Rectangle() : Shape(), vs(new Point2D[N_VERTICES]) {
	vs[0] = Point2D(-1, 0.5);
	vs[1] = Point2D(1, 0.5);
	vs[2] = Point2D(1, -0.5);
	vs[3] = Point2D(-1, -0.5);
}

Rectangle::Rectangle(std::string color, Point2D* vertices) : Shape(color), vs(new Point2D[N_VERTICES]) {
	try {
		set_vertices(vertices);
	} catch (...) {
		delete[] vs;
		throw;
	}
}

Rectangle::Rectangle(const Rectangle &r) : Shape(r.color), vs(new Point2D[N_VERTICES]) {
	for (int i = 0; i < N_VERTICES; i++) {
		vs[i] = r.vs[i];
	}
}

Rectangle::~Rectangle() {
	delete[] vs;
}

Point2D Rectangle::get_vertex(int ind) const {
	if (ind < 0 || ind >= N_VERTICES) {
		throw std::out_of_range("Invalid vertex index");
	}
	
	return vs[ind];
}

Point2D Rectangle::operator[](int ind) const {
	return get_vertex(ind);
}

bool Rectangle::check(Point2D* vertices) {
	if (vertices == nullptr) {
		return false;
	}
	
	double d01 = Point2D::distance(vertices[0], vertices[1]);
	double d12 = Point2D::distance(vertices[1], vertices[2]);
	double d23 = Point2D::distance(vertices[2], vertices[3]);
	double d30 = Point2D::distance(vertices[3], vertices[0]);
	
	const double EPSILON = 1e-9;
	
	return std::fabs(d01 - d23) < EPSILON && std::fabs(d12 - d30) < EPSILON;
}

void Rectangle::set_vertices(Point2D* vertices) {
	if (!check(vertices)) {
		throw std::invalid_argument("Invalid rectangle vertices");
	}
	
	for (int i = 0; i < N_VERTICES; i++) {
		vs[i] = vertices[i];
	}
}

Rectangle& Rectangle::operator=(const Rectangle &r) {
	if (this != &r) {
		set_color(r.color);
		
		for (int i = 0; i < N_VERTICES; i++) {
			vs[i] = r.vs[i];
		}
	}
	
	return *this;
}

double Rectangle::area() const {
	double width = Point2D::distance(vs[0], vs[1]);
	double height = Point2D::distance(vs[1], vs[2]);
	
	return width * height;
}

double Rectangle::perimeter() const {
	double width = Point2D::distance(vs[0], vs[1]);
	double height = Point2D::distance(vs[1], vs[2]);
	
	return 2 * (width + height);
}

void Rectangle::translate(double incX, double incY) {
	for (int i = 0; i < N_VERTICES; i++) {
		vs[i].x += incX;
		vs[i].y += incY;
	}
}

void Rectangle::print() {
	std::cout << *this << std::endl;
}

std::ostream& operator<<(std::ostream &out, const Rectangle &r) {
	out << "[Rectangle: color = " << r.color << "; vertices = ";
	
	for (int i = 0; i < Rectangle::N_VERTICES; i++) {
		if (i > 0){
			out << ", ";
		}
		
		out << r.vs[i];
	}
	
	out << "]";
	return out;
}

