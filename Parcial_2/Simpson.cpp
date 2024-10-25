#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Función a integrar
double f(double x) {
    return 8 + 5 * cos(x);
}

// Método de Simpson 1/3
double metodoSimpson(double a, double b, int n) {
    if (n % 2 != 0) {
        cout << "El número de subintervalos (n) debe ser par." << endl;
        return -1; // Error, n debe ser par
    }

    double h = (b - a) / n;
    double sum = f(a) + f(b);

    // Imprimir valor de h
    cout << "Valor de h = " << h << endl << endl;

    // Imprimir la tabla
    cout << left << setw(10) << "i" << setw(10) << "Xi" << setw(10) << "f(Xi)" << endl;
    cout << "-----------------------------------" << endl;
    
    for (int i = 1; i < n; i++) {
        double xi = a + i * h;
        double fxi = f(xi);
        
        cout << left << setw(10) << i << setw(10) << fixed << setprecision(5) << xi << setw(10) << fixed << setprecision(5) << fxi << endl;

        if (i % 2 == 0) {
            sum += 2 * fxi;
        } else {
            sum += 4 * fxi;
        }
    }

    double resultado = (h / 3) * sum;

    // Mostrar el cálculo de I_S
    cout << "\nCalculo de Is:" << endl;
    cout << "Is = ( h / 3 ) * [f(x0) + 4 * sum f(x impares) + 2 * sum f(x pares) + f(xn)]" << endl;
    cout << "Is = (" << h << " / 3) * [" << f(a) << " + 4 * " << (sum / 4 - f(a) / 4 - f(b) / 4) << " + 2 * " << (sum / 2 - f(a) / 2 - f(b) / 2) << " + " << f(b) << "]" << endl;
    cout << "Is = " << resultado << endl;

    return resultado;
}

int main() {
    double a = 0;
    double b = M_PI; // Límite superior pi
    int n = 10; // Debe ser par

    // Calcular la integral usando el método de Simpson
    metodoSimpson(a, b, n);

    return 0;
}

/*
técnica de integración numérica que permite aproximar el valor de una integral definida.
Es particularmente útil cuando no se puede obtener una solución analítica exacta de una integral.
Este método divide el intervalo de integración en partes más pequeñas y utiliza una combinación
de funciones polinómicas para aproximar el área bajo la curva de una función.

Se aplica cuando el intervalo de integración se puede dividir en un número par de subintervalos.
El intervalo [a,b] se divide en n subintervalos de igual longitud h = (b − a) / n
​
Aproxima la función f(x) en cada subintervalo usando una parábola que pasa por tres puntos: los dos extremos y el punto medio.
formula:
Is = (h / 3) * [f(x0) + 4 * sum f(x impares) + 2 * sum f(x pares) + f(xn)]

h es el ancho de los subintervalos.
f(x0​) y f(xn) son los valores de la función en los extremos del intervalo.
Los términos 4 y 2 se utilizan para ponderar los valores de los puntos en los subintervalos impares y pares, respectivamente.

Pasos:
Dividir el intervalo [a,b] en n subintervalos iguales.
Calcular los valores de la función f(x) en los puntos de división.
Aplicar la fórmula de Simpson sumando los valores de la función según la fórmula (ponderados con 4 y 2).
Multiplicar por h/3 para obtener la aproximación de la integral.

Condiciones:
n debe ser par.
Cuanto mayor sea n, mayor será la precisión, ya que se aproximará mejor la curva.
No es adecuado si la función no es suave (es decir, si presenta discontinuidades).
*/