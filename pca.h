

#ifndef _PCA
#define _PCA

#include <armadillo>
#include <memory>
#include <string>
namespace SBSSON002 {
    class Pca {
    private:
        int rows = 64, columns = 2;
        double** data_array_ptr = new double*[rows];
        double* means = new double[2];
    public:
        // Default constructor and Destructor
        Pca(void);
        ~Pca(void);

        // Copy and move constructors
        Pca(const Pca&);
        Pca(Pca&&);

        // Copy and Move assignment operators
        Pca& operator=(const Pca&);
        Pca& operator=(Pca&&);

        void init_array();
        void readFromFile(std::string filename);
        double* meanForEachDimension();
        void subtractMean();
        arma::mat createMatrix(int dimension);
    };
}
#endif