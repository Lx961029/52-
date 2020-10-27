#include "sigproc.h"
#include "math.h"
#include "QDebug"




double singleCvt(double* raw690,double* raw830,double baseline1,double baseline2){

     double HbT,HbR,HbO,PATH = 3*pdf[0];// cm
     *raw690 = -log10(*raw690/baseline1)*1e4;
     *raw830 = -log10(*raw830/baseline2)*1e4;
     *raw690 = (*raw690)/PATH;  // = 自右向左
     *raw830 = (*raw830)/PATH;
     HbO =  *raw690;
     HbR =  *raw830;
     *raw690 = invex_data[0]*HbO + invex_data[1]*HbR;
     *raw830 = invex_data[2]*HbO + invex_data[3]*HbR;

     HbT = *raw690 + *raw830;

     return HbT;
 }
