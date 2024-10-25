#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

using namespace std;

typedef vector<vector<double>> Matrix;
typedef vector<double> Vector;

// Función para mostrar una matriz
void printMatrix(const Matrix& mat) {
    for (const auto& row : mat) {
        for (double val : row) {
            cout << val << "\t";
        }
        cout << endl;
    }
}

// Función para mostrar un vector
void printVector(const Vector& vec) {
    for (double val : vec) {
        cout << val << "\t";
    }
    cout << endl;
}

// Función para crear una matriz identidad de tamaño n
Matrix identityMatrix(int n) {
    Matrix I(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++) {
        I[i][i] = 1.0;
    }
    return I;
}

// Función para calcular la inversa de una matriz usando el método de Gauss-Jordan
Matrix inverseMatrix(const Matrix& A) {
    int n = A.size();
    Matrix augmentedMatrix(n, vector<double>(2 * n));

    // Crear una matriz aumentada [A | I]
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmentedMatrix[i][j] = A[i][j];        // Parte A
            augmentedMatrix[i][j + n] = (i == j) ? 1.0 : 0.0;  // Parte I
        }
    }

    // Aplicar eliminación Gaussiana para convertir A en I y obtener A^-1
    for (int i = 0; i < n; i++) {
        // Verificar si el pivote es cero y buscar una fila para intercambiar
        if (augmentedMatrix[i][i] == 0) {
            bool swapped = false;
            for (int k = i + 1; k < n; k++) {
                if (augmentedMatrix[k][i] != 0) {
                    swap(augmentedMatrix[i], augmentedMatrix[k]);
                    swapped = true;
                    break;
                }
            }
            if (!swapped) {
                throw runtime_error("La matriz no es invertible.");
            }
        }

        // Hacer que el pivote sea 1 dividiendo toda la fila
        double pivot = augmentedMatrix[i][i];
        for (int j = 0; j < 2 * n; j++) {
            augmentedMatrix[i][j] /= pivot;
        }

        // Hacer que todos los demás elementos de la columna sean cero
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = augmentedMatrix[k][i];
                for (int j = 0; j < 2 * n; j++) {
                    augmentedMatrix[k][j] -= factor * augmentedMatrix[i][j];
                }
            }
        }
    }

    // Extraer la inversa (parte derecha de la matriz aumentada)
    Matrix inverse(n, vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inverse[i][j] = augmentedMatrix[i][j + n];
        }
    }

    return inverse;
}

// Función para multiplicar una matriz por un vector
Vector multiplyMatrixVector(const Matrix& A, const Vector& b) {
    int n = A.size();
    Vector result(n, 0.0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i] += A[i][j] * b[j];
        }
    }
    return result;
}

// Función para calcular la norma de un vector
double vectorNorm(const Vector& v) {
    double sum = 0.0;
    for (double val : v) {
        sum += val * val;
    }
    return sqrt(sum);
}

// Función para calcular la norma de una matriz
double matrixNorm(const Matrix& A) {
    double maxSum = 0.0;
    for (const auto& row : A) {
        double rowSum = 0.0;
        for (double val : row) {
            rowSum += fabs(val);
        }
        maxSum = max(maxSum, rowSum);
    }
    return maxSum;
}

// Función para calcular el número de condición
double conditionNumber(const Matrix& A) {
    Matrix A_inv = inverseMatrix(A);
    double normA = matrixNorm(A);
    double normA_inv = matrixNorm(A_inv);
    return normA * normA_inv;
}

int main() {
    // Definir una matriz de tamaño 2x2 y un vector de resultados b
    Matrix A = {{1, 2},
                {1.1, 2}};
    
    Vector b = {10.00, 10.40};

    cout << "Matriz original A:" << endl;
    printMatrix(A);

    cout << "\nVector b:" << endl;
    printVector(b);

    try {
        // Calcular la inversa de A
        Matrix A_inv = inverseMatrix(A);

        cout << "\nInversa de A:" << endl;
        printMatrix(A_inv);

        // Resolver el sistema Ax = b usando la inversa de A
        Vector x = multiplyMatrixVector(A_inv, b);

        cout << "\nSolución del sistema Ax = b (x):" << endl;
        printVector(x);

        // Calcular el número de condición
        double condA = conditionNumber(A);
        cout << "\nNúmero de condición de A: " << condA << endl;

        // Analizar estabilidad
        if (condA < 100) {
            cout << "El sistema es estable." << endl;
        } else {
            cout << "El sistema es inestable." << endl;
        }

    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
