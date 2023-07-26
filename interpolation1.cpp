#include <iostream>
#include <vector>
using namespace std;

string polyPrinter(vector<vector<double>> poly){

    string polynomial{""};

    for(int i=0;i<poly.size();i++){
        polynomial = polynomial + "+ " + to_string(poly[i][0]) + "x^" + to_string(int(poly[i][1])) + " ";
    }
    return polynomial;
}

vector<vector<double>> simplifier(vector<vector<double>> poly){

    vector<vector<double>> finalPoly;
    for(int i=0;i<poly.size();i++){
        for(int j=i+1;j<poly.size();j++){
            if(poly[i][1]==poly[j][1]){
                poly[i][0] = poly[i][0] + poly[j][0];
                poly[j][0]=0;
            }
        }
    }
    for(int i=0;i<poly.size();i++){
        if(poly[i][0]!=0){
            finalPoly.push_back(poly[i]);
        }
    }
    return finalPoly;
}

vector<vector<double>> polynomialMultiplier(vector<vector<double>> p1, vector<vector<double>> p2){

    vector<vector<double>> result;

    for(int i=0;i<p1.size();i++){
        for(int j=0; j<p2.size();j++){
            result.push_back({p1[i][0] * p2[j][0],p1[i][1] + p2[j][1]});
        }
    }

    return result;
} 

vector<vector<double>> lfinder(int i, double functionValues[][2],int n, double f){

    vector<vector<double>> numerator{{1,0}};
    float denumerator = 1;

    for(int j=0;j<n;j++){
        if(j != i){
            denumerator = denumerator * (functionValues[i][0] - functionValues[j][0]);
        }
    }

    for(int j=0;j<n;j++){
        if(j != i){
                //cout << "\nStep (whole)" << j << " "<< 1 << " "<< (functionValues[j][0]*-1);
                numerator = polynomialMultiplier(numerator,{{1,1},{(functionValues[j][0]*-1),0}});
        }
    }

    for(int k=0;k<numerator.size();k++){
        numerator[k][0] = numerator[k][0]*(f/denumerator);
    }

    return numerator;
}

int main(){
   
    int n{3};

    cout<<"Enter Number of Values: ";
    cin>>n;

    double functionValues[n][2];
    double x,fx;

    for(int i = 0;i<n;i++){
        cout<<"Enter x: ";
        cin>>x;
        cout<<"Enter f(x): ";
        cin>>fx;

        functionValues[i][0]={x};
        functionValues[i][1]={fx};
    }
    
    vector<vector<double>> polynomial{{0,0}};
    vector<vector<double>> subPolynomial;
    string polyToPrint{""};

    for(int i = 0;i<n;i++){
        if(functionValues[i][1]!=0){
            subPolynomial = lfinder(i, functionValues, n, functionValues[i][1]);
            polynomial.insert(polynomial.end(), subPolynomial.begin(), subPolynomial.end());
        }
    }

    polynomial = simplifier(polynomial);
    polyToPrint = polyPrinter(polynomial).substr(1);

    cout <<"\n  Interpolated Polynomial: " << polyToPrint << endl;

    return 0;
}
