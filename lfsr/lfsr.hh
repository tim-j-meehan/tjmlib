#include <vector>
template<typename T>

std::vector<int> lfsr(T init, int len, T poly){
    static_assert(std::is_integral<T>::value,"type not integral");
    std::vector<int> ret(len);
    T lfsr = init;
    for(int ii=0;ii<len;ii++){
        int bit = lfsr & 1;
        lfsr = (lfsr >> 1);
        if (bit){
            lfsr = lfsr ^ poly;
        }
        ret[ii] = bit; 
    }
    return(ret);
}
