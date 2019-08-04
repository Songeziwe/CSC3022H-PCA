#include <iostream>
#include <armadillo>
#include <fstream>
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

  // Covariance matrix
  cov_matrix << x_variance(0,0) << xy_variance(0,0) << endr
             << xy_variance(0,0) << y_variance(0,0) << endr;

  cx_vec eigval;
  cx_mat eigvec;

  // Calculate Eigenvalues and Eigenvectors
  eig_gen(eigval, eigvec, cov_matrix);
  double totalVariance = cov_matrix(0,0) + cov_matrix(1,1) + 2 * cov_matrix(0,1);
  
  // Calculate proportion for component 1 and 2
  double x_proportion = cov_matrix(0,0) / totalVariance;
  double y_proportion = cov_matrix(1,1) / totalVariance;

  // Print out the result 
  cout << "\nCovariance matrix:" << endl
       << cov_matrix << endl 
       << "Eigenvalues:" << endl
       << eigval << endl
       << "Eigenvectors:" << endl
       << eigvec << endl
       << "Total variance:" << endl 
       << " " << totalVariance << endl
       << "\nProportion for principal component 1: " << endl
       << " " << x_proportion << endl
       << "\nProportion for principal component 2: " << endl
       << " " << y_proportion << "\n"<< endl; 
  

  return 0;
}