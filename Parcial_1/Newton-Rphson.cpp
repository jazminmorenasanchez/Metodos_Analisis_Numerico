#include <iostream>
#include <cmath>
#include <limits>
#include <stdexcept>

using namespace std;

struct NewtonRaphsonParams {
    double x0;          // Valor inicial
    double tol;        // Tolerancia
    int maxIter;       // Máximo número de iteraciones
};

// Definimos la función f(x)
double f(double x) {
    return (1 + x) / pow(M_E, x);
}

// Definimos la derivada f'(x)
double f_prime(double x) {
    return (-x) / pow(M_E, x);
}

// Función para verificar si un valor es infinito o demasiado grande
bool is_value_invalid(double value) {
    return isinf(value) || fabs(value) > numeric_limits<double>::max();
}

// Función principal de Newton-Raphson
double newton_raphson(NewtonRaphsonParams params) {
    double x0 = params.x0;
    double tol = params.tol;
    int maxIter = params.maxIter;
    double x1;
    int iter = 0;

    // Validar entradas
    if (tol <= 0) {
        throw invalid_argument("La tolerancia debe ser mayor a 0.");
    }

    if (maxIter <= 0) {
        throw invalid_argument("El número máximo de iteraciones debe ser mayor a 0.");
    }

    cout << "Iniciando el metodo de Newton-Raphson con los siguientes valores:" << endl;
    cout << "Valor inicial (x0): " << x0 << endl;
    cout << "Tolerancia (epsilon): " << tol << endl;
    cout << "Numero maximo de iteraciones: " << maxIter << endl;

    while (iter < maxIter) {
        double derivada = f_prime(x0);
        int adjustmentAttempts = 0; // Contador para intentos de ajuste

        // Comprobar si la derivada es cercana a cero
        while (fabs(derivada) < numeric_limits<double>::epsilon() && adjustmentAttempts < 10) {
            cout << "La derivada es cercana a cero en x = " << x0 << ". Ajustando x0 ligeramente." << endl;
            x0 += 0.1;  // Ajuste ligero
            derivada = f_prime(x0);
            adjustmentAttempts++;
        }

        // Si aún es cercana a cero después de 10 intentos, salimos del bucle
        if (adjustmentAttempts >= 10) {
            throw runtime_error("No se pudo encontrar una raíz, derivada cercana a cero repetidamente.");
        }

        // Validar que los valores de f(x0) y derivada no sean infinitos o muy grandes
        if (is_value_invalid(f(x0)) || is_value_invalid(derivada)) {
            throw runtime_error("Error: Se encontraron valores extremadamente grandes o infinitos en x = " + to_string(x0));
        }

        x1 = x0 - f(x0) / derivada;  // Aplicamos la fórmula de Newton-Raphson
        iter++;                       // Incrementamos el contador de iteraciones

        // Verificamos la convergencia
        if (fabs(x1 - x0) < tol || fabs((x1 - x0) / x1) < tol) {
            cout << "\n\nLa raiz aproximada es: " << x1 << endl;
            cout << "Numero de iteraciones: " << iter << endl;
            return x1;  // Salimos del programa si hemos convergido
        }

        x0 = x1;  // Actualizamos x0 para la siguiente iteración
    }

    // Si llegamos aquí, significa que no hemos convergido
    throw runtime_error("El método no converge en " + to_string(maxIter) + " iteraciones.");
}

int main() {
    try {
        // Configuración de parámetros
        NewtonRaphsonParams params = {-1, 1e-3, 1000}; // Ejemplo de valores

        // Llamamos a la función de Newton-Raphson
        newton_raphson(params);
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
