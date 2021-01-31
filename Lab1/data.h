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

class data {

	public:

    vector<Epoch> Epochs;

    double currEpoch;

    MatrixXd truepos;

    /*
    Definition:
        Default contructor, does nothing
    Input:

    Output:

    */
    data();


    /*
    Definition:
        Reads the satelite observation file
    Input:

    Output:

    */
    void readSatFile(string filename = "satpos.txt");

    /*
    Definition:
        Updated the current epoch and return the new counter
    Input:

    Output:

    */
    int newHeaderLine(string line);

    /*
    Definition:
        Reads the satelite observation file
    Input:

    Output:

    */
    void readObsFile(string obsFilename = "sample.18o");


    /*
    Definition:
        Adds a measurement to the an epoch's satelites measurement
    Input:
        satNum: of the satelite in the epoch
        epochCounter: of the epochs (assuming in same order as sat position)
        pseadorange: the measuremnt to add to that satelite in the epoch
    Output:

    */
    void epochSatMeas(int satNum, int epochCounter, double pseudorange);


    /*
    Definition:
        Reads the true position file
    Input:

    Output:

    */
    void readTruePosFile(string positionFilename = "true pos.txt");
};
