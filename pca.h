

#ifndef _PCA
#define _PCA

#include <armadillo>
#include <memory>
#include <string>
namespace SBSSON002 {

    double** readFromFile(std::string filename);
    double* meanForEachDimension(double** data_ptr);
    double** subtractMean(double** data_ptr);
    arma::mat createMatrix(double** data_ptr, int dimension);
}

#endif