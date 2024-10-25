#include <iostream>
#include <cmath>      // Para usar la función exp()
#include <functional> // Para usar std::function
using namespace std;

// Definimos la función f(x, y) = dy/dx
double f(double x, double y) {
    return exp(0.8 * x) - 0.5 * y;
}

// Implementación del método de Runge-Kutta de cuarto orden mostrando k1, k2, k3 y k4 hasta x = 4
void metodoRK4(std::function<double(double, double)> func, double x0, double y0, double h, double xFinal) {
    double x = x0, y = y0;

    // Imprimimos el encabezado
    cout << "xi\tyi (RK4)\tk1\t\tk2\t\tk3\t\tk4\n";

    // Calculamos los valores de y en cada paso, incluyendo xFinal
    while (x <= xFinal) {
        // Cálculo de k1 en el punto actual (xi, yi)
        double k1 = func(x, y);

        // Cálculo de k2 en el punto (xi + h/2, yi + (h/2) * k1)
        double k2 = func(x + h / 2, y + (h / 2) * k1);

        // Cálculo de k3 en el punto (xi + h/2, yi + (h/2) * k2)
        double k3 = func(x + h / 2, y + (h / 2) * k2);

        // Cálculo de k4 en el punto (xi + h, yi + h * k3)
        double k4 = func(x + h, y + h * k3);

        // Imprimimos los valores actuales de x, y, k1, k2, k3 y k4
        cout << x << "\t" << y << "\t\t" << k1 << "\t\t" << k2 << "\t\t" << k3 << "\t\t" << k4 << endl;

        // Actualizamos y usando el promedio ponderado de k1, k2, k3 y k4
        y = y + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);

        // Avanzamos x en un paso h
        x = x + h;

        // Ajuste para incluir el último valor exacto xFinal
        if (x > xFinal && x < xFinal + h) x = xFinal;
    }
}

int main() {
    double x0 = 0;     // Valor inicial de x
    double y0 = 2;     // Condición inicial y(0) = 2
    double h = 0.1;    // Tamaño del paso
    double xFinal = 4; // Límite superior para x

    metodoRK4(f, x0, y0, h, xFinal);

    return 0;
}
