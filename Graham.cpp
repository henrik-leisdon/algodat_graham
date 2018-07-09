//Algodat Task 5 - Graham Scan

//Henrik Leisdon Mt-Nr. 118334

#include "vec2.hpp"
#include <math.h>
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>


int smallest_y(std::vector<Vec2> points)  //method to get the lowest point/anchor point
{
    int min_ind;        //index of the lowest point of the vetor
    int min_val = 50;   //value of the lowest point

    for(int i=0;i<points.size();i++) //iterate through vector to find the lowest point 
    {
        if(min_val>points[i].y) //if the value of the current point is smaller than the overall lowest point before 
        {
            min_val = points[i].y; //the current point is the new lowest point.
            min_ind = i;
        }
    }
    return min_ind;     
} 

float checkAngle(Vec2 p1, Vec2 p2_mid, Vec2 p3)     //checks angle betweet three points
                                                    //while the second point is the point in the middle
{
    int x1 =p1.x-p2_mid.x;
    int x2 =p3.x-p2_mid.x;
    int y1 =p1.y-p2_mid.y;
    int y2 =p3.y-p2_mid.y;
    
    Vec2 v1{x1,y1};         //get the vector between point 1 and point two
    Vec2 v2{x2,y2};         //get vector between point two and three

    float sc = acos((v1.x*v2.x+v1.y*v2.y)/(sqrt(v1.x*v1.x+v1.y*v1.y)*sqrt(v2.x*v2.x+v2.y*v2.y)));  //get angle between the two vectors
    
    float angle_deg = sc*180.0/M_PI; //convert the angle from radian to degrees    
    
    return angle_deg ;
    
}

std::vector<Vec2> closed_path(std::vector<Vec2> path) //generate the closed path
{
    int min = smallest_y(path); //get lowest point
    int h_y=path[min].y; //horizon y
    int a_x=path[min].x;  //anchor x
    int a_y=path[min].y;  //anchor y
    Vec2 horizon{50,h_y}; //generate the horizon point, to get the angles of all points to the horizon
    Vec2 anchor{a_x,a_y}; //anchor point/lowest point
   
    for(int i = 0; i<path.size();i++)   
    {
        if(path[i].x == anchor.x && path[i].y == anchor.y) //while iterating through the vector, the anchor point has the angle 0
        {
           path[i].angle=0.0f; 
          
        }
        else
        {
            float a=checkAngle(horizon,anchor,path[i]); //get angle between point i, anchor and horizon
            path[i].angle= a;
        
        }
        
    }
    for (int i = 0; i < path.size() ; i++)  //sort vector by angle
    {
      for (int j = 0; j < path.size()-1; j++)
      {
          if (path[j].angle > path[j+1].angle) 
          {
            
            std::swap(path[j],path[j+1]);

              
         }
      }
   }
   return path; //finished closed path


}

std::vector<Vec2> graham_scan(std::vector<Vec2> points)
{
    int i=0;
    int p = points.size();
    Vec2 anchor = points[0];  //anchor point = first point of closed path
    while(i<p-2)
    {
        Vec2 p1 = anchor;      
        Vec2 p2 = points[i];   //sequence of 3 sucessive points
        Vec2 p3 = points[i+1]; //
        Vec2 p4 = points[i+2];

/*
Idea: a rectangle has 360°
The method checkAngle checks the smallest angle between 3 points. 
You can take 3 sucessive points and the anchor to get a rectangle. If the sum of all 4 angles is 360° the point
p3 belongs to the convex hull. if the sum is smaller than 360°, then point p3 doesnt belong to the convex hull.
because of the fact, that the p3 has an angle >180° and checkAngle takes the outer angle - the one <180°.
So the sum of all angles is smaller than 360° and p3 doesn't belong to the convex hull
*/

        float alpha=checkAngle(p4,p1,p2);  
        float beta=checkAngle(p1,p2,p3);
        float gamma = checkAngle(p2,p3,p4);
        float delta = checkAngle(p3,p4,anchor);

        if(alpha+beta+gamma+delta<360.1f )                        //if the sum of all angles < 360°
        {                                                         
                        points.erase(points.begin()+i+1);                     //erase p3 from vector
        }
        ++i;

    
    }
    return points;
}


int main(int argc, char const *argv[])
{


    //input:
    std::cout << "how may points should be generated? \n";
    int pointCount;
    std::cin >> pointCount;

    if(pointCount<4)
    {
        std::cout << "path is too small";
    }
    else
    {
        std::vector<Vec2> v_points;         
        for(int i = 0; i<pointCount;i++)        //generate n random points
            {
            int x{rand()%50};
            int y{rand()%51};

            Vec2 rdm_point{x,y};
            v_points.push_back(rdm_point);  //push them into a vector
        }


    //test methods

        int min = smallest_y(v_points);
        
        std::cout <<"\n raw array: \n"; //output of all random points
        for(int i=0;i<v_points.size();i++)
        {
            std::cout << v_points[i].x <<", " << v_points[i].y << " ;  ";  
        } 
        std::cout << "\n";
        std::cout <<"min: "<< min+1 << "-> " <<  v_points[min].x << " , " <<v_points[min].y <<"\n";  //output anchor point
        
        std::vector<Vec2> points2 = closed_path(v_points);
        std::vector<Vec2> points3 = graham_scan(points2);

        
        std::cout <<"\n convex hull array: \n";  //output convex hull vector
        
        for(int i=0;i<points3.size();i++)
        {
            std::cout << points3[i].x <<", " << points3[i].y  << " ;  \n";      
        } 


        return 0;
        }

    
}

