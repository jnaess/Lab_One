#pragma once

#include <cmath>
#include <Eigen/Dense>
#include <iomanip>
#include <string>
#include <iostream>

using namespace Eigen;
using namespace std;

class LSA {
	public:

    int N_sat;          //number of satellites/number of observations
    int N_iter=0;       //number of iterations

    MatrixXd l_o;       //pseudorange observations
    MatrixXd x_o;       //initial estimate. Parameters x, y, z, t
    MatrixXd C_l;       //variance matrix of observations
    MatrixXd P;         //weight matrix
    double apriori=1;   //apriori variance factor
    MatrixXd N;         //normal equations matrix
    MatrixXd U;         //intermediate calculation
    MatrixXd x_cap;     //corrected parameters
    MatrixXd l_cap;     //corrected observations
    MatrixXd delta;     //correction vector
    MatrixXd A;         //design matrix
    MatrixXd w;         //misclosure vector
    MatrixXd C_xcap;    //variance covariance of estimate
    MatrixXd v;         //residuals

    /*Function: adjustment
    Runs an iterative least squares adjustment
    Inputs: None
    Outputs: None
    */
    void adjustment();

    /*Function: designA
    Populates design matrix, A
    Inputs: None
    Outputs: None
    */
    void designA();

    /*Function: misclosure
    Populates misclosure vector
    Inputs: None
    Outputs: None
    */
    void misclosure();

    /*Function: weights
    Populates variance matrix of observations and weight matrix
    Assumes uniform variances for all observations
    Inputs: None
    Outputs: None
    */
    void weights();
};
