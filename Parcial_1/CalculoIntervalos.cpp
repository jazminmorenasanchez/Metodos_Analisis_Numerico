#include <iostream>
#include <iomanip>
#include <cmath>
#define PRESICION 6
using namespace std;

double f(double x){
    return (-x)/pow(M_E,x);
}

#define INTERVALOS 10
void tabula(double a, double b){
    int puntos = INTERVALOS +1;
    double ancho=(b-a)/ INTERVALOS;

    cout<<"\n\tx\tf(x) \n";
    for(int i=0;i<puntos;i++){
        cout<<"\t"<<a<<"\t"<<f(a)<<endl;
        a = a+ ancho;
    }
}

int main(){
    cout<<setprecision(PRESICION);
    cout<<"\nPrograma para encontrar el Intervalo Adecuado:";
    cout<<"\nIngrese el intervalo inicial [a,b]:\n";

    double a, b;
    cout<<"\na= ";
    cin>>a;
    cout<<"\nb= ";
    cin>>b;

    tabula(a,b);
}