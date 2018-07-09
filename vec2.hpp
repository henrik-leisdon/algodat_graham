#ifndef VEC2_HPP
#define VEC2_HPP

struct Vec2
{
    int x;
    int y;
    float angle;

    Vec2():
       x{0},
       y{0},
       angle{0.0f}
       {}; 

    Vec2(int x, int y):
        x{x},
        y{y},
        angle{0}
        {};

    
    Vec2(int x, int y, float angle):
        x{x},
        y{y},
        angle{angle}
        {};
};

/*std::ostream operator<< (std::ostream& stream, const Vec2& point)
{
   stream << point.x <<" " << point.y <<"; ";
}
*/
#endif