#include <iostream>
#include <cmath>      // Para usar la función exp()
#include <functional> // Para usar std::function
using namespace std;

// Definimos la función f(x, y) = dy/dx
double f(double x, double y) {
    return exp(0.8 * x) - 0.5 * y;
}

// Implementación del método de Runge-Kutta de segundo orden mostrando k1 y k2 hasta x = 4
void metodoRK2(std::function<double(double, double)> func, double x0, double y0, double h, double xFinal) {
    double x = x0, y = y0;

    // Imprimimos el encabezado
    cout << "xi\t\tyi (RK2)\t\tk1\t\t\tk2\n";

    // Calculamos los valores de y en cada paso, incluyendo xFinal
    while (x <= xFinal) {
        // Cálculo de k1 en el punto actual (xi, yi)
        double k1 = func(x, y);

        // Cálculo de k2 en el punto (xi + h, yi + h * k1)
        double k2 = func(x + h, y + h * k1);

        // Imprimimos los valores actuales de x, y, k1 y k2
        cout << x << "\t" << y << "\t\t" << k1 << "\t\t" << k2 << endl;

        // Actualizamos y usando el promedio de k1 y k2
        y = y + (h / 2) * (k1 + k2);

        // Avanzamos x en un paso h
        x = x + h;
        
        // Evitamos errores de punto flotante que impidan alcanzar exactamente xFinal
        if (x > xFinal && x < xFinal + h) x = xFinal;
    }
}

int main() {
    double x0 = 0;     // Valor inicial de x
    double y0 = 0.3333;     // Condición inicial y(0) = 2
    double h = 0.01;    // Tamaño del paso
    double xFinal = 2; // Límite superior para x

    metodoRK2(f, x0, y0, h, xFinal);

    return 0;
}
