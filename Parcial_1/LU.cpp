#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <stdexcept>

using namespace std;

typedef vector<vector<double>> Matrix;

// Funcion para hacer la factorizacion LU
void luDecomposition(const Matrix& A, Matrix& L, Matrix& U) {
    int n = A.size();

    for (int i = 0; i < n; i++) {
        // Llenar la matriz U
        for (int k = i; k < n; k++) {
            double sum = 0.0;
            for (int j = 0; j < i; j++) {
                sum += L[i][j] * U[j][k];
            }
            U[i][k] = A[i][k] - sum;
        }

        // Llenar la matriz L
        for (int k = i; k < n; k++) {
            if (i == k) {
                L[i][i] = 1; // La diagonal de L es 1
            } else {
                double sum = 0.0;
                for (int j = 0; j < i; j++) {
                    sum += L[k][j] * U[j][i];
                }
                if (fabs(U[i][i]) < 1e-10) {
                    throw runtime_error("Error: la matriz es singular o casi singular, no se puede factorizar.");
                }
                L[k][i] = (A[k][i] - sum) / U[i][i];
            }
        }

        // Mostrar L y U en cada iteracion
        cout << "Paso " << i + 1 << " de la factorizacion LU:" << endl;
        cout << "Matriz L:" << endl;
        for (const auto& row : L) {
            for (double val : row) {
                cout << setw(10) << setprecision(4) << fixed << val << " ";
            }
            cout << endl;
        }
        cout << "Matriz U:" << endl;
        for (const auto& row : U) {
            for (double val : row) {
                cout << setw(10) << setprecision(4) << fixed << val << " ";
            }
            cout << endl;
        }
        cout << "--------------------------------------" << endl;
    }
}

// Funcion para resolver LY = B usando sustitucion hacia adelante
vector<double> forwardSubstitution(const Matrix& L, const vector<double>& B) {
    int n = L.size();
    vector<double> Y(n, 0);

    cout << "Resolviendo LY = B mediante sustitucion hacia adelante:" << endl;
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        cout << "Y[" << i + 1 << "] = (B[" << i + 1 << "]";
        for (int j = 0; j < i; j++) {
            cout << " - L[" << i + 1 << "][" << j + 1 << "] * Y[" << j + 1 << "]";
            sum += L[i][j] * Y[j];
        }
        cout << ") / L[" << i + 1 << "][" << i + 1 << "]" << endl;
        
        if (fabs(L[i][i]) < 1e-10) {
            throw runtime_error("Error: division por cero al resolver LY = B.");
        }
        Y[i] = (B[i] - sum) / L[i][i];
        
        cout << "Y[" << i + 1 << "] = " << setprecision(4) << fixed << Y[i] << endl;
    }
    return Y;
}

// Funcion para resolver UX = Y usando sustitucion hacia atras
vector<double> backSubstitution(const Matrix& U, const vector<double>& Y) {
    int n = U.size();
    vector<double> X(n, 0);

    cout << "\nResolviendo UX = Y mediante sustitucion hacia atras:" << endl;
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        cout << "X[" << i + 1 << "] = (Y[" << i + 1 << "]";
        for (int j = i + 1; j < n; j++) {
            cout << " - U[" << i + 1 << "][" << j + 1 << "] * X[" << j + 1 << "]";
            sum += U[i][j] * X[j];
        }
        cout << ") / U[" << i + 1 << "][" << i + 1 << "]" << endl;
        
        if (fabs(U[i][i]) < 1e-10) {
            throw runtime_error("Error: division por cero al resolver UX = Y.");
        }
        X[i] = (Y[i] - sum) / U[i][i];
        
        cout << "X[" << i + 1 << "] = " << setprecision(4) << fixed << X[i] << endl;
    }
    return X;
}

// Funcion para imprimir un vector (solucion)
void printSolution(const vector<double>& X) {
    cout << "\nSoluciones aproximadas:" << endl;
    for (int i = 0; i < X.size(); i++) {
        cout << "x" << i + 1 << " = " << setw(10) << setprecision(4) << fixed << X[i] << endl;
    }
}

int main() {
    try {
        // Definir la matriz A y el vector B directamente en el codigo
        int n = 3;  // Cambia este valor para matrices de otro tamaño
        Matrix A = {
            {3.0, -0.1, -0.2},
            {0.1, 7.0, -0.3},
            {0.3, -0.2, 10.0}
        };
        vector<double> B = {7.85, 19.30, 71.40};

        // Inicializar matrices L y U como matrices de ceros
        Matrix L(n, vector<double>(n, 0));
        Matrix U(n, vector<double>(n, 0));

        // Realizar la descomposicion LU
        cout << "Factorizacion LU de la matriz A:" << endl;
        luDecomposition(A, L, U);

        // Resolver el sistema LY = B
        vector<double> Y = forwardSubstitution(L, B);

        // Resolver el sistema UX = Y
        vector<double> X = backSubstitution(U, Y);

        // Imprimir la solucion final
        printSolution(X);

    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
    } catch (const exception& e) {
        cerr << "Error inesperado: " << e.what() << endl;
    }

    return 0;
}
