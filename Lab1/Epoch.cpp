#include "Epoch.h"

Epoch::Epoch(){
}

Epoch::Epoch(double Epoch, int satelites, int epochorder){
    epoch = Epoch;
    Satelites = satelites;
    epochOrder = epochorder;

}

void Epoch::AddMeasurement(string line){
    meas.emplace_back(line, epoch);
}

Measurement* Epoch::findSat(int satNum){
    for(int i=0; i < meas.size(); i++){
        if(meas[i].SatNum == satNum){
            //cout << "Satelite found" << endl;
            return &meas[i];
        }
    }
    //cout << "Could not find satelite" << endl;
}
