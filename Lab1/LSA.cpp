#include "LSA.h"

void LSA::adjustment()
{
    N_iter++;
	cout << "~~~~~~~~ ITERATION #" << N_iter << " ~~~~~~~~~~\n";

    //read observations, etc
    //populate x_o, l_o,
	this->designA();
	this->misclosure();
	this->weights();

	N = A.transpose() * P * A;
	U = A.transpose() * P * w;
	delta = -1 * N.inverse() * U;
	v = A * delta + w;

	x_cap = x_o + delta;
	l_cap = l_o + v;


	if (N_iter < 5)
	{
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
}

void LSA::designA()
{
    A.resize(N_sat, 4);
    for(int i = 0; i<A.rows(); ++i)
    {
        for(int j=0; j<A.cols()-1; ++j)
        {
            A(i,j) = 3; //TODO: wait for format of coordinates, etc.
        }
        A(i,A.cols()) = -1;
    }
}

void LSA::misclosure()
{
    w.resize(N_sat, 1);
    for(int i = 0; i<w.rows(); ++i)
    {
        w(i,0) = 6; //TODO: wait for format of coordinates, etc.
    }
}

void LSA::weights()
{
    C_l.Identity(N_sat, N_sat);
    P = apriori*C_l.inverse();
}
