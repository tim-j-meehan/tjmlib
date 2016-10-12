#include<iostream>
#include<iomanip>
#include<cmath>
#include<vector>

//! Simple class for storing x,y pair
template <typename T>
class Point
{ 
    public:
    T x;
    T y;
    Point()
    {}
    Point(T x, T y)
        :x(x), y(y)
    {}
    T dot(const Point<T>& p0) const
    {
        return p0.x*x + p0.y*y;
    }
};    

//! Euclidean distance between two points
template<typename T>
T dist(const Point<T>& p0, const Point<T>& p1){
    Point<T> tmp = p0 - p1;
    return sqrt(tmp.x*tmp.x + tmp.y*tmp.y); 
}

template <typename T>
std::ostream& operator <<(std::ostream& os, const Point<T>& p0)
{
    return os << "x " << p0.x << " y "<< p0.y;
}

template <typename T>
Point<T>  operator +(const Point<T>& p0 , const Point<T>& p1)
{
    return Point<T>(p0.x + p1.x,p0.y+p1.y);
}

template <typename T>
Point<T>  operator -(const Point<T>& p0 , const Point<T>& p1)
{
    return Point<T>(p0.x - p1.x,p0.y-p1.y);
}

