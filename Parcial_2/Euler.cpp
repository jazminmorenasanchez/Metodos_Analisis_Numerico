#include <iostream>
#include <cmath>  // Para usar la función exp()
#include <functional>  // Para usar std::function
using namespace std;

// Definimos la función f(x, y) = dy/dx como un puntero a función
double f(double x, double y) {
    return exp(0.8 * x) - 0.5 * y;  // Ecuación a resolver
}

// Implementación del método de Euler
void metodoEuler(std::function<double(double, double)> func, double x0, double y0, double h, double xFinal) {
    double x = x0, y = y0;
    int i = 0; // Contador de pasos

    // Imprimimos el encabezado
    cout << "i\txi\tyi+1\n";
    cout << i << "\t" << x << "\t" << y << endl;

    // Validaciones
    if (h <= 0) {
        cout << "Error: El tamaño del paso h debe ser positivo." << endl;
        return;
    }

    // Calculamos los valores de y en cada paso
    while (x < xFinal) {
        y = y + h * func(x, y);  // y_{i+1} = y_i + h * f(x_i, y_i)
        x = x + h;  // Avanzamos en x
        i++;  // Incrementamos el contador
        cout << i << "\t" << x << "\t" << y << endl;
    }
}

int main() {
    double x0 = 0;     // Valor inicial de x
    double y0 = 2;     // Condición inicial y(0) = 2
    double h = 0.1;    // Tamaño del paso
    double xFinal = 4; // Límite superior para x

    metodoEuler(f, x0, y0, h, xFinal);

    return 0;
}

/*
método numérico para aproximar la solución de ecuaciones diferenciales ordinarias (EDO) de primer orden. 
Este método es especialmente útil cuando no es posible encontrar una solución analítica exacta para la EDO.

Concepto Básico
Supongamos que tenemos una ecuación diferencial ordinaria de primer orden en la forma:
dx/dy = f(x,y), y(x0)=y0 
donde y(x0)=y0es la condición inicial.

El objetivo del método de Euler es aproximar el valor de la función y(x) en puntos posteriores a x0​, avanzando paso a paso. 
Para esto, necesitamos definir un tamaño de paso h que representa el cambio en x en cada paso.

Fórmula del Método de Euler
𝑦𝑛+1=𝑦𝑛+ℎ*𝑓(𝑥𝑛,𝑦𝑛) 

donde:
𝑦𝑛 es el valor actual de 𝑦 en el punto 𝑥𝑛
h es el tamaño del paso (es decir, la distancia entre 𝑥𝑛 y 𝑥𝑛+1),
𝑓(𝑥𝑛,𝑦𝑛) es la pendiente de la solución en (𝑥𝑛, 𝑦𝑛) calculada usando la ecuación diferencial.

El método de Euler estima la solución al avanzar a lo largo de la curva de la solución
mediante una aproximación lineal en cada paso. Cada nuevo punto se calcula basándose en la pendiente 
en el punto actual y se asume que esta pendiente es constante en el intervalo pequeño h.

*/