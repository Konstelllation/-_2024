#include <cassert>
#include <numeric> // для std::midpoint


int binarySearch(const int* array, int target, int min, int max)
{
    assert(array); 

    

    if (min > max)
        return -1;

    int midpoint{ std::midpoint(min, max) };
    

    if (array[midpoint] > target)
    {
        return binarySearch(array, target, min, midpoint - 1);
    }
    else if (array[midpoint] < target)
    {
        return binarySearch(array, target, midpoint + 1, max);
    }
    else
    {
        return midpoint;
    }
}