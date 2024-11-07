#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

// Define la funcion f(x) para la cual se quiere encontrar la raiz
double f(double x) {
    return exp(-x)-x;  // Cambia esta funcion segun el problema que desees resolver
}

// Define la derivada de f(x), es decir, f'(x)
double f_prime(double x) {
    return -exp(-x)-1;  // Cambia esta derivada segun la funcion f(x) que utilices
}

// Metodo de Newton-Raphson
void metodoNewtonRaphson(double x0, double tol, int max_iter) {
    int iter = 0;
    double x1;

    cout << "Iteracion\t" << "x_n\t\t" << "f(x_n)\t\t" << "Error\n";
    cout << "----------------------------------------------------------\n";
    
    while (iter < max_iter) {
        double fx = f(x0);
        double fx_prime = f_prime(x0);

        if (fabs(fx_prime) < 1e-10) {  // Evita division por cero
            cout << "La derivada es muy pequeña en x = " << x0 << ". Metodo fallido.\n";
            return;
        }

        x1 = x0 - fx / fx_prime;  // Formula de Newton-Raphson
        double error = fabs(x1 - x0);  // Calcula el error |x_(n+1) - x_n|

        // Muestra la iteracion actual, x_n, f(x_n) y el error
        cout << iter + 1 << "\t\t" << x0 << "\t\t" << fx << "\t\t" << error << "\n";

        if (error < tol) {  // Si el error es menor que la tolerancia, se ha convergido
            cout << "\nSolucion encontrada: x = " << x1 << " despues de " << iter + 1 << " iteraciones.\n";
            return;
        }

        x0 = x1;  // Actualiza x0 para la siguiente iteracion
        iter++;
    }

    cout << "\nNo se alcanzo la convergencia despues de " << max_iter << " iteraciones.\n";
}

// Funcion para obtener un numero en punto flotante de entrada del usuario
double obtenerNumero(const string& mensaje) {
    double valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail()) {  // Si hubo un error en la entrada
            cin.clear();   // Limpia el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descarta la entrada incorrecta
            cout << "Entrada invalida. Por favor, introduce un numero.\n";
        } else {
            return valor;
        }
    }
}

// Funcion para obtener un numero entero de entrada del usuario
int obtenerEntero(const string& mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail() || valor <= 0) {  // Verifica que sea un numero entero positivo
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Por favor, introduce un numero entero positivo.\n";
        } else {
            return valor;
        }
    }
}

int main() {
    // Solicita los valores de entrada de forma robusta
    double x0 = obtenerNumero("Introduce el valor inicial x0: ");
    double tol = obtenerNumero("Introduce la tolerancia (por ejemplo, 0.0001): ");
    int max_iter = obtenerEntero("Introduce el numero maximo de iteraciones: ");

    // Llama al metodo de Newton-Raphson
    metodoNewtonRaphson(x0, tol, max_iter);

    return 0;
}
