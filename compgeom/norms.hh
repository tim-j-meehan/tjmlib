#include<iostream>
#include<iomanip>
#include<cmath>
#include<vector>

//! normalize a vector and return the it's len
/*!
 * \parm vin input vector is modified
 * \return returns type T len
 */
template <typename T> 
T norm2(std::vector<T> & vin){
    T sum2 = 0;
    for(auto val:vin){
        sum2 += val*val;
    }
    T ssum = sqrt(sum2);
    for(auto val:vin){
        val /= ssum;
    }
    return ssum;
}

