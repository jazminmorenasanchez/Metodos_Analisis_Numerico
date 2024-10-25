#include <iostream>
#include <cmath>

using namespace std;

// Definimos la función g(x), que es la función transformada.
double g(double x) {
    return exp(-x);  // Función g(x) = e^(-x)
}

// Definimos la derivada de g(x) para verificar la contractividad
double g_prime(double x) {
    return -exp(-x);  // Derivada g'(x) = -e^(-x)
}

// Función para verificar si g(x) es contractiva en el intervalo [a, b]
bool isContractive(double a, double b) {
    return fabs(g_prime((a + b) / 2)) < 1;  // Verifica la derivada en el punto medio
}

// Función para realizar el método de punto fijo
bool fixedPointMethod(double& x0, double tol, int maxIter) {
    int iter = 0;  // Contador de iteraciones
    double x1;

    do {
        x1 = g(x0);  // Calculamos g(x0)
        iter++;      // Incrementamos el contador de iteraciones

        // Verificamos la convergencia.
        if (fabs(x1 - x0) < tol) {
            cout << "\nLa raiz aproximada es: " << x1 << endl;
            cout << "Numero de iteraciones: " << iter << endl;
            return true;  // Salimos de la función si hemos convergido
        }

        // Verificar si la derivada es cercana a cero
        if (fabs(g_prime(x0)) < tol) {
            cout << "Error: g'(x) es cercano a cero en x = " << x0 << ". El método no puede continuar." << endl;
            cout << "Pruebe con otro intervalo y/o otro x0." << endl;
            return false; // Salimos si la derivada es demasiado pequeña
        }

        x0 = x1;  // Actualizamos x0 para la siguiente iteración

    } while (iter < maxIter);

    return false; // Retorna false si no ha convergido
}

int main() {
    // Constantes
    const double TOLERANCE = 1e-3; // Tolerancia epsilon = 10^(-3)
    const int MAX_ITERATIONS = 50;  // Número máximo de iteraciones

    double x0 = 0.5;  // Valor inicial x0 dentro del intervalo definido

    // Definición del intervalo [A, B]
    double A = 0.4;  // Puedes cambiar este valor
    double B = 0.8;  // Puedes cambiar este valor

    cout << "Iniciando el metodo de punto fijo:" << endl;
    cout << "Valor inicial (x0): " << x0 << endl;
    cout << "Tolerancia (epsilon): " << TOLERANCE << endl;
    cout << "Numero maximo de iteraciones: " << MAX_ITERATIONS << endl;
    cout << "Intervalo: [" << A << ", " << B << "]" << endl;

    // Verificamos si la función es contractiva en el intervalo [A, B]
    if (!isContractive(A, B)) {
        cout << "Error: La función no es contractiva en el intervalo [" << A << ", " << B << "]." << endl;
        cout << "Esto puede llevar a que el método no converja." << endl;
        return 1;
    }

    // Llamamos a la función del método de punto fijo
    if (!fixedPointMethod(x0, TOLERANCE, MAX_ITERATIONS)) {
        cout << "El método no converge en " << MAX_ITERATIONS << " iteraciones." << endl;
        cout << "Considere ajustar el valor inicial o verificar la función." << endl;
    }

    return 0;
}
