#include "negdry.h"



// **************static *********************
int Negdry::numFrameNIRS = 0; // 690+830 -> ch ->2
int Negdry::numFrameEEG = 0;
Negdry* Negdry::m_neg = NULL;   // get access to static function
std::list<NEGMat> Negdry::buffer;
QDoubleBufferedQueue<vector<double>>* Negdry::buffer1;
std::list<int> Negdry::debug_Buffer;
ofstream Negdry::outfile;
bool Negdry::isSaveData;
