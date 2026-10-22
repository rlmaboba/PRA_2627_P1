#include "Drawing.h"
#include "Circle.h"
#include "Square.h"

Drawing::Drawing(){
	shapes = new std::vector<Shape*>();
}

Drawing::~Drawing(){
	delete shapes;
}

void Drawing::add_front(Shape* shape){
	shapes->insert(shapes->begin(), shape);
}

void Drawing::add_back(Shape* shape){
	shapes->push_back(shape);
}

void Drawing::print_all(){
	for (Shape* shape : *shapes) {
		shape->print();
	}
}

double Drawing::get_area_all_circles(){
	double total = 0.0;
	for (Shape* shape : *shapes) {
		Circle* circle = dynamic_cast<Circle*>(shape);
		if (circle != nullptr) {
			total += circle->area();
		}
	}
	return total;
}

void Drawing::move_squares(double incX, double incY){
	for (Shape* shape : *shapes) {
		Square* square = dynamic_cast<Square*>(shape);
		if (square != nullptr){
			square->translate(incX, incY);
		}
	}
}

