#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

// Define la funcion f(x) para la cual se quiere encontrar la raiz
double f(double x) {
    // Ejemplo de funcion: f(x) = x^2 - 4
    return exp(-x)-x;  // Cambia esta funcion segun el problema que desees resolver
}

// Metodo de la secante
void metodoSecante(double x0, double x1, double tol, int max_iter) {
    int iter = 0;
    double x2, error;

    cout << "Iteracion\t" << "x_n\t\t" << "f(x_n)\t\t" << "Error\n";
    cout << "----------------------------------------------------------\n";
    
    while (iter < max_iter) {
        double fx0 = f(x0);
        double fx1 = f(x1);

        if (fabs(fx1 - fx0) < 1e-10) {  // Evita division por cero en la formula de la secante
            cout << "La diferencia f(x_n) - f(x_(n-1)) es demasiado pequena. Metodo fallido.\n";
            return;
        }

        // Formula de la secante para obtener x_(n+1)
        x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);
        error = fabs(x2 - x1);  // Calcula el error |x_(n+1) - x_n|

        // Muestra la iteracion actual, x_n, f(x_n) y el error
        cout << iter + 1 << "\t\t" << x1 << "\t\t" << fx1 << "\t\t" << error << "\n";

        if (error < tol) {  // Si el error es menor que la tolerancia, se ha convergido
            cout << "\nSolucion encontrada: x = " << x2 << " despues de " << iter + 1 << " iteraciones.\n";
            return;
        }

        // Actualiza x0 y x1 para la siguiente iteracion
        x0 = x1;
        x1 = x2;
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
    double x1 = obtenerNumero("Introduce el valor inicial x1: ");
    double tol = obtenerNumero("Introduce la tolerancia (por ejemplo, 0.0001): ");
    int max_iter = obtenerEntero("Introduce el numero maximo de iteraciones: ");

    // Llama al metodo de la secante
    metodoSecante(x0, x1, tol, max_iter);

    return 0;
}
