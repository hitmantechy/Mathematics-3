//Writing program for curve fitting by method of group averages
//version 1.0.0 (fitting of straight line according to given points)
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

 void groupAverages(float* x,float* y,int n,int type){
       float x1{},y1{},x2{},y2{},a,b;
        switch(type){
            
            case 1: 
                    for(int i=0;i<n/2;i++){x1 += x[i] ; y1 += y[i];}
                    x1/=(n/2);
                    y1/=(n/2);
                    for(int i=n/2;i<n;i++){x2 += x[i] ; y2 += y[i];}
                    x2/=(n/2);
                    y2/=(n/2);
                    a = (y2 - y1);
                    a/=(x2-x1);

                    b = y2 - x2 * a;
                    cout<<"The fitted curve is Y = "<<a<<"X + ("<<b<<")"<<endl;
                    break;
            default : cout<<"No valid operation selected.";
        }
 }

int main(){
    int n,type;
    cout<<"Enter the number of entries. \n";
    cin>>n;
    cout<<"Enter the type of curve fitting \n 1 - Straight line \n 2 - Quadratic polynomial \n 3 - Exponential "<<endl;
    cin>>type;
    cout<<"Enter data for x \n";
    float x[n],y[n];
    for(int i=0;i<n;i++){
        cin>>x[i];
    }
    cout<<"Enter data for x \n";
    for(int i=0;i<n;i++){
        cin>>y[i];
    }
    groupAverages(x,y,n,type);
}