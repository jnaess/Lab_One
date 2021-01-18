// test edit
//Summary:
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

#include "LSA.h"
#include "rinex.h"
#include "NRinexUtils.h"
#include <vector>

using namespace std;
using namespace NGSrinex;



int main( int argc, char* argv[] )
{
   // input file names
   string obsFilename;
   string satFilename;

   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   // START: Get necessary input

   // prompt for obs file name
   cout << "Please enter the name of the RINEX observation file: ";
   getline( cin, obsFilename );

   // prompt for file with satellite positions
   cout << "Please enter the name of the file containing the satellite positions: ";
   getline( cin, satFilename );


   // END: Get necessary input
   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   // START: Open the file containing the satellite positions



//==>>  TO BE COMPLETED



   // END: Open the file containing the satellite positions
   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   // START: Open an output file for the solution



//==>>  TO BE COMPLETED



   // END: Open an output file for the solution
   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   // START: Open the RINEX observation file


   // input RINEX file
   RinexObsFile inObsFile;
   if( !NRinexUtils::OpenRinexObservationFileForInput( inObsFile, obsFilename ) )
   {
      cout << "Could not open input observation file \"" << obsFilename << "\"...quitting." << endl;
      return 0;
   }




   // END: Open the input and output RINEX observation files
   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   // START: Main processing loop



   // end of program
   return 0;
}
