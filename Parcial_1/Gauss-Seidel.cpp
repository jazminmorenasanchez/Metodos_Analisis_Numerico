#include <iostream>
#include <cmath>
#include <vector>
#include <stdexcept>  // Para manejo de excepciones

using namespace std;

const double epsilon = pow(10, -3); // Error tolerable mas preciso

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

// Funcion para aplicar el metodo de Gauss-Seidel
void gaussSeidel(vector<vector<double>>& A, vector<double>& B, vector<double>& X, int max_iter) {
    int n = A.size();

    // Verificar que la matriz A sea cuadrada y que B tenga el tamaño correcto
    if (B.size() != n) {
        throw invalid_argument("El tamano de la matriz A y el vector B no coincide.");
    }

    // Verificar si la matriz es diagonalmente dominante
    if (!isDiagonallyDominant(A)) {
        cout << "Advertencia: La matriz no es diagonalmente dominante. El metodo podria no converger." << endl;
    }

    vector<double> X_old(n);
    for (int iter = 0; iter < max_iter; iter++) {
        double max_error = 0.0;  // Usado para calcular el error de convergencia

        cout << "Iteracion " << iter + 1 << "..." << endl;
        // Mostrar el valor actual de X antes de la iteracion
        cout << "Estado actual de X: ";
        for (int i = 0; i < n; i++) {
            cout << "x" << i + 1 << " = " << X[i] << " ";
        }
        cout << endl;

        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            // Sumar los productos de las otras variables ya calculadas
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    sum += A[i][j] * X[j];
                }
            }

            if (fabs(A[i][i]) < epsilon) {
                throw runtime_error("Error: Pivote cercano a cero. No se puede dividir por cero.");
            }

            // Calcular el nuevo valor para X[i]
            double new_Xi = (B[i] - sum) / A[i][i];
            max_error = max(max_error, fabs(new_Xi - X[i]));  // Actualizar error maximo
            X[i] = new_Xi;

            // Mostrar el paso actual para X[i]
            cout << "Nuevo valor para x" << i + 1 << " = " << new_Xi << endl;
        }

        // Verificar si la solucion es suficientemente precisa
        if (max_error < epsilon) {
            cout << "Convergencia alcanzada en " << iter + 1 << " iteraciones." << endl;
            return;
        }
        cout << "Error maximo de la iteracion " << iter + 1 << " = " << max_error << endl;
    }
    cout << "Maximo numero de iteraciones alcanzado sin convergencia." << endl;
}

int main() {
    try {
        // Coeficientes del sistema de ecuaciones
        vector<vector<double>> A = {
            {3, -0.1, -0.2},
            {0.1, 7, -0.3},
            {0.3, -0.2, 10}
        };
        // Resultados del sistema
        vector<double> B = {7.85, 19.30, 71.40};

        // Inicializar el vector de soluciones con ceros
        vector<double> X = {0.0, 0.0, 0.0};

        int max_iter = 1000;  // Numero maximo de iteraciones

        // Aplicar el metodo de Gauss-Seidel
        gaussSeidel(A, B, X, max_iter);

        // Imprimir soluciones
        cout << "Soluciones aproximadas utilizando el metodo de Gauss-Seidel:" << endl;
        for (int i = 0; i < X.size(); i++) {
            cout << "x" << i + 1 << " = " << X[i] << endl;
        }
    } catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    } catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    } catch (...) {
        cout << "Ocurrio un error inesperado." << endl;
    }

    return 0;
}
