#include<iostream>
#include<iomanip>
#include<cmath>
#include<vector>
#include<limits>
#include<sstream>

#ifndef _CIRCLE_
#define _CICCLE_
//! Simple class for storing Point and radius
template <typename T>
class Circle
{ 
    public:
    Point<T> ctr;
    T radius;
    Circle()
    {}
    Circle<T>(Point<T> ctr, T r)
        :ctr(ctr), radius(r)
    {}
    bool onCircle(Point<T> pt){
        return (std::abs(dist(pt,ctr) - radius) < std::numeric_limits<T>::epsilon());
    }
    std::pair<Point<T>, Point<T> > intersection(Circle<T> circ){
        Point<T> ctrPt = (ctr - circ.ctr) / (T) 2.0 + circ.ctr;
        T R = dist(ctr,circ.ctr);
        T R2 = R * R;
        T R4 = R2 * R2;
        T r12 = radius * radius;
        T r22 = circ.radius * circ.radius;
        Point<T> last = ((T) (0.5 * sqrt(2* (r12 + r22)/R2 - ((r12-r22) * (r12-r22)) / R4 -1))) * Point<T>(circ.ctr.y - ctr.y,ctr.x - circ.ctr.x);
        Point<T> pt1 = ctrPt + (r12 - r22)/(2*R2) * (circ.ctr - ctr) + last;
        Point<T> pt2 = ctrPt + (r12 - r22)/(2*R2) * (circ.ctr - ctr) - last;
        return (std::make_pair(pt1,pt2));
    }
    std::string svg(const std::string & color="#ff0000"){
        std::ostringstream retstr; 
        retstr << 
                  "<circle fill = 'none' stroke=\"" << color << "\" stroke-width='1'"
                         " cx =\"" << ctr.x << "\"" <<
                         " cy =\"" << ctr.y << "\"" <<
                         " r  =\"" << radius << "\"/>";
        return retstr.str();
    }
    std::string svg(Point<T> p1, Point<T> p2, const std::string & color="#ff0000"){
        std::ostringstream retstr; 
        // determin arc sweep
        Point<T>  p1mc = p1 - ctr;
        Point<T>  p2mc = p2 - ctr;
        double ang1 = atan2(p1mc.y,p1mc.x); 
        double ang2 = atan2(p2mc.y,p2mc.x); 
        int sweep = ang1-ang2>0?1:0;
        retstr << 
                  "<path d=\"M " << p1.x << " " << p1.y << " " <<
                  "A " << radius << " " << radius << " 0 1  " << sweep << " " << 
                  p2.x << " " << p2.y << "\" " << 
                         "fill = 'none' stroke=\"" << color << "\" stroke-width='4'" << 
                         //"stroke-dasharray='5,5'" <<
                          "\"/>";
        return retstr.str();
    }
};    

#endif
