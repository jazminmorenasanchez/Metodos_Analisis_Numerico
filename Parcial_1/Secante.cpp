#include <iostream>
#include <cmath>
#include <stdexcept>  // Para manejo de excepciones

using namespace std;

// Definimos la función f(x)
double f(double x) {
    return pow(M_E, -x)-x;
}

// Método de la secante
double secante(double x0, double x1, double tol, int maxIter) {
    int iter = 0;
    double x2;

    // Validaciones iniciales
    if (tol <= 0) {
        throw invalid_argument("Error: la tolerancia debe ser un valor positivo.");
    }

    if (maxIter <= 0) {
        throw invalid_argument("Error: el numero maximo de iteraciones debe ser mayor que 0.");
    }

    if (fabs(f(x0) - f(x1)) < 1e-12) {
        throw invalid_argument("Error: la diferencia entre f(x0) y f(x1) es demasiado pequeña. Esto puede provocar inestabilidad numerica.");
    }

    cout << "Iteracion\t x0\t\t x1\t\t f(x1)\t\t x2\t\t Error" << endl;
    
    // Método de la secante
    while (iter < maxIter) {
        // Calculamos el siguiente valor de x2 usando la fórmula de la secante
        x2 = x1 - f(x1) * (x1 - x0) / (f(x1) - f(x0));
        iter++;  // Incrementamos el contador de iteraciones
        
        // Mostramos el progreso de la iteración
        cout << iter << "\t\t" << x0 << "\t\t" << x1 << "\t\t" << f(x1) << "\t\t" << x2 << "\t\t" << fabs(x2 - x1) << endl;

        // Verificamos la convergencia basada en la diferencia de puntos y el valor de f(x2)
        if (fabs(x2 - x1) < tol || fabs(f(x2)) < tol) {
            cout << "\nLa raiz aproximada es: " << x2 << endl;
            cout << "Numero de iteraciones: " << iter << endl;
            return x2;
        }

        // Actualizamos x0 y x1 para la siguiente iteración
        x0 = x1;
        x1 = x2;

        // Chequeo adicional para evitar que los valores de f(x0) y f(x1) sean muy cercanos y causen errores de división
        if (fabs(f(x0) - f(x1)) < 1e-12) {
            throw runtime_error("Error: los valores de f(x0) y f(x1) se están acercando demasiado, lo que puede provocar inestabilidad numérica.");
        }
    }

    // Si no se logró convergencia dentro del número máximo de iteraciones, lanzamos excepción
    throw runtime_error("El metodo no converge en el numero maximo de iteraciones.");
}

int main() {
    double x0 = -1;       // Primer valor inicial x0
    double x1 = 2;       // Segundo valor inicial x1
    double tol = pow(10,-3);     // Tolerancia epsilon = 10^(-3)
    int maxIter = 50;      // Número máximo de iteraciones

    // Mostramos los valores iniciales
    cout << "Iniciando el metodo de la secante con los siguientes valores:" << endl;
    cout << "Primer valor inicial (x0): " << x0 << endl;
    cout << "Segundo valor inicial (x1): " << x1 << endl;
    cout << "Tolerancia (epsilon): " << tol << endl;
    cout << "Numero maximo de iteraciones: " << maxIter << endl;

    try {
        // Llamamos al método de la secante
        secante(x0, x1, tol, maxIter);
    } catch (const exception& e) {
        // Capturamos cualquier excepción y mostramos el mensaje de error
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
