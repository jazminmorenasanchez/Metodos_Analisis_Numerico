#include <iostream>
#include <cmath>
#include <vector>
#include <stdexcept>  // Para manejo de excepciones

using namespace std;

const double epsilon = pow(10,-3); // Error tolerable más preciso

// Verifica si la matriz es diagonalmente dominante
bool isDiagonallyDominant(const vector<vector<double>>& A) {
    int n = A.size();
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            if (i != j) sum += fabs(A[i][j]);
        }
        if (fabs(A[i][i]) < sum) {
            return false;
        }
    }
    return true;
}

// Función para aplicar el método de Gauss-Seidel
void gaussSeidel(const vector<vector<double>>& A, const vector<double>& B, vector<double>& X, int max_iter) {
    int n = A.size();

    // Verificar que la matriz A sea cuadrada y que B tenga el tamaño correcto
    if (B.size() != n) {
        throw invalid_argument("El tamanio de la matriz A y el vector B no coincide.");
    }

    // Verificar si la matriz es diagonalmente dominante
    if (!isDiagonallyDominant(A)) {
        cout << "Advertencia: La matriz no es diagonalmente dominante. El metodo podria no converger." << endl;
    }

    vector<double> X_old(n);
    for (int iter = 0; iter < max_iter; iter++) {
        double max_error = 0.0;  // Usado para calcular el error de convergencia

        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    sum += A[i][j] * X[j];
                }
            }

            if (fabs(A[i][i]) < epsilon) {
                throw runtime_error("Error: Pivote cercano a cero. No se puede dividir por cero.");
            }

            double new_Xi = (B[i] - sum) / A[i][i];
            max_error = max(max_error, fabs(new_Xi - X[i]));  // Actualizar error máximo
            X[i] = new_Xi;
        }

        // Verificar si la solución es suficientemente precisa
        if (max_error < epsilon) {
            cout << "Convergencia alcanzada en " << iter + 1 << " iteraciones." << endl;
            return;
        }
    }
    cout << "Maximo número de iteraciones alcanzado sin convergencia." << endl;
}

int main() {
    // Coeficientes del sistema de ecuaciones
    vector<vector<double>> A = {
        {3, -0.1, -0.2},
        {0.1, 7, -0.3},
        {0.3, -0.2, 10}
    };
    // Resultados del sistema
    vector<double> B = {7.85, 19.30, 71.40};

    // ponemos las x1, x2, ..., xn con valores nulos, ceros.
    vector<double> X = {0.0, 0.0, 0.0};

    int max_iter = 1000;  // Número máximo de iteraciones

    try {
        gaussSeidel(A, B, X, max_iter);

        // Imprimir soluciones
        cout << "Soluciones aproximadas utilizando el metodo de Gauss-Seidel:" << endl;
        for (int i = 0; i < X.size(); i++) {
            cout << "x" << i + 1 << " = " << X[i] << endl;
        }
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
