#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

//14
double line(double x){ 
    if (x >= -5 && x <= -3){
        return 1;
    }
    if (x >= -1 && x <= 2){
        return -2;
    }
    if (x > 2){ // k = (0+2)/(4-2) = 1; b = -4 
        return x - 4.0;
    }
}

double circle(double x){ //Окружность - x^2 + y^2 = R^2; R = 2; центр в точке (-1; 0) => (x + 1)^2 + y^2 = 2^2
    return -sqrt(4 - (x + 1.0)*(x + 1.0));
}


int main(){
    double dx = 0.5;
    double x_end = 5.0;
    double x_begin = -5.0;

    cout << fixed << setprecision(1);
    cout << left << setw(10) << "x" << setw(10) << "y" << endl; //Заголовок таблицы

    for (double x = x_begin; x <= x_end; x += dx){
        double y;
        if (x <= -3) y = line(x);
        if (x > -3 && x <= -1) y = circle(x);
        if (x > -1 && x <= 2) y = line(x);
        if (x > 2) y = line(x);
         
        cout << left << setw(10) << x << setw(10) << y << endl;
    }
    
    return 0 ;
}