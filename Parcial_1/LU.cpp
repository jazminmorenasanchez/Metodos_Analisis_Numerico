#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Función para hacer la factorización LU
void luDecomposition(const vector<vector<double>>& A, vector<vector<double>>& L, vector<vector<double>>& U) {
    int n = A.size();
    
    for (int i = 0; i < n; i++) {
        // Llenar la matriz U
        for (int k = i; k < n; k++) {
            double sum = 0.0;
            for (int j = 0; j < i; j++) {
                sum += (L[i][j] * U[j][k]);
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
                    sum += (L[k][j] * U[j][i]);
                }
                L[k][i] = (A[k][i] - sum) / U[i][i];
            }
        }
    }
}

// Función para resolver LY = B
vector<double> forwardSubstitution(const vector<vector<double>>& L, const vector<double>& B, double errorThreshold) {
    int n = L.size();
    vector<double> Y(n, 0);
    
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < i; j++) {
            sum += L[i][j] * Y[j];
        }
        Y[i] = (B[i] - sum) / L[i][i];
        if (fabs(Y[i]) < errorThreshold) {
            Y[i] = 0; // Ajuste basado en el umbral de error
        }
    }
    
    return Y;
}

// Función para resolver UX = Y
vector<double> backSubstitution(const vector<vector<double>>& U, const vector<double>& Y, double errorThreshold) {
    int n = U.size();
    vector<double> X(n, 0);
    
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++) {
            sum += U[i][j] * X[j];
        }
        X[i] = (Y[i] - sum) / U[i][i];
        if (fabs(X[i]) < errorThreshold) {
            X[i] = 0; // Ajuste basado en el umbral de error
        }
    }
    
    return X;
}

int main() {
    // Definir los parámetros directamente en el código
    int n = 3;  // Tamaño de la matriz
    
    vector<vector<double>> A = {  // Coeficientes de la matriz A
        {3.0, -0.1, -0.2},
        {0.1, 7.0, -0.3},
        {0.3, -0.2, 10.0}
    };
    
    vector<double> B = {7.85, 19.30, 71.40};  // Resultados del sistema
    
    double errorThreshold = 1e-5;  // Umbral de error
    
    // Inicializar las matrices L y U
    vector<vector<double>> L(n, vector<double>(n, 0));
    vector<vector<double>> U(n, vector<double>(n, 0));
    
    // Realizar la descomposición LU
    luDecomposition(A, L, U);
    
    // Resolver el sistema usando sustitución hacia adelante y hacia atrás
    vector<double> Y = forwardSubstitution(L, B, errorThreshold);
    vector<double> X = backSubstitution(U, Y, errorThreshold);
    
    // Imprimir las soluciones
    cout << "Soluciones aproximadas utilizando el metodo de LU:" << endl;
    for (int i = 0; i < X.size(); i++) {
        cout << "x" << i + 1 << " = " << X[i] << endl;
    }

    return 0;
}
