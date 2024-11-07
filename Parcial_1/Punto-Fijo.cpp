#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;  // Se agrega using namespace std para evitar el uso de std::

double g(double x) {
    // Define aqui la funcion g(x) que quieres utilizar. Ejemplo:
    return exp(-x);  // Esta es solo un ejemplo, cambiala segun tu problema
}

// Metodo del punto fijo
void metodoPuntoFijo(double x0, double tol, int max_iter) {
    int iter = 0;
    double x1;

    cout << "Iteracion\t" << "x_n\t\t" << "g(x_n)\t\t" << "Error\n";
    cout << "----------------------------------------------------------\n";
    
    while (iter < max_iter) {
        x1 = g(x0);  // Calcula g(x_n)
        double error = fabs(x1 - x0);  // Calcula el error |x_(n+1) - x_n|

        // Muestra la iteracion actual, x_n, g(x_n) y el error
        cout << iter + 1 << "\t\t" << x0 << "\t\t" << x1 << "\t\t" << error << "\n";

        if (error < tol) {  // Si el error es menor que la tolerancia, se ha convergido
            cout << "\nSolucion encontrada: x = " << x1 << " despues de " << iter + 1 << " iteraciones.\n";
            return;
        }

        x0 = x1;  // Actualiza x0 para la siguiente iteracion
        iter++;
    }

    cout << "\nNo se alcanzo la convergencia despues de " << max_iter << " iteraciones.\n";
}

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

    // Llama al metodo de punto fijo
    metodoPuntoFijo(x0, tol, max_iter);

    return 0;
}
