#include<iostream>
 using namespace std;

 MyMatrix MyMatrix::zeros(int rows,int cols)
 {

     float mat [rows][cols];
     for (int i=0; i<rows;i++)
     {
         for (int j=0; j<cols;j++)
         {
             mat[i][j]=0;
         }
     }
     MyMatrix C(mat,rows,cols);
     return C;
 }
