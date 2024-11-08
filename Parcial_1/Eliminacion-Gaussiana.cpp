#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <stdexcept>

using namespace std;

typedef vector<vector<double>> Matrix;
typedef vector<double> Vector;

// Función para imprimir la matriz aumentada
void printAugmentedMatrix(const Matrix& A, const Vector& B) {
    int n = A.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(10) << setprecision(4) << fixed << A[i][j] << " ";
        }
        cout << " | " << setw(10) << setprecision(4) << fixed << B[i] << endl;
    }
    cout << endl;
}

// Función para realizar la eliminación Gaussiana
Vector gaussianElimination(Matrix A, Vector B) {
    int n = A.size();

    cout << "Metodo de eliminacion Gaussiana: " << endl;

    // Fase de eliminación
    for (int i = 0; i < n; i++) {
        // Pivoteo: encontrar el elemento mayor en la columna actual para evitar divisiones por cero
        double maxElem = abs(A[i][i]);
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (abs(A[k][i]) > maxElem) {
                maxElem = abs(A[k][i]);
                maxRow = k;
            }
        }

        // Intercambiar filas si es necesario
        if (maxRow != i) {
            swap(A[i], A[maxRow]);
            swap(B[i], B[maxRow]);
            cout << "Intercambiando fila " << i + 1 << " con fila " << maxRow + 1 << " para maximizar el pivote." << endl;
            printAugmentedMatrix(A, B);
        }

        // Verificar si el pivote es cero (matriz singular o sistema sin solucion unica)
        if (fabs(A[i][i]) < 1e-10) {
            throw runtime_error("Error: la matriz es singular o el sistema no tiene solucion unica.");
        }

        // Normalizar la fila para que el pivote sea 1
        double pivot = A[i][i];
        cout << "Haciendo 1 el elemento de la fila " << i + 1 << " dividiendo por el pivote " << pivot << "." << endl;
        for (int j = i; j < n; j++) {
            A[i][j] /= pivot;
        }
        B[i] /= pivot;
        printAugmentedMatrix(A, B);

        // Hacer ceros en las filas debajo del pivote
        for (int k = i + 1; k < n; k++) {
            double factor = A[k][i];
            cout << "Haciendo cero el elemento A[" << k + 1 << "][" << i + 1 << "] utilizando el factor " << factor << "." << endl;
            for (int j = i; j < n; j++) {
                A[k][j] -= factor * A[i][j];
            }
            B[k] -= factor * B[i];
            printAugmentedMatrix(A, B);
        }
    }

    // Fase de sustitución hacia atrás
    Vector X(n);
    cout << "Iniciando la sustitucion hacia atras para resolver el sistema..." << endl;
    for (int i = n - 1; i >= 0; i--) {
        X[i] = B[i];
        for (int j = i + 1; j < n; j++) {
            X[i] -= A[i][j] * X[j];
        }
        cout << "X[" << i + 1 << "] = " << setprecision(4) << fixed << X[i] << endl;
    }

    return X;
}

int main() {
    try {
        // Definir una matriz de prueba y vector de resultados B
        int n = 3;  // Tamaño de la matriz (puedes cambiar esto)
        Matrix A = { 
            {2, -9, 7.1},
            {9.01, 3.2, 2.05},
            {18.04, 6.01, 4.1}
        };
        Vector B = {6, 4.2, 8.1};

        cout << "Matriz aumentada inicial:" << endl;
        printAugmentedMatrix(A, B);

        // Resolver el sistema utilizando eliminación Gaussiana
        Vector X = gaussianElimination(A, B);

        // Imprimir las soluciones
        cout << "\nSoluciones del sistema:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "x" << i + 1 << " = " << setprecision(4) << fixed << X[i] << endl;
        }
    } catch (const runtime_error& e) {
        cerr << "Excepcion atrapada: " << e.what() << endl;
    } catch (...) {
        cerr << "Ocurrio un error inesperado." << endl;
    }

    return 0;
}
