#include<iostream>
#include<sstream>
#include<fstream>
#include<iomanip>


using namespace std;

int main ()
{
    int i=0, x=0, y=0;
    ofstream myfile;
    myfile.open ("random_numbers");

    for (int j=0; j < 300; j++)
    {
        myfile  << i ;
        myfile  << " " << x;
        i++;
        x = x + 2;
        y = x + 1;
    }
    myfile.close();
    return 0;
}