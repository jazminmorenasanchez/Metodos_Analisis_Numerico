#include <iostream>
#include <vector> // Para usar vectores dinámicos
using namespace std;

// Derivada progresiva en x0 con 3 puntos
double derivada_progresiva(double y0, double y1, double y2, double h) {
    return (-3 * y0 + 4 * y1 - y2) / (2 * h);
}

// Derivada centrada en puntos intermedios con 3 puntos
double derivada_centrada(double y_prev, double y_next, double h) {
    return (y_next - y_prev) / (2 * h);
}

// Derivada regresiva en el último punto con 3 puntos
double derivada_regresiva(double y0, double y1, double y2, double h) {
    return (3 * y0 - 4 * y1 + y2) / (2 * h);
}

int main() {
    // Tabla de valores de x y y (dados por el usuario)
    vector<double> x = {0, -0.1, -0.2, -0.3, -0.4, -0.5, -0.6, -0.7, -0.8, -0.9};  // Valores de x
    vector<double> y = {0, -0.9, -0.16, -0.22, -0.26, -0.3, -0.32, -0.34, -0.35, -0.36};  // Valores correspondientes de y

    int n = x.size();  // Número de puntos
    double h = x[1] - x[0];  // Suponemos que h es constante (diferencia entre puntos de x)
    
    // Imprimimos la cabecera
    cout << "Xi\tf(Xi)\t\tf'(Xi)\t\tMetodo" << endl;
    
    // Calculamos las derivadas según el método correspondiente
    for (int i = 0; i < n; i++) {
        double derivada;
        if (i == 0) {
            // Ecuación progresiva para el primer punto
            derivada = derivada_progresiva(y[i], y[i+1], y[i+2], h);
            cout << x[i] << "\t" << y[i] << "\t\t" << derivada << "\t\tEcuacion progresiva" << endl;
        } else if (i == n - 1) {
            // Ecuación regresiva para el último punto
            derivada = derivada_regresiva(y[i], y[i-1], y[i-2], h);
            cout << x[i] << "\t" << y[i] << "\t\t" << derivada << "\t\tEcuacion regresiva" << endl;
        } else {
            // Ecuación centrada para los puntos intermedios
            derivada = derivada_centrada(y[i-1], y[i+1], h);
            cout << x[i] << "\t" << y[i] << "\t\t" << derivada << "\t\tEcuacion centrada" << endl;
        }
    }

    return 0;
}
