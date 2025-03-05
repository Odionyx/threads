#include "shape.h"

void Shape::shift(int m, int n){
    for( int i{0}; i< size; ++i){
        this-> x[i]+= m;
        this-> y[i]+= n;
    }
}

void Shape::scaleX(int a){
    for( int i{0}; i< size; ++i){
        this-> x[i]*= a;
    }
}

void Shape::scaleY(int d){
    for( int i{0}; i< size; ++i){
        this-> y[i]*= d;
    }
}

void Shape::scale(int s){
    for( int i{0}; i< size; ++i){
        this-> x[i]/= s;
        this-> y[i]/= s;
    }
}

Shape::Shape(std::vector<int>& _x, std::vector<int>& _y){
    for( int i{0}; i< size; ++i){
        this->x.push_back(_x[i]);
        this->y.push_back(_y[i]);
    }
}

Square::Square(std::vector<int>& _x, std::vector<int>& _y)
              : Shape(_x, _y){}

void Cube::shift(int m, int n, int k){
    for( int i{0}; i< size; ++i){
        this-> x[i]+= m;
        this-> y[i]+= n;
        this-> z[i]+= k;
    }
}

void Cube::scale(int s){
    for( int i{0}; i< size; ++i){
        this-> x[i]/= s;
        this-> y[i]/= s;
        this-> z[i]/= s;
    }
}

void Cube::scaleZ(int e){
    for( int i{0}; i< size; ++i){
        this-> z[i]*= e;
    }
}

Cube::Cube(std::vector<int> &_x, std::vector<int> &_y,
           std::vector<int> &_z): Square(_x, _y){
    for( int i{0}; i< size; ++i){
        this->z.push_back(_z[i]);
    }
}

Circle::Circle(std::vector<int> &_x, std::vector<int> &_y,
               double R): Shape(_x, _y){
    radius = R;
}

Cylinder::Cylinder(std::vector<int> &_x, std::vector<int> &_y,
                   double R, double H): Circle(_x, _y, R){
    height = H;
}
