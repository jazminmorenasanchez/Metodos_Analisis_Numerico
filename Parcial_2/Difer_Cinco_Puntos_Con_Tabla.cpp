#include <iostream>
#include <vector>
using namespace std;

// Derivada progresiva en x0 con 5 puntos
double derivada_progresiva(double y0, double y1, double y2, double y3, double y4, double h) {
    return (-25 * y0 + 48 * y1 - 36 * y2 + 16 * y3 - 3 * y4) / (12 * h);
}

// Derivada centrada en puntos intermedios con 5 puntos
double derivada_centrada(double y_prev2, double y_prev1, double y_next1, double y_next2, double h) {
    return (-y_prev2 + 8 * y_prev1 - 8 * y_next1 + y_next2) / (12 * h);
}

// Derivada regresiva en el último punto con 5 puntos
double derivada_regresiva(double y0, double y1, double y2, double y3, double y4, double h) {
    return (25 * y0 - 48 * y1 + 36 * y2 - 16 * y3 + 3 * y4) / (12 * h);
}

int main() {
    // Tabla de valores de x y y (dados por el usuario)
    vector<double> x = {0, 0.5, 1, 1.5, 2};  // Valores de x
    vector<double> y = {0, 0.4207, 0.4546, 0.0706, -0.3784};  // Valores correspondientes de y

    int n = x.size();  // Número de puntos
    double h = x[1] - x[0];  // Suponemos que h es constante (diferencia entre puntos de x)
    
    // Imprimimos la cabecera
    cout << "Xi\tf(Xi)\t\tf'(Xi)\t\tMetodo" << endl;
    
    // Calculamos las derivadas según el método correspondiente
    for (int i = 0; i < n; i++) {
        double derivada;
        if (i == 0) {
            // Ecuación progresiva para el primer punto
            derivada = derivada_progresiva(y[i], y[i+1], y[i+2], y[i+3], y[i+4], h);
            cout << x[i] << "\t" << y[i] << "\t\t" << derivada << "\t\tEcuacion progresiva" << endl;
        } else if (i == 1 || i == n-2) {
            // Para los puntos en el segundo o penúltimo lugar, usamos la fórmula centrada
            derivada = derivada_centrada(y[i-2], y[i-1], y[i+1], y[i+2], h);
            cout << x[i] << "\t" << y[i] << "\t\t" << derivada << "\t\tEcuacion centrada" << endl;
        } else if (i == n - 1) {
            // Ecuación regresiva para el último punto
            derivada = derivada_regresiva(y[i], y[i-1], y[i-2], y[i-3], y[i-4], h);
            cout << x[i] << "\t" << y[i] << "\t\t" << derivada << "\t\tEcuacion regresiva" << endl;
        } else {
            // Usamos ecuación centrada para los puntos intermedios
            derivada = derivada_centrada(y[i-2], y[i-1], y[i+1], y[i+2], h);
            cout << x[i] << "\t" << y[i] << "\t\t" << derivada << "\t\tEcuacion centrada" << endl;
        }
    }

    return 0;
}
