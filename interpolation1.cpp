#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

vector<vector<double>> simplifier(){
    
}

string polyPrinter(vector<vector<double>> poly){

    string polynomial{""};

    for(int i=0;i<poly.size();i++){
        polynomial = polynomial + "+ " + to_string(poly[i][0]) + "x^" + to_string(int(poly[i][1])) + " ";
    }
    return polynomial;
}

vector<vector<double>> polynomialMultiplier(vector<vector<double>> p1, vector<vector<double>> p2){
    vector<vector<double>> result;

    for(int i=0;i<p1.size();i++){
        for(int j=0; j<p2.size();j++){
            //cout << "#"<<i<<j<<"\n";

            result.push_back({p1[i][0] * p2[j][0],p1[i][1] + p2[j][1]});
        }
    }

    //cout<< result.size();
    //cout<< polyPrinter(result);

    return result;
} 

vector<vector<double>> lfinder(int i, double functionValues[][2],int n, double f){
    cout<<"\nLFINDER"<< " "<<f <<endl;
    vector<vector<double>> numerator{{1,0}};
    float denumerator = 1;

    for(int j=0;j<n;j++){
        if(j != i){
            denumerator = denumerator * (functionValues[i][0] - functionValues[j][0]);
        }
    }
    cout <<"Denum " << denumerator;

    int divided = 0;

    for(int j=0;j<n;j++){
        if(j != i){
            if (divided ==0){
                cout << "\nStep (division)" << j << " "<< f/denumerator << " "<< (functionValues[j][0]*f*-1)/denumerator;
                numerator = polynomialMultiplier(numerator,{{f/denumerator,1},{(functionValues[j][0]*f*-1)/denumerator,0}});
                divided=1;
            }
            else{
                cout << "\nStep (whole)" << j << " "<< 1 << " "<< (functionValues[j][0]-1);
                numerator = polynomialMultiplier(numerator,{{1,1},{(functionValues[j][0]-1),0}});
            }
        }
    }

    return numerator;
}

int main(){
   
    int n{3};

    //cout<<"Enter Number of Values: ";
    //cin>>n;

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
    
    string polynomial{""};
    string subPolynomial{""};

    for(int i = 0;i<n;i++){
        if(functionValues[i][1]!=0){
            subPolynomial = polyPrinter(lfinder(i, functionValues, n, functionValues[i][1]));
            cout << "\n&SP "<< subPolynomial;
            polynomial = polynomial + subPolynomial;
        }
    }

    cout <<"\nFINAL" << polynomial;

    //polynomialMultiplier({{1,1},{-3,0}},{{1,1},{-2,0}});

    return 0;
}