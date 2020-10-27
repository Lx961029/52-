#ifndef FILTER_IIR_H
#define FILTER_IIR_H

#include "Queue.hpp"

//fdatool coff


const int NL = 9;
const double NUM[9] = {
  0.0003528733058069,-0.0007531535975194, 0.001232070931843,-0.001139267491595,
   0.001249047782669,-0.001139267491595, 0.001232070931843,-0.0007531535975194,
  0.0003528733058069
};
const int DL = 9;
const double DEN[9] = {
                   1,   -5.747929582178,    14.70127570072,    -21.7968976217,
      20.45323012935,   -12.42091510983,    4.762008601865,   -1.052832820231,
     0.1026947960851
};


template<typename T>
class Filter_IIR
{
public:
    Filter_IIR();
    ~Filter_IIR();
    char filterData(T data,T* res);
private:
    unsigned int orders;
    Queue<T>* num;
    Queue<T>* den;

};

template<typename T>
Filter_IIR<T>::Filter_IIR(){
    orders = DL-1;  // 6阶！！！！！！
    num = new Queue<T>(DL);
    den = new Queue<T>(DL);
    for(int i = 0;i< orders; i ++){
        num->push(0);
        den->push(0);
    }
}

template<typename T>
Filter_IIR<T>::~Filter_IIR(){
    delete num;
    delete den;
}

template<typename T>
char Filter_IIR<T>::filterData(T data,T *res){
    unsigned int n = orders;
    T temp,temp_res;
    temp_res = data*NUM[0];
           while(n--){         //n-1 ~0
               num->at(n,temp);   // 新 -> 老
              temp_res += temp*NUM[DL-1-n];  // 此处已经减过1
               den->at(n,temp);
              temp_res -= temp*DEN[DL-1-n];
          }
    num->pop(temp);  //必须先pop
    den->pop(temp);
    num->push(data);
    den->push(temp_res);

    *res = temp_res;
    return 1;
}





#endif // FILTER_H
