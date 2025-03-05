#pragma once
#include <vector>

class Shape{
public:
    void shift(int m, int n);
    virtual void scaleX(int a);
    virtual void scaleY(int d);
    virtual void scale(int s);
    Shape(std::vector<int>& _x, std::vector<int>& _y);
    Shape() = default;
    virtual ~Shape() = default;
protected:
    const static int size= 2;
    std::vector<int> x;
    std::vector<int> y;
};

class Square: public Shape{
public:
    virtual void transformShift(int m, int n, int k);
    Square(std::vector<int>& _x, std::vector<int>& _y);
    ~Square()= default;
private:
    const static int size= 4;
};

class Cube: public Square{
public:
    void shift(int m, int n, int k);
    void scale(int s) override;
    virtual void scaleZ(int e);
    Cube(std::vector<int>& _x, std::vector<int>& _y, std::vector<int>& _z);
    ~Cube()= default;
private:
    const static int size= 8;
    std::vector<int> z;
};

class Circle: public Shape{
public:
    Circle(std::vector<int>& _x, std::vector<int>& _y, double R);
    ~Circle()= default;
private:
    const static int size= 1;
    double radius;
};

class Cylinder: public Circle{
public:
    Cylinder(std::vector<int>& _x, std::vector<int>& _y, double R, double H);
    ~Cylinder()= default;
private:
    double height;
};
