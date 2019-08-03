
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <armadillo>
#include "pca.h"

namespace SBSSON002 {
    using namespace std;
    using namespace arma;
    // need to clear memory to prevent data leaks
    double** readFromFile(string filename){
        ifstream file;
        string line;
        string value;

        int rows = 64, columns = 2;
        double** data_array_ptr = new double*[rows]; // 64 rows
        file.open("./Data/"+ filename);
        
        // create 64 by 2 array
        for(int i = 0; i < rows; ++i){
           data_array_ptr[i] = new double[columns]; 
        }
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
        return data_array_ptr;
    }

    // need to clear memory to prevent data leaks
    double* meanForEachDimension(double** data_ptr){
        double ymean = 0, xmean = 0;
        double* means = new double[2];
        int col_pos = 0;
        for(int i = 0; i < 64; ++i){
            xmean += data_ptr[i][col_pos];
            ymean += data_ptr[i][col_pos + 1];
        }
        xmean /= 64;
        ymean /= 64;
        means[0] = xmean;
        means[1] = ymean;

        return means;
    }

    // subtract the mean from each data point
    double** subtractMean(double** data_ptr){
        double* means = meanForEachDimension(data_ptr);
        int col_pos = 0;
        for(int i = 0; i < 64; ++i){
            data_ptr[i][col_pos] -= means[0];     // x dimension
            data_ptr[i][col_pos + 1] -= means[1]; // y dimension
        }
        return data_ptr;
    }

    // create a matrix
    mat createMatrix(double** data_ptr, int dimension){
        mat matrix(64, 1); // 64 rows, 1 column

        for(int i = 0; i < 64; ++i){
            matrix(i, 0) = data_ptr[i][dimension];
            //matrix(i, 1) = data_ptr[i][1];    
        }
        return matrix;
    }
}