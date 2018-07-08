#include<iostream>
#include<iomanip>
#include<cmath>
#include<vector>

template <typename T>
class Polygon
{
    public:
    std::vector<Point<T> > points;
    std::vector<Segment<T> > segments;
        
    Polygon(int len, int N){
    points.push_back(Point<T> (0.0,0.0));
    points.push_back(Point<T> (1.0,0.0)*len);
    for(int ii =2;ii<len;ii++)
        points.push_back(points[ii-1] + Point<T>(std::cos((ii-1)*d2r*360.0/N), std::sin((ii-1)*d2r*360.0/N)));

    for(int ii=0;ii<5;ii++)
        segments.push_back(Segment<T>(points[ii],points[(ii+1)%5]));

    }
                   
    
}


template <typename T>
std::ostream& operator <<(std::ostream& os, const Polygon <T>& p0)
{
    for (auto point in points)
        os << points << "\n ";
    return os;
}

template <typename T>
class Pentagon
{
    public:

        
        std::vector<Point<T> > points;
    
        std::vector<Segment<T> > segments;
        
        Segment<T> hole;
    
        Segment<T>* curSeg;
        std::shared_ptr<Point<T> > srcPoint;
        Line<T> ray;

        double bounceDist;
    
    Pentagon(T angle)
        
    {
        bounceDist=0;
        points.push_back(Point<T> (0.0,0.0));
        points.push_back(Point<T> (1.0,0.0));
        for(int ii =2;ii<5;ii++)
            points.push_back(points[ii-1] + Point<T>(std::cos((ii-1)*d2r*72.0), std::sin((ii-1)*d2r*72.0)));

        for(int ii=0;ii<5;ii++)
            segments.push_back(Segment<T>(points[ii],points[(ii+1)%5]));


        // define the hole based on segment 4 
        std::vector<T> uu(2); 
        uu.at(0) = segments[4].p1.x - segments[4].p0.x;
        uu.at(1) = segments[4].p1.y - segments[4].p0.y;
        norm2(uu);
        T hrad = 5.0/1000.0;
        hole = Segment<T>(segments[4].p0 + Point<T>(uu[0] * (.5-hrad),uu[1] * (.5-hrad)),
                          segments[4].p0 + Point<T>(uu[0] * (.5+hrad),uu[1] * (.5+hrad)));


        // define the starting ray
        Point<T> holeCenter = (hole.p1 - hole.p0)/2.0 + hole.p0;
        ray = segments[4].line.rotLine(holeCenter,90-angle);
        curSeg = &segments[4];
        std::shared_ptr<Point<T> > ptmp{new Point<T>};
        ptmp->x = holeCenter.x;
        ptmp->y = holeCenter.y;
        srcPoint = ptmp;
        

//        ray.AA = 1.2;
//        ray.BB = 1.1;
//        ray.CC = 1;
//        curSeg = &segments[3];
//        srcPoint = curSeg->crosses(ray);

    }
   
    //! check for crossing,
    //reflect from src point,ray to crossing segment 
    //update current segment, ray, srcPoint
    T bounce()
    {
        std::shared_ptr<Point<T> > bouncePoint = NULL;
        for(int segIdx = 0;segIdx < segments.size();segIdx ++){
            if (&segments[segIdx] == curSeg){
                continue;
            }
            bouncePoint = segments[segIdx].crosses(ray);
//            bouncePoint = ray.crosses(thisSeg);
            if (bouncePoint != NULL){
                if(PRINT_BOUNCE)
                    std::cout <<  *bouncePoint << std::endl;
                curSeg = &segments[segIdx];
                if (segIdx == 4){
                    //check to see if we made it out of the hole 
                    if (hole.crosses(ray) != NULL){
                        bounceDist += dist(*srcPoint,*bouncePoint);
                        return bounceDist;
                    }
                }   
                break;
            }
        }        
        if (bouncePoint == NULL){
            std::cout << " ERROR WE MISSED \n";
            std::cout << " RAY was " << ray << std::endl;
            std::cout << "source point was " << *srcPoint <<  std::endl; 
            std::cout << "x " << 1.3 << " y " << ray.Y(1.3) <<  std::endl; 
            return -999;
        }

        ray=curSeg->line.reflect(*bouncePoint, *srcPoint );
        bounceDist += dist(*srcPoint,*bouncePoint);
        srcPoint=bouncePoint;
        
        return -1;
    }
};

template <typename T>
std::ostream& operator <<(std::ostream& os, const Pentagon <T>& p0)
{
    return os << p0.points[0] << "\n "<<\
                 p0.points[1] << "\n "<<\
                 p0.points[2] << "\n "<<\
                 p0.points[3] << "\n "<<\
                 p0.points[4] << "\n "<<\
                 p0.points[0] << "\n ";
            
}

