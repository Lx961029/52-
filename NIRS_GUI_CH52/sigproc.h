#ifndef SIGPROC_H
#define SIGPROC_H

#include "math.h"





static const double invex_data[4]={
 -1.8403,    5.0663,
  2.3844,   -0.9828
};

static const double pdf[4] = {
    616, 0,
    0, 584
};



double singleCvt(double* raw690,double* raw830,double baseline1,double baseline2);


#endif // SIGPROC_H
