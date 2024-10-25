#include <iostream>
#include <iomanip>  // Para controlar la precisión de los resultados
#include <cmath>
#include <stdexcept>  // Para manejo de excepciones

using namespace std;

// Función para imprimir la matriz aumentada
void printMatrix(double** a, int n) {
    cout << "Matriz Aumentada:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << setw(10) << fixed << setprecision(4) << a[i][j] << " ";
        }
        cout << endl;
    }
}

// Definimos la función para realizar la eliminación gaussiana
void gaussianElimination(double** a, double* x, int n, double error) {
    // Fase de eliminación
    for (int i = 0; i < n - 1; i++) {
        // Verificamos que el pivote no sea cero usando el error personalizado
        if (fabs(a[i][i]) < error) {
            throw runtime_error("Error: Pivote es cero o muy cercano a cero. El sistema podría ser inconsistente o mal condicionado.");
        }

        for (int k = i + 1; k < n; k++) {
            double factor = a[k][i] / a[i][i];  // Cálculo del factor para eliminar la variable
            for (int j = i; j <= n; j++) {
                a[k][j] -= factor * a[i][j];
            }
        }
        
        // Opcional: Imprimir la matriz después de cada paso de eliminación
        printMatrix(a, n);
    }

    // Fase de sustitución hacia atrás
    for (int i = n - 1; i >= 0; i--) {
        x[i] = a[i][n];
        for (int j = i + 1; j < n; j++) {
            x[i] -= a[i][j] * x[j];
        }

        if (fabs(a[i][i]) < error) {
            throw runtime_error("Error: División por un pivote cercano a cero. El sistema podría ser indeterminado.");
        }

        x[i] /= a[i][i];
    }
}

// Función principal
int main() {
    int n = 3;  // Número de ecuaciones
    // Matriz aumentada del sistema
    double a[3][4] = {
        {2, -9, 7.10, 6},
        {9.01, 3.20, 2.05, 4.20},
        {18.04, 6.10, 4.10, 8.10}
    };

    double error = pow(10,-3); // Solicitar el valor de error al usuario

    // Convertimos la matriz estática a punteros dinámicos para mayor flexibilidad
    double** augmentedMatrix = new double*[n];
    for (int i = 0; i < n; i++) {
        augmentedMatrix[i] = new double[n + 1];
        for (int j = 0; j <= n; j++) {
            augmentedMatrix[i][j] = a[i][j];
        }
    }

    double* x = new double[n];  // Arreglo para almacenar las soluciones
    

    cout << "Resolviendo el sistema de ecuaciones usando Eliminación Gaussiana:" << endl;

    try {
        // Llamamos a la función de eliminación gaussiana
        gaussianElimination(augmentedMatrix, x, n, error);

        // Mostramos los resultados con más precisión
        cout << fixed << setprecision(6);
        cout << "Las soluciones son:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "x" << i + 1 << " = " << x[i] << endl;
        }
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    // Liberamos memoria dinámica
    for (int i = 0; i < n; i++) {
        delete[] augmentedMatrix[i];
    }
    delete[] augmentedMatrix;
    delete[] x;

    return 0;
}
