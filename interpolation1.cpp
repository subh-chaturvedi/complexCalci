#include <iostream>
#include <vector>
using namespace std;

// Function to covert Nested Vector form of polynomial to the written algebraic form.
string polyPrinter(vector<vector<double>> poly){

    string polynomial{""};

    for(int i=0;i<poly.size();i++){
        //Adds each polynomial element to the existing string by concatenation
        //Only uses atmost 4 decimal points to improve readability
        //Converts power of x to integer because the calculations were done in double form
        polynomial = polynomial + "+ " + to_string(poly[i][0]).substr(0,4) + "x^" + to_string(int(poly[i][1])) + " ";
    }
    return polynomial;
}

// Function to simplify the extensive polynomial, ie. combine all coefficients with same powers of x
vector<vector<double>> simplifier(vector<vector<double>> poly){

    vector<vector<double>> finalPoly;
    for(int i=0;i<poly.size();i++){
        for(int j=i+1;j<poly.size();j++){
            // Adds the coefficients of the elements which have the same power of x
            // After addition of coefficients, converts the rest of the elements to 0 for easy removal
            if(poly[i][1]==poly[j][1]){
                poly[i][0] = poly[i][0] + poly[j][0];
                poly[j][0]=0;
            }
        }
    }
    for(int i=0;i<poly.size();i++){
        // Does not push elements with coefficient as 0 to the final polynomial vector
        if(poly[i][0]>=0.0001 || poly[i][0]<=-0.0001){
            finalPoly.push_back(poly[i]);
        }
    }
    return finalPoly;
}

// Function to multiply polynomials in nested vector form
vector<vector<double>> polynomialMultiplier(vector<vector<double>> p1, vector<vector<double>> p2){

    vector<vector<double>> result;

    for(int i=0;i<p1.size();i++){
        for(int j=0; j<p2.size();j++){
            //Polynomial of the form a(x^n) and b(x^m) is stored as [a*b,n+m]
            result.push_back({p1[i][0] * p2[j][0],p1[i][1] + p2[j][1]});
        }
    }

    return result;
} 

// Function to find the l(x)f element of lagrange interpolation equation
vector<vector<double>> lfinder(int i, double functionValues[][2],int n, double f){

    vector<vector<double>> numerator{{1,0}};
    float denumerator = 1;

    for(int j=0;j<n;j++){
        if(j != i){
            // denumerator is the product of (xi - xn) where n={0,1,2,...i-1,i+1,...n}
            denumerator = denumerator * (functionValues[i][0] - functionValues[j][0]);
        }
    }

    for(int j=0;j<n;j++){
        if(j != i){
                // numerator is the product of (x - xn) where n={0,1,2,...i-1,i+1,...n}
                numerator = polynomialMultiplier(numerator,{{1,1},{(functionValues[j][0]*-1),0}});
        }
    }

    for(int k=0;k<numerator.size();k++){
        //Multipies the numerator with the value of (f/denumerator)
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

        //Storing the values in a nested array
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
