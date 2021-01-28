#pragma once

#include "Measurement.h"
#include "rinex.h"
#include "NRinexUtils.h"
#include "Epoch.h"
#include "LSA.h"

using namespace std;
using namespace NGSrinex;
using namespace NRinexUtils;

#include <vector>
#include <cmath>
#include <Eigen/Dense>
#include <iomanip>

using namespace Eigen;

class LSA {
    friend class Epoch;
    public:
    //Constructor
    LSA();


    int N_sat;          //number of satellites/number of observations
    int N_iter=0;       //number of iterations

    MatrixXd l_o;       //pseudorange observations
    MatrixXd x_o;       //initial estimate. Parameters x, y, z, t
    MatrixXd satpos;    //x y z coordinates of satellites
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

    void copyEpoch2LSA(Epoch epoch);

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

    void print_mat(MatrixXd mat);

