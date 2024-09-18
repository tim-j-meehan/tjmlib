#include<iostream>
#include<iomanip>
#include<cmath>
#include<vector>
#include<compgeom.hh>

#ifndef _ARC_
#define _ARC_

//! find center of circle and radius given 3 points on circle
/*!
 * \parm vin input vector 3 points
 * \return returns type T len
 */
template <typename T> 
Circle<T > find_circle(Point<T>  & A,
              Point<T>  & B,
              Point<T>  & C){
    Line<T> lab = Segment<float>(A,B).perp_bisect();
    Line<T> lbc = Segment<float>(B,C).perp_bisect();
    std::shared_ptr<Point<T> > center = lab.crosses(lbc);
    if (center == NULL){
        return Circle<T>();
    }
    T radius = dist(*center,A);
    return Circle<T>(*center,radius); 
}

#endif
