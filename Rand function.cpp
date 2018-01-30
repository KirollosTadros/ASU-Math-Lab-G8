
#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

 MyMatrix MyMatrix::rand(int rows,int cols)
 {
    float mat [rows][cols];
    srand(time(0));

    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;f++)
        {
            mat[i][j]=rand()%6;
        }
    }

    MyMatrix C(mat,rows,cols);

    return C;

 }
