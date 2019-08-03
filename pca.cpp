
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <armadillo>
#include "pca.h"

namespace SBSSON002 {
    using namespace std;
    using namespace arma;

    // Default constructor
    Pca::Pca(void){
        init_array();
    }
    
    // destructor
    Pca::~Pca(void){
        if(data_array_ptr != nullptr){
           for(int i = 0; i < rows; ++i){
                delete[] data_array_ptr[i];
            }
            delete[] data_array_ptr; 
        }
        if(means != nullptr){
            delete[] means;
        }
    }

    // Copy and move constructors
    Pca::Pca(const Pca& other){
        for(int i = 0; i < rows; ++i){
            this->data_array_ptr[i][0] = other.data_array_ptr[i][0];
            this->data_array_ptr[i][1] = other.data_array_ptr[i][1];
        }

    }
    Pca::Pca(Pca&& other):data_array_ptr(other.data_array_ptr){
        other.data_array_ptr = nullptr;
        means = nullptr;
    }

    // Copy and Move assignment operators
    Pca& Pca::operator=(const Pca& other){
        if(&other != this){
            Pca(other);
        }
        return *this;
    }
    Pca& Pca::operator=(Pca&& other){
        if(&other != this){
            Pca(other);
        }
        return *this;
    }
    // need to clear memory to prevent data leaks

    void Pca::init_array(){
        // create 64 by 2 array
        for(int i = 0; i < rows; ++i){
           data_array_ptr[i] = new double[columns]; 
        }
    }
    void Pca::readFromFile(string filename){
        ifstream file;
        string line;
        string value;

        file.open("./Data/"+ filename);
        
        int count = 0, row_pos = 0, col_pos = 0;
        getline(file, line); // skip heading
        if (file.is_open()){
            while( getline(file, line)) {
                col_pos = 0;
                istringstream iss(line);
                while(getline(iss, value, ';')){
                    count++;
                    istringstream iss(value);
                    iss >> data_array_ptr[row_pos][col_pos]; // populate 2D array
                    ++col_pos;
                }
                ++row_pos;
            }
            file.close();
        }
        else
            cout << "not opened" << endl;
    }

    // need to clear memory to prevent data leaks
    double* Pca::meanForEachDimension(){
        double ymean = 0, xmean = 0;
        int col_pos = 0;
        for(int i = 0; i < 64; ++i){
            xmean += data_array_ptr[i][col_pos];
            ymean += data_array_ptr[i][col_pos + 1];
        }
        xmean /= 64;
        ymean /= 64;
        means[0] = xmean;
        means[1] = ymean;

        return means;
    }

    // subtract the mean from each data point
    double** Pca::subtractMean(){
        double* means = meanForEachDimension();
        int col_pos = 0;
        for(int i = 0; i < 64; ++i){
            data_array_ptr[i][col_pos] -= means[0];     // x dimension
            data_array_ptr[i][col_pos + 1] -= means[1]; // y dimension
        }
        return data_array_ptr;
    }

    // create a matrix
    mat Pca::createMatrix(int dimension){
        mat matrix(64, 1); // 64 rows, 1 column

        for(int i = 0; i < 64; ++i){
            matrix(i, 0) = data_array_ptr[i][dimension];
            //matrix(i, 1) = data_ptr[i][1];    
        }

        // deallocate memory
        
        return matrix;
    }
}