#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <limits>
#include <stdexcept>

using namespace std;

typedef vector<vector<double>> Matrix;

// Función para calcular la norma infinita de una matriz
double infinityNorm(const Matrix& mat) {
    double maxSum = 0.0;
    for (const auto& row : mat) {
        double rowSum = 0.0;
        for (double val : row) {
            rowSum += abs(val);
        }
        maxSum = max(maxSum, rowSum);
    }
    return maxSum;
}

// Función para obtener la inversa de una matriz usando el método de Gauss-Jordan
bool inverseMatrix(const Matrix& mat, Matrix& inverse) {
    int n = mat.size();
    inverse = Matrix(n, vector<double>(n, 0.0));

    Matrix augmented(mat);

    for (int i = 0; i < n; ++i) {
        augmented[i].resize(2 * n);
        augmented[i][i + n] = 1.0;
    }

    for (int i = 0; i < n; ++i) {
        double maxElem = abs(augmented[i][i]);
        int maxRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (abs(augmented[k][i]) > maxElem) {
                maxElem = abs(augmented[k][i]);
                maxRow = k;
            }
        }

        if (maxElem < numeric_limits<double>::epsilon()) {
            cerr << "Error: La matriz es singular y no tiene inversa." << endl;
            return false;
        }

        swap(augmented[i], augmented[maxRow]);

        double diag = augmented[i][i];
        for (int j = 0; j < 2 * n; ++j) {
            augmented[i][j] /= diag;
        }

        for (int k = 0; k < n; ++k) {
            if (k != i) {
                double factor = augmented[k][i];
                for (int j = 0; j < 2 * n; ++j) {
                    augmented[k][j] -= factor * augmented[i][j];
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inverse[i][j] = augmented[i][j + n];
        }
    }

    return true;
}

// Función para imprimir matrices
void printMatrix(const Matrix& mat) {
    for (const auto& row : mat) {
        for (double val : row) {
            cout << setw(10) << setprecision(4) << fixed << val << " ";
        }
        cout << endl;
    }
}

// Función principal para calcular el número de condición
double conditionNumber(const Matrix& mat) {
    try {
        cout << "Calculando la matriz inversa...\n";
        Matrix inverse;

        if (!inverseMatrix(mat, inverse)) {
            throw runtime_error("La matriz es singular y no tiene inversa.");
        }

        cout << "Matriz A:\n";
        printMatrix(mat);

        cout << "\nMatriz Inversa A^-1:\n";
        printMatrix(inverse);

        double normA = infinityNorm(mat);
        double normAInv = infinityNorm(inverse);

        cout << "\nNorma de A: " << fixed << setprecision(4) << normA << endl;
        cout << "Norma de A^-1: " << fixed << setprecision(4) << normAInv << endl;

        double condA = normA * normAInv;
        cout << "\ncond(A) = Norma de A * Norma de A^-1 = " 
             << normA << " * " << normAInv << " = " << condA << endl;

        return condA;

    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
        return -1;
    } catch (const exception& e) {
        cerr << "Error inesperado: " << e.what() << endl;
        return -1;
    }
}

int main() {
    //Apartir de Ax=H.  Definir el tamaño de la matriz A y los valores
    int n = 3; 
    Matrix A = {
        {2, -9, 7.1},  
        {9.01, 3.2, 2.05},
        {4.2, 18.9, 14.1}
    };

    cout << "Matriz A:" << endl;
    double condA = conditionNumber(A);
    if (condA != -1) {
        cout << "\nEl numero de condicion de la matriz es: " << fixed << setprecision(4) << condA << endl;
    }

    cout <<"\nLa matriz estara bien condicionada si cond(A) = 1 o proximo a 1. (indica estabilidad en los cálculos numericos que involucran esa matriz.)";
    cout << "\nLa matriz estara mal condicionada si cond(A) es un numero muy grande.\n";
    cout << "\nUna matriz con valores muy pequenios o cercanos a cero en sus filas o columnas, generalmente estara mal condicionada porque cond(A) tendera a ser muy grande.";

    return 0;
}
