#include "data.h"

#include <sstream>

//Test comment here
data::data(){
    // input file names
   string obsFilename = "data_v2.21o";
   string satFilename = "satpos.txt";


   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   // START: Get necessary input

   // prompt for obs file name
   //cout << "Please enter the name of the RINEX observation file: ";
   //getline( cin, obsFilename );

   // prompt for file with satellite positions
   //cout << "Please enter the name of the file containing the satellite positions: ";
   //getline( cin, satFilename );


   // END: Get necessary input
   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   // START: Open the file containing the satellite positions

    readSatFile(satFilename);



   // END: Open the file containing the satellite positions
   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   // START: Open an output file for the solution



//==>>  TO BE COMPLETED



   // END: Open an output file for the solution
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   // START: Open the RINEX observation fil
   readObsFile(obsFilename);
}

void data::readSatFile(string filename){
 ifstream file(filename);
 cout <<"readSatFile\n";

  if (file.is_open()) {
      string line;

      //to tell us when to switch between read in types
      //-1 to indicate first line
      int counter = 0;
      int epochCounter = -1;

      while (getline(file, line)) {
          //This means that we can use this line to input some sort of value
          if(counter == 0 || counter == -1){
            counter = newHeaderLine(line);

            //add to the epochcounter to follow along
            epochCounter = epochCounter + 1;

            //add a new epoch
            Epochs.emplace_back(currEpoch, counter, epochCounter);


          }
          else{
            //assign a new measurement to the epoch
            Epochs[epochCounter].AddMeasurement(line);

            //move counter down
            counter = counter - 1;
          }
        }
      }
      file.close();
}

int data::newHeaderLine(string line){
    //header type
    //assign new counter (number of satelites in this epoch
    string arr[2];
    int i = 0;

    stringstream ssin(line);
    while (ssin.good() && i < 2){
        ssin >> arr[i];
        ++i;
    }

    //update Epoch
    currEpoch = stold(arr[0]);

    //restart counter
    //cout << "returning counter " << stoi(arr[1]) << endl;
    return stoi(arr[1]);
}

void data::readObsFile(string obsFilename){
       //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   // START: Open the RINEX observation file
    cout << "readObsFile"<<"\n";

   // input RINEX file
   RinexObsFile inObsFile;
   if( !OpenRinexObservationFileForInput( inObsFile, obsFilename ) )
   {
      cout << "Could not open input observation file \"" << obsFilename << "\"...quitting." << endl;
      return;
   }


   // END: Open the input and output RINEX observation files
   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   // START: Main processing loop


   // current epoch's data from RINEX file
   ObsEpoch  currentRinexObs;

   // read the observation epochs
   try
   {
        int epochCounter = 0;
      // for all epochs in the RINEX file...
      while( inObsFile.readEpoch( currentRinexObs ) != 0 )
      {
         // get the observation time
         double obsTime = currentRinexObs.getEpochTime().GetGPSTime().secsOfWeek;

         // TO BE COMPLETED: Compute least-squares solution


         //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
         // NOTE: The following is sample code that you can use to better understand how the data
         //       is organized.   Feel free to use this as is (with modifications, obviously), or
         //       use it as a guideline for your own development.  The keys things to be aware of
         //       are:
         //       -> Only consider GPS satellites (satCode == 'G')
         //       -> Only consider pseudoranges on L1 (obsType == C1)
         //       -> Make sure that the observations are present (obsPresent == true)
         //
         //
         //   // for all satellites...
            for( unsigned short i = 0 ; i < currentRinexObs.getNumSat() ; ++i )
            {
               // get the satellite observations for the current satellite
               SatObsAtEpoch satObs = currentRinexObs.getSatListElement(i);

               // for this lab, only deal with GPS observations
               if( satObs.satCode != 'G' )
                  continue;

               // for all observations from the current satellite (MAXOBSTYPES is defined in rinex.h)...
               for( unsigned short j = 0 ; j < MAXOBSTYPES ; ++j )
               {
                  // for this lab, only deal with pseudorange measurements on L1 (denoted C1; defined in rinex.h)
                  if( satObs.obsList[j].obsType != C1 )
                     continue;

                  // make sure the observation is present
                  if( !satObs.obsList[j].obsPresent )
                     continue;

                  // get the observations
                  // this gives us the pseudorange measurement

                  double pseudorange = satObs.obsList[j].observation;
                //cout<< "satObs.satNum()" << satObs.satNum << endl;
                  epochSatMeas(satObs.satNum, epochCounter, pseudorange);

               }// for all observations at a given epoch...

            }// for all satellites...

         //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //Epoch epoch;

        LSA lsa = LSA();
        lsa.copyEpoch2LSA(this->Epochs[epochCounter]);
        lsa.adjustment();

         // TO BE COMPLETED: Output the result for the current epoch to file
        epochCounter = epochCounter + 1;
      }// for all epochs in the RINEX file...

   }
   catch( RinexReadingException &readingExcep )
   {
      cout << " RinexReadingException is: " << endl << readingExcep.getMessage() << endl;
   }


   // end of program
}

void data::epochSatMeas(int satNum, int epochCounter, double pseudorange){
    Epochs[epochCounter].findSat(satNum)->setObs(pseudorange);
}
