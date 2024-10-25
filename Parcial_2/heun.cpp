#include <iostream>
#include <cmath>      // Para usar la función exp()
#include <functional> // Para usar std::function
using namespace std;

// Definimos la función f(x, y) = dy/dx
double f(double x, double y) {
    return exp(0.8 * x) - 0.5 * y;
}

// Implementación del método de Heun con una columna adicional para Euler
void metodoHeunConEuler(std::function<double(double, double)> func, double x0, double y0, double h, double xFinal) {
    double x = x0, y = y0;
    int i = 0; // Contador de pasos

    // Imprimimos el encabezado
    cout << "i\txi\ty0i+1 (Euler)\tyi+1 (Heun)\n";
    cout << i << "\t" << x << "\t"<< y <<"\t\t" << y << endl;

    // Calculamos los valores de y en cada paso
    while (x < xFinal) {
        // Paso de Euler: Predicción
        double yEuler = y + h * func(x, y); // Valor de Euler en el siguiente punto

        // Corrección con Heun usando la pendiente promedio
        double yHeun = y + (h / 2) * (func(x, y) + func(x + h, yEuler));

        // Actualizamos x y y para el siguiente paso
        x = x + h;
        y = yHeun;
        
        // Mostramos la fila con ambos valores de Euler y Heun
        i++;
        cout << i << "\t" << x << "\t" << yEuler << "\t\t" << yHeun << endl;
    }
}

int main() {
    double x0 = 0;     // Valor inicial de x
    double y0 = 2;     // Condición inicial y(0) = 2
    double h = 0.1;    // Tamaño del paso
    double xFinal = 4; // Límite superior para x

    metodoHeunConEuler(f, x0, y0, h, xFinal);

    return 0;
}

/*
dx/dy = f(x,y), y(x0) = y0 
queremos calcular una aproximación del valor de 𝑦 en un intervalo [𝑥0,𝑥final] avanzando en pasos de tamaño ℎ.

Predictor (Euler): Primero, calculamos un valor "predicho" de 𝑦 en el siguiente paso 
𝑥𝑖+1 utilizando el método de Euler: 𝑦predicho = 𝑦𝑖 + ℎ * 𝑓(𝑥𝑖,𝑦𝑖)

Corrector: Calculamos el valor de la pendiente en el nuevo punto (𝑥𝑖+1,𝑦predicho) 
y usamos esta pendiente junto con la pendiente original para obtener un promedio de las pendientes. 
Este promedio se usa para calcular el valor corregido de 𝑦 en 𝑥𝑖+1:

𝑦𝑖+1 = 𝑦𝑖 + ℎ/2 * (𝑓(𝑥𝑖,𝑦𝑖) + 𝑓(𝑥𝑖+1, 𝑦predicho))
*/