`#include<iostream>
#include <math.h>
using namespace std;


   MyMatrix MyMatrix::sin ()
   {

       float **a=this->matrix;
          float **c=new float *[this->rows];
           for(int i=0;i<this->rows;i++)
           {
               c[i]=new float [this->cols]
           }


        for (int i=0; i<rows;i++)
           {
               for (int j=0;j<cols;j++)
               {
                   c[i][j]= sin(a[i][j]);
               }
           }

            my_matrix C(c,this->rows,this->cols);
           for (int i=0;i<rows;i++)
           {
               delete [] c[i];
           }
           delete [] c;
           retrun C;
   }
   MyMatrix MyMatrix::cos ()
   {

       float **a=this->matrix;
          float **c=new float *[this->rows];
           for(int i=0;i<this->rows;i++)
           {
               c[i]=new float [this->cols]
           }


        for (int i=0; i<rows;i++)
           {
               for (int j=0;j<cols;j++)
               {
                   c[i][j]= cos(a[i][j]);
               }
           }

            my_matrix C(c,this->rows,this->cols);
           for (int i=0;i<rows;i++)
           {
               delete [] c[i];
           }
           delete [] c;
           retrun C;
   }
   MyMatrix MyMatrix::tan ()
   {

       float **a=this->matrix;
          float **c=new float *[this->rows];
           for(int i=0;i<this->rows;i++)
           {
               c[i]=new float [this->cols]
           }


        for (int i=0; i<rows;i++)
           {
               for (int j=0;j<cols;j++)
               {
                   c[i][j]= tan(a[i][j]);
               }
           }

            my_matrix C(c,this->rows,this->cols);
           for (int i=0;i<rows;i++)
           {
               delete [] c[i];
           }
           delete [] c;
           retrun C;
   }


   MyMatrix MyMatrix::asin ()
   {

       float **a=this->matrix;
          float **c=new float *[this->rows];
           for(int i=0;i<this->rows;i++)
           {
               c[i]=new float [this->cols]
           }


        for (int i=0; i<rows;i++)
           {
               for (int j=0;j<cols;j++)
               {
                   c[i][j]= asin(a[i][j]);
               }
           }

            my_matrix C(c,this->rows,this->cols);
           for (int i=0;i<rows;i++)
           {
               delete [] c[i];
           }
           delete [] c;
           retrun C;
   }
   MyMatrix MyMatrix::acos ()
   {

       float **a=this->matrix;
          float **c=new float *[this->rows];
           for(int i=0;i<this->rows;i++)
           {
               c[i]=new float [this->cols]
           }


        for (int i=0; i<rows;i++)
           {
               for (int j=0;j<cols;j++)
               {
                   c[i][j]= acos(a[i][j]);
               }
           }

            my_matrix C(c,this->rows,this->cols);
           for (int i=0;i<rows;i++)
           {
               delete [] c[i];
           }
           delete [] c;
           retrun C;
   }
   MyMatrix MyMatrix::atan()
   {

       float **a=this->matrix;
          float **c=new float *[this->rows];
           for(int i=0;i<this->rows;i++)
           {
               c[i]=new float [this->cols]
           }


        for (int i=0; i<rows;i++)
           {
               for (int j=0;j<cols;j++)
               {
                   c[i][j]= atan(a[i][j]);
               }
           }

            my_matrix C(c,this->rows,this->cols);
           for (int i=0;i<rows;i++)
           {
               delete [] c[i];
           }
           delete [] c;
           retrun C;
   }
   MyMatrix MyMatrix::log ()
   {

       float **a=this->matrix;
          float **c=new float *[this->rows];
           for(int i=0;i<this->rows;i++)
           {
               c[i]=new float [this->cols]
           }


        for (int i=0; i<rows;i++)
           {
               for (int j=0;j<cols;j++)
               {
                   c[i][j]= log(a[i][j]);
               }
           }

            my_matrix C(c,this->rows,this->cols);
           for (int i=0;i<rows;i++)
           {
               delete [] c[i];
           }
           delete [] c;
           retrun C;
   }
   MyMatrix MyMatrix::log10 ()
   {

       float **a=this->matrix;
          float **c=new float *[this->rows];
           for(int i=0;i<this->rows;i++)
           {
               c[i]=new float [this->cols]
           }


        for (int i=0; i<rows;i++)
           {
               for (int j=0;j<cols;j++)
               {
                   c[i][j]= log10(a[i][j]);
               }
           }

            my_matrix C(c,this->rows,this->cols);
           for (int i=0;i<rows;i++)
           {
               delete [] c[i];
           }
           delete [] c;
           retrun C;
   }
   MyMatrix MyMatrix::pow ()
   {

       float **a=this->matrix;
          float **c=new float *[this->rows];
           for(int i=0;i<this->rows;i++)
           {
               c[i]=new float [this->cols]
           }


        for (int i=0; i<rows;i++)
           {
               for (int j=0;j<cols;j++)
               {
                   c[i][j]= pow(a[i][j]);
               }
           }

            my_matrix C(c,this->rows,this->cols);
           for (int i=0;i<rows;i++)
           {
               delete [] c[i];
           }
           delete [] c;
           retrun C;
   }
   MyMatrix MyMatrix::sqrt ()
   {

       float **a=this->matrix;
          float **c=new float *[this->rows];
           for(int i=0;i<this->rows;i++)
           {
               c[i]=new float [this->cols]
           }


        for (int i=0; i<rows;i++)
           {
               for (int j=0;j<cols;j++)
               {
                   c[i][j]= sqrt(a[i][j]);
               }
           }

            my_matrix C(c,this->rows,this->cols);
           for (int i=0;i<rows;i++)
           {
               delete [] c[i];
           }
           delete [] c;
           retrun C;
   }









`
