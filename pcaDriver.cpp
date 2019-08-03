#include <iostream>
#include <armadillo>
#include "pca.h"

using namespace std;
using namespace arma;
using namespace SBSSON002;

int main(){
  double** array = subtractMean(readFromFile("myData.csv"));
  mat x = createMatrix(array, 0);
  mat y = createMatrix(array, 1);

  mat covariance = cov(y, y);
  cout << covariance << endl;
  return 0;
}
