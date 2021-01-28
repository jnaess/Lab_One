#pragma once

#include "Measurement.h"
#include "rinex.h"
#include "NRinexUtils.h"

using namespace std;
using namespace NGSrinex;
using namespace NRinexUtils;

#include <vector>
#include <cmath>
#include <Eigen/Dense>
#include <iomanip>

using namespace Eigen;

class Epoch {
    friend class LSA;

    vector<Measurement> meas;

    double epoch;

    //the nth epoch
    int epochOrder;

    //number of satelites in this epoch
    int Satelites;

	public:

    /*
    Definition:
        Default contructor, does nothing
    Input:

    Output:

    */
    Epoch();

    /*
    Definition:
        Sets up the Epoch,
        satelites measurements still need to be added
    Input:
        epoch: the epoch for this one
        satelites: the number of satelite measurements in this epoch
    Output:

    */
    Epoch(double Epoch, int satelites, int epochorder);

    /*
    Definition:
        Adds a satelites measurement to the vector of measurements
        inside this epoch
    Input:
        The classic satpos.txt line
    Output:

    */
    void AddMeasurement(string line);

    /*
    Definition:
        Finds the satelite within the epoch and return its address
    Input:
        The number of the satelite that you are looking for
    Output:
        Address of the measurement
    */
    Measurement* findSat(int satNum);
};
