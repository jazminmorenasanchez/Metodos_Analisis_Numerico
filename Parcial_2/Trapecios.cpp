#include <iostream>
#include <iomanip>
#include <cmath>
#include <functional> // Para std::function

using namespace std;

// Función genérica para representar la integral dada
double f(double x) {
    return 8 + 5 * cos(x); // Ejemplo: esta función es modificable
}

// Método de los trapecios genérico
double metodoTrapecios(double a, double b, int n, function<double(double)> func) {
    if (n <= 0 || a == b) {
        cerr << "Error: El número de intervalos debe ser mayor que 0 y los límites de integración deben ser distintos." << endl;
        return 0.0;
    }

    double h = (b - a) / n;
    double sum = 0.0;

    // Imprimir valor de h
    cout << "Valor de h = " << h << endl << endl;

    // Imprimir la tabla
    cout << left << setw(10) << "i" << setw(15) << "Xi" << setw(15) << "f(Xi)" << endl;
    cout << "-----------------------------------" << endl;
    
    for (int i = 0; i <= n; i++) {
        double xi = a + i * h;
        double fxi = func(xi);
        
        cout << left << setw(10) << i << setw(15) << fixed << setprecision(5) << xi << setw(15) << fixed << setprecision(5) << fxi << endl;

        if (i == 0 || i == n) {
            sum += fxi;
        } else {
            sum += 2 * fxi;
        }
    }
    
    double resultado = (h / 2) * sum;

    // Mostrar el cálculo de I_T de forma clara
    cout << "\nCalculo de It:" << endl;
    cout << "It = [(b - a) / (2 * n)] * [f(x0) + 2 * sum(f(xi)) + f(xn)]" << endl;
    cout << "It = [(" << b << " - " << a << ") / (2 * " << n << ")] * [" << func(a) << " + 2 * " 
         << (sum / 2 - func(a) - func(b)) << " + " << func(b) << "]" << endl;
    cout << "It = " << resultado << endl;

    return resultado;
}

int main() {
    double a = 0;
    double b = M_PI; // Límite superior pi
    int n = 10;

    // Calcular la integral usando el método de los trapecios
    metodoTrapecios(a, b, n, f);

    return 0;
}
/*
técnica de integración numérica que se utiliza para aproximar el valor de una integral definida. 
Se basa en aproximar la curva de la función mediante segmentos lineales, formando una serie de trapecios bajo la curva.

Funcionamiento del Método de Trapecios:
El método de trapecios divide el intervalo de integración [a,b] en varios subintervalos. 
Luego, cada par de puntos consecutivos se conecta mediante una línea recta, formando un trapecio. 
El área de cada trapecio se calcula y luego se suman todas esas áreas para obtener una aproximación de la integral.

Fórmula:
La fórmula del método de trapecios para aproximar una integral ∫𝑏𝑎 𝑓(𝑥)𝑑𝑥 es:
It = [(b - a) / (2 * n)] * [f(x0) + 2 * sum(f(xi)) + f(xn)]

Donde:
h = (b−a) / n es el ancho de cada subintervalo.
f(x0) y f(xn) son los valores de la función en los extremos del intervalo.
La suma 2 ∑ 𝑓(𝑥𝑖) incluye los valores de la función en todos los puntos interiores, multiplicados por 2, 
ya que estos puntos aparecen en dos trapecios.

Dividir el intervalo [a,b] en n subintervalos de igual tamaño, donde n puede ser par o impar.
Calcular los valores de la función f(x) en los extremos y en los puntos intermedios del intervalo.
Aplicar la fórmula del método de trapecios, que suma los valores de la función en los puntos inicial y final, y el doble de los valores en los puntos intermedios.
Multiplicar por h/2 para obtener la aproximación de la integral.
*/