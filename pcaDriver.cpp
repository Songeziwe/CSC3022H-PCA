#include <iostream>
#include <armadillo>
#include "pca.h"

using namespace std;
using namespace arma;
using namespace SBSSON002;

int main(){

  mat cov_matrix;
  Pca pca;

  pca.readFromFile("myData.csv");
  mat x = pca.createMatrix(0);
  mat y = pca.createMatrix(1);
  
  pca.subtractMean();

  mat x_variance = cov(x, x);
  mat y_variance = cov(y, y);
  mat xy_variance = cov(x, y);

  cov_matrix << x_variance(0,0) << xy_variance(0,0) << endr
             << xy_variance(0,0) << y_variance(0,0) << endr;

  cx_vec eigval;
  cx_mat eigvec;

  eig_gen(eigval, eigvec, cov_matrix);

  cout << "\nCovariance matrix:" << endl;
  
  cout << "\nCovariance matrix:" << endl
       << cov_matrix << endl 
       << "Eigenvalues:" << endl
       << eigval << endl
       << "Eigenvectors:" << endl
       << eigvec << endl; 

  return 0;
}