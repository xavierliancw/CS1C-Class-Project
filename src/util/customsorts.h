#ifndef CUSTOMSORTS_H
#define CUSTOMSORTS_H
#include <vector>
#include <functional>
using namespace std;

/**
 * @brief This class contains all developer-implemented sorting functions.
 * @par REQUIREMENTS:
 * #include <vector>       <br>
 * #include <functional>   <br>
 * using namespace std;
 */
template<typename Type>
class CustomSorts
{
public:

    /**
     * @brief Constructor
     *
     * @param cv: vector to be copied to member variable v_copyVector
     */
    CustomSorts(vector<Type> cv){v_copyVector = cv;}

    /**
     * @brief insertionSort algorithm
     *
     * @param comparatorWhereFirstComesBeforeSecondPrm: Custom comparator lambda
     */
    void insertionSort(function<bool(Type, Type)> comparatorWhereFirstComesBeforeSecondPrm);

    vector<Type> v_copyVector;

};

template<typename X>
void CustomSorts<X>::insertionSort(function<bool(X, X)> comparatorWhereFirstComesBeforeSecondPrm)
{
    //There's gotta be something to sort
    if (v_copyVector.size() < 1) {return;}

    X holder;  //Holds onto an element being moved
    int cursor = 0;  //Cursor for element that's going to be shifted
    int shifter = 0; //Shifts elements until the correct spot for holder is found
    int finder = 0;  //Finds place to insert into

    //Loop until sorted
    while (cursor < v_copyVector.size())
    {
        //Pick up the cursor element
        holder = v_copyVector[cursor];

        //Look for spot to insert into
        finder = cursor - 1;
        while (finder > -1 && comparatorWhereFirstComesBeforeSecondPrm(holder, v_copyVector[finder]))
        {
            --finder;
        }
        //Now that a spot has been found, shift everything over to make room for the cursor element
        shifter = cursor - 1;
        while (shifter > finder)
        {
            v_copyVector[shifter + 1] = v_copyVector[shifter];
            --shifter;
        }
        //Insert into the found spot
        v_copyVector[finder + 1] = holder;

        //Advance for next loop
        ++cursor;
    }
}

#endif // CUSTOMSORTS_H

