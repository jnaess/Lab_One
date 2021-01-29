#include "LSA.h"

//LSA::LSA(){}

LSA::LSA()
{

}

void LSA::copyEpoch2LSA(Epoch epoch)
{

    N_sat = epoch.Satelites;

    l_o.resize(epoch.meas.size(), 1);
    //cout << "\n observation vector \n";
    for(int i = 0; i<l_o.rows(); ++i)
    {
        l_o(i,0) = epoch.meas[i].obs;
        //cout<<l_o(i,0)<<"\n";
    }

    x_o.resize(4,1);
    for(int i = 0; i<x_o.rows(); ++i)
    {
        x_o(i,0) = 0;
    }

    satpos.resize(epoch.Satelites, 3);
    for(int i = 0; i<satpos.rows(); ++i)
    {
        satpos(i,0) = epoch.meas[i].X;
        satpos(i,1) = epoch.meas[i].Y;
        satpos(i,2) = epoch.meas[i].Z;
    }

}


void LSA::adjustment()
{
    N_iter++;
	cout << "~~~~~~~~ ITERATION #" << N_iter << " ~~~~~~~~~~\n";

    //read observations, etc
    //populate x_o, l_o,


	this->designA();
	this->misclosure();
	this->weights();

   // N.resize(A.cols(), A.cols());
//    U.resize(A.cols(), w.cols());
//    delta.resize(N.cols(), U.cols());
//    v.resize(A.rows(), delta.cols());
//    x_cap.resize(x_o.rows(), x_o.cols());
//    l_cap.resize(l_o.rows(), l_o.cols());


	N = A.transpose() * P * A;
	U = A.transpose() * P * w;
	delta = -1*N.inverse() * U;
	v = A * delta + w;

	x_cap = x_o + delta;
	l_cap = l_o + v;

//    print_mat(satpos, "satpos");
//    print_mat(A, "A");
//    print_mat(w, "w");
//    print_mat(P, "P");
//	print_mat(delta, "delta");
//	print_mat(x_cap, "x_cap");
//	print_mat(l_cap, "l_cap");
//	print_mat(v, "v");

    for (int i = 0; i < delta.rows(); ++i)
    {
        if (this->delta(i, 0) > 0.00001 || this->delta(i, 0) < -0.00001)
        {
            l_o = l_cap;
            x_o = x_cap;
            adjustment();
        }
    }
}

void LSA::designA()
{
    A.resize(N_sat, 4);
    for(int i = 0; i<A.rows(); ++i)
    {
        double p_o = sqrt(pow(satpos(i,0)-x_o(0,0),2) + pow(satpos(i,1)-x_o(1,0),2) + pow(satpos(i,2)-x_o(2,0),2));
        for(int j=0; j<A.cols()-1; ++j)
        {
            A(i,j) = (x_o(j,0)-satpos(i,j))/p_o;
        }
        A(i,A.cols()-1) = -1;
    }
}

void LSA::misclosure()
{
    w.resize(N_sat, 1);
    for(int i = 0; i<w.rows(); ++i)
    {
        double p_o = sqrt(pow(satpos(i,0)-x_o(0,0),2) + pow(satpos(i,1)-x_o(1,0),2) + pow(satpos(i,2)-x_o(2,0),2));
        w(i,0) = p_o-l_o(i,0) -x_o(3,0);
    }
}

void LSA::weights()
{
    C_l.resize(N_sat, N_sat);
    C_l.setIdentity();

    P = apriori*C_l.inverse();
}

void LSA::precision()
{
    Qx = (A.transpose()*P*A).inverse();
    //Cx = apriori*Qx;
    GDOP = sqrt(Qx(0,0)+Qx(1,1)+Qx(2,2)+Qx(3,3));
    PDOP = sqrt(Qx(0,0)+Qx(1,1)+Qx(2,2));

    R.resize(4,4);
    //Need lat and lon to calculate rotation matrix

    //HDOP =
    //VDOP =
}

void LSA::output_x(string name)
{
    ofstream outfile;
    outfile.open(name, ios::app);   //will continue to append each time you run. Clear file or create new
    if (outfile.fail())
    {
        cout << "could not open output file";
    }
    outfile << fixed << setprecision(3) << x_cap(0,0) << " " << x_cap(1,0) << " " << x_cap(2,0) << " \n";
}


void print_mat(MatrixXd mat, string name)
{
    cout << "\n" << name << "\n";
    for(int i = 0; i<mat.rows(); ++i)
    {
        for(int j = 0; j<mat.cols(); ++j)
        {
            cout << mat(i,j) << "  ";
        }
        cout << "\n";
    }
}

