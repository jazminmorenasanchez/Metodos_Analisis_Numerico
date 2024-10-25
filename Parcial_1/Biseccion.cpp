#include <iostream>
#include <cmath>
#include <stdexcept>  // Para manejar excepciones

using namespace std;

double biseccion(double a, double b, double E);
double f(double x);

int main() {
    double a = -1;
    double b = 2;
    double E = pow(10,-3);


    try {
        double raiz = biseccion(a, b, E);
        cout << "La raiz en el intervalo [" << a << "; " << b << "] es: " << raiz << endl;
    } catch (const std::invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}

double biseccion(double a, double b, double E) {
    if (a >= b) {
        throw invalid_argument("El valor de 'a' debe ser menor que 'b'.");
    }

    double fa = f(a);
    double fb = f(b);

    if (fa * fb > 0) {
        throw invalid_argument("La funcion no cambia de signo en el intervalo dado.");
    }

    double c = 0;
    double error = (b - a) / 2;

    while (error > E) {
        c = (a + b) / 2;
        double fc = f(c);

        // Comparación de valores cercanos a cero
        if (fabs(fc) < E) {
            return c;  // Encontramos una raíz suficientemente cercana a cero
        }

        if (fa * fc < 0) {
            b = c;
            fb = fc;
        } else {
            a = c;
            fa = fc;
        }

        error = (b - a) / 2;  // Actualiza el error
    }

    return c;
}

double f(double x) {
    return pow(M_E, -x)-x;  // Ejemplo de función, puedes cambiarla
}
/*
e es M_E
logaritmos: log10(numero) logaritmo en base 10, log() logaritmo en base e, es decir log natural, log(numero)/log(base) para cualquier caso
double f(double x){
    return -0.874*pow(x,2) + 1.75*x + 2.627;
}

double f(double x){
    return log(x)-5;
}

double f(double x){
    return pow(M_E,-x) - x;
}
// Función con seno
double f(double x) {
    return sin(x) + x;
}

// Función con coseno
double f(double x) {
    return cos(x) - 2 * x;
}

// Función con tangente
double f(double x) {
    return tan(x) + x / 2;
}

// Función con arcoseno
double f(double x) {
    return asin(x) + pow(x, 2);
}

// Función con arcocoseno
double f(double x) {
    return acos(x) + x * 2;
}

// Función con arcotangente
double f(double x) {
    return atan(x) - 3 * x;
}

// Función con raíz cuadrada
double f(double x) {
    return sqrt(x) - log(x);
}

// Función con exponencial
double f(double x) {
    return exp(x) - pow(x, 3);
}

// Función con valor absoluto
double f(double x) {
    return fabs(x) - 2 * pow(x, 2);
}

// Función con logaritmo natural
double f(double x) {
    return log(x) + x * x;
}

// Función con logaritmo base 10
double f(double x) {
    return log10(x) - x + 1;
}

// Función con hiperbólicas (sinh, cosh, tanh)
double f(double x) {
    return sinh(x) - cosh(x) + tanh(x);
}

//Funcion Raiz cubica
double f(double x) {
    return cbrt(x);
}
*/