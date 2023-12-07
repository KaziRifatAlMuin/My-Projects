#include <iostream>
#include <typeinfo>
using namespace std;

class shape{
public:
    virtual double area() = 0;
};

class Rectangle : public shape{
    double a, b;
public:
    Rectangle(){}
    Rectangle(double x, double y)
    {
        a = x;
        b = y;
    }
    double area()
    {
        return a * b;
    }
    void RectDraw()
    {
        cout << "Drawing a Rectangle\n";
    }
};

class Triangle : public shape{
    double a, b;
public:
    Triangle(){}
    Triangle(double x, double y)
    {
        a = x;
        b = y;
    }
    double area()
    {
        return 0.5 * a * b;
    }
};


int main()
{
    shape *s[5];
    for(int i; i < 5; i++){
        if(rand() % 2 == 0){
            s[i] = new Rectangle(10, 20);
        }
        else{
            s[i] = new Triangle(10, 20);
        }
    }
    for(int i = 0; i < 5; i++){
        if(typeid(s[i]) == typeid(Rectangle)){
            cout << "Area : " << s[i]->area() << "\n";
            Rectangle *p = dynamic_cast <Rectangle*> (s[i]);
            p->RectDraw();
        }
        else{
            cout << "Area : " << s[i]->area() << "\n";
        }
    }

    return 0;
}
