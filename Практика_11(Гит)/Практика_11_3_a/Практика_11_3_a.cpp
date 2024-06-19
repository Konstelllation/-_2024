#include <cassert>
#include <numeric> // для std::midpoint


int binarySearch(const int* array, int target, int min, int max)
{
    assert(array); 

    while (min <= max)
    {
        
        int midpoint{ std::midpoint (min, max) };
        

        if (array[midpoint] > target)
        {
            
            max = midpoint - 1;
        }
        else if (array[midpoint] < target)
        {
           
            min = midpoint + 1;
        }
        else
        {
            return midpoint;
        }
    }

    return -1;
}