#include <iostream>
#include <cmath> // Para funciones matemáticas como exp y cos
using namespace std;

// Función f(x) = e^x * cos(x)
double f(double x) {
    return exp(x)*cos(x);
}

// Derivada progresiva en x0
double derivada_progresiva(double x0, double h) {
    return (-3 * f(x0) + 4 * f(x0 + h) - f(x0 + 2 * h)) / (2 * h);
}

// Derivada centrada en puntos intermedios
double derivada_centrada(double x0, double h) {
    return (f(x0 + h) - f(x0 - h)) / (2 * h);
}

// Derivada regresiva en el último punto
double derivada_regresiva(double x0, double h) {
    return (3 * f(x0) - 4 * f(x0 - h) + f(x0 - 2 * h)) / (2 * h);
}

int main() {
    // Valores iniciales
    double h = 0.1;
    double x[] = { 0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7}; // Puntos donde queremos calcular la derivada
    int n = sizeof(x) / sizeof(x[0]); // Número de puntos
    
    cout << "Xi\tf(Xi)\t\tf'(Xi)\t\tMetodo" << endl;
    for (int i = 0; i < n; i++) {
        double derivada;
        if (i == 0) {
            // Usar ecuación progresiva en el primer punto
            derivada = derivada_progresiva(x[i], h);
            cout << x[i] << "\t" << f(x[i]) << "\t\t" << derivada << "\t\tEcuacion progresiva" << endl;
        } else if (i == n - 1) {
            // Usar ecuación regresiva en el último punto
            derivada = derivada_regresiva(x[i], h);
            cout << x[i] << "\t" << f(x[i]) << "\t\t" << derivada << "\t\tEcuacion regresiva" << endl;
        } else {
            // Usar ecuación centrada para los puntos intermedios
            derivada = derivada_centrada(x[i], h);
            cout << x[i] << "\t" << f(x[i]) << "\t\t" << derivada << "\t\tEcuacion centrada" << endl;
        }
    }
    
    return 0;
}
