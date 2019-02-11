#include<iostream>
#include<iomanip>
#include<cmath>
#include<vector>
#include<compgeom.hh>

#ifndef _LINE_
#define _LINE_
const double d2r= M_PI/180.0;

//! Simple class to store a line
/*! 
 * Equation for line in form
 *  Ax + By = C
 */
template <typename T>
class Line
{
    public:
    T AA;
    T BB;
    T CC;
    Line()
    {}
    Line(const Point<T>& p0,const Point<T>& p1)
    {
        AA=p1.y - p0.y;     
        BB=p0.x - p1.x;
        CC=AA*p0.x+BB*p0.y;
    }
    Line(T AA,T BB, T CC): AA(AA),BB(BB),CC(CC)
    {}
   
    T Y(T x){
        return (CC - AA*x)  / BB;
    }

/*! 
 *  calculate crossing as
 *[A0  B0  [x = C1
 * A1  B1]  y] = C2
 * solve for  x and y
 * \param l1 line to find crossing
 * \return shared pointer to point of crossing or NULL of no cross
 */
    std::shared_ptr<Point<T> > crosses(const Line<T>& l1) const
    { 
        T det = AA * l1.BB - l1.AA * BB;
        std::shared_ptr<Point<T> > p0{new Point<T>};
        if (det == 0){
//            std::cout << "lines par \n";
            return NULL;
        }else{
            p0->x = (l1.BB * CC - BB * l1.CC)/det;
            p0->y = (AA*l1.CC - l1.AA*CC)/det;
        }
    return p0;
    }
    //! return a line perpendicular to this line at point
    Line<T> perpLine(const Point<T> p0)
    {
        T tAA = -BB;
        T tBB = AA;
        T tCC = tAA*p0.x + tBB*p0.y;
        return Line<T>(tAA,tBB,tCC);
    }
    //! rotate line around  point
    Line<T> rotLine(const Point<T> p0, T angle)
    {
        T tAA = AA * cos(d2r*angle) -BB * sin(d2r*angle);
        T tBB = AA * sin(d2r*angle) +BB * cos(d2r*angle);;
        T tCC = tAA*p0.x + tBB*p0.y;
        return Line<T>(tAA,tBB,tCC);
    }
/*! 
 *given a src/bounce point
 *find parallel surface to segment
 *find line perp to segment and at intersection
 *find point on parallel line reflected about perp line
 *\param bouncePoint point on this line to bounce the ray
 *\param srcPoint source of the ray
 *\return reflected line
 */
    Line<T> reflect(const Point<T> bouncePoint, const Point<T> srcPoint )
    {
        Line<T> parLine(*this);
        parLine.CC = parLine.AA*srcPoint.x + parLine.BB*srcPoint.y;
        std::shared_ptr<Point<T> > centerPoint = perpLine(bouncePoint).crosses(parLine);       
        Point<T> dstPoint = *centerPoint - (srcPoint - *centerPoint);
        
        return Line<T>(bouncePoint,dstPoint);
    }

};

template <typename T>
std::ostream& operator <<(std::ostream& os, const Line <T>& l0)
{
    return os << "A " << l0.AA << " B "<< l0.BB << " C " << l0.CC;
}

template <typename T>
class Segment
{
    public:
    Point<T> p0;
    Point<T> p1;
    Line<T> line;
    Segment()
        {}
    Segment(Point<T> p0,Point<T> p1)
        :p0(p0), p1(p1)
    {
        line = Line<T>(p0,p1);
    }
    std::shared_ptr<Point<T> > crosses(const Segment<T> & s1) const
    {
        std::shared_ptr<Point<T> > pc = Line<T>(p0,p1).crosses(Line<T>(s1.p0,s1.p1));
        if (pc == NULL){
            return NULL;
        }
        std::cout << "ERROR  not sure conditional below works \n";
        if ((std::min(p0.x, p1.x) <= pc->x <= std::max(p0.x,p1.x)) &&
            (std::min(p0.y, p1.y) <= pc->y <= std::max(p0.y,p1.y))){
            return pc;
        }else{
            return NULL;
        }
    }
    std::shared_ptr<Point<T> > crosses(const Line<T> & l1) const
    {
        std::shared_ptr<Point<T> > pc = Line<T>(p0,p1).crosses(l1);
        if (pc == NULL){
            return NULL;
        }
        if ((std::min(p0.x, p1.x) <= pc->x) &&
            (pc->x  <= std::max(p0.x,p1.x)) &&
            (std::min(p0.y, p1.y) <= pc->y) &&
            (pc->y <= std::max(p0.y,p1.y))){
            return pc;
        }else{
            return NULL;
        }
    }
    T dot(const Segment<T> & s1) const
    {
        return (p1 - p0).dot(s1.p1 - s1.p0);
    }
    //! return a perpendicular bisector to this segment 
    Line<T> perp_bisect(){
    	return line.perpLine((p1-p0)/(T) 2.0+p0);
    }
};

template <typename T>
std::ostream& operator <<(std::ostream& os, const Segment <T>& s0)
{
    return os << "p0 " << s0.p0 << " p1 "<< s0.p1;
}
#endif    
