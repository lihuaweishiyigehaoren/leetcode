#include <iostream>
#include <assert.h>
using namespace std;

template<class type, int dim>
class Point
{
public:
    Point(){};
    Point(type coords[dim])
    {
        for(int index = 0; index<dim;index++)
        {
            _coords[index] = coords[index];
        }
    }

    type& operator[] (int index)
    {
        assert(index < dim && index >= 0);
        return _coords[index];
    }

    type operator[] (int index) const
    {
        assert(index < dim && index>= 0);
        return _coords[index];
    }

private:
    type _coords[dim];
};

inline
template <class type, int dim>
ostream&
operator << (ostream &os, const Point<type,dim> &pt)
{
    os<<"(";
    for(int ix = 0 ; ix<dim-1;ix++)
    {
        os<<pt[ix]<<", ";
    }
    os<<pt[dim-1];
    os<<")";
    return os;
}

int main()
{
    int vals[3] = {1,2,3};
    Point<int, 3> point(vals);

    // cout << point << endl;
    return 0;
}