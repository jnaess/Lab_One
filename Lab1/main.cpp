// Jan Erik Naess and Claire Mah
// Summary:
//    Skeleton program to open a RINEX observation file and scroll through all
//    of the epochs.  Students in ENGO 465 will use this to develop code to compute
//    a least-squares solution using data from a standalone GPS receiver.
//
// History:
//    Jan 16/13 - Created by Mark Petovello
//
// Copyright:
//    Position, Location And Navigation (PLAN) Group
//    Department of Geomatics Engineering
//    Schulich School of Engineering
//    University of Calgary
//
// Disclaimer:
//    This source code is not freeware nor shareware and is only provided under
//    an agreement between authorized users/licensees and the University of
//    Calgary (Position, Location And Navigation (PLAN) Group, Geomatics
//    Engineering, Schulich School of Engineering) and may only be used under
//    the terms and conditions set forth therein.

#include <iostream>
#include <fstream>
#include <sstream>

#include "rinex.h"
#include "NRinexUtils.h"
#include "LSA.h"
#include "data.h"
#include "Measurement.h"
#include "Epoch.h"


using namespace std;
using namespace NGSrinex;
using namespace NRinexUtils;



int main( int argc, char* argv[] )
{
    //test that a measurement is properly added
    /*string line = "5 -22032612.69069 4715954.08976 14056228.45825 9125.04961";
    Measurement meas = Measurement(line, -1.0);
    meas.Output();*/

    data obj = data();
    cout << "Epochs: " << obj.Epochs.size() << endl;
    return 0;
}
