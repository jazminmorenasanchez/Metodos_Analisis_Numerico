#include <iostream>
#include <cmath> // Para funciones matemáticas como exp y cos
using namespace std;

// Función f(x) = e^x * cos(x)
double f(double x) {
    return exp(x) * cos(x);
}

// Derivada progresiva en x0 con 5 puntos
double derivada_progresiva(double x0, double h) {
    return (-25 * f(x0) + 48 * f(x0 + h) - 36 * f(x0 + 2 * h) + 16 * f(x0 + 3 * h) - 3 * f(x0 + 4 * h)) / (12 * h);
}

// Derivada centrada en puntos intermedios con 5 puntos
double derivada_centrada(double x0, double h) {
    return (f(x0 - 2 * h) - 8 * f(x0 - h) + 8 * f(x0 + h) - f(x0 + 2 * h)) / (12 * h);
}

// Derivada regresiva en el último punto con 5 puntos
double derivada_regresiva(double x0, double h) {
    return (3 * f(x0 - 4 * h) - 16 * f(x0 - 3 * h) + 36 * f(x0 - 2 * h) - 48 * f(x0 - h) + 25 * f(x0)) / (12 * h);
}

void mostrarFormulas(double h, double a, double b) {
    cout << "Formulas:\n";
    cout << "Ecuacion progresiva --> f'(x) = [-25 * f(x0) + 48 * f(x0 + h) - 36 * f(x0 + 2h) + 16 * f(x0 + 3h) - 3 * f(x0 + 4h)] / (12 * h)\n";
    cout << "Ecuacion centrada --> f'(x) = [f(x0 - 2h) - 8 * f(x0 - h) + 8 * f(x0 + h) - f(x0 + 2h)] / (12 * h)\n";
    cout << "Ecuacion regresiva --> f'(x) = [3 * f(x0 - 4h) - 16 * f(x0 - 3h) + 36 * f(x0 - 2h) - 48 * f(x0 - h) + 25 * f(x0)] / (12 * h)\n";
    cout << endl;
    cout << "Intervalo: [" << a <<" ; "<< b <<"]"<<endl;
    cout << "Valor de h = " << h << endl;
}

int main() {
    // Pedimos los extremos del intervalo y el valor de h
    double a, b, h;
    a = 0;
    b = 0.7;
    h = 0.1;

    // Calculamos la cantidad de puntos en el intervalo
    int n = (b - a) / h + 1;
    double x[n];  // Array para almacenar los puntos de x

    // Generamos los puntos de x
    for (int i = 0; i < n; i++) {
        x[i] = a + i * h;
    }

    mostrarFormulas(h,a,b);

    // Imprimimos los resultados
    cout << "\nXi\tf(Xi)\t\tf'(Xi)\t\tMetodo" << endl;
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
