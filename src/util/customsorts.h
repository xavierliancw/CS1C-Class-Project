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
class CustomSorts
{
public:
    /**
     * @brief Selection sort algorithm
     * @param sortThese - Vector of data to be sorted
     * @param comparatorWhereFirstComesBeforeSecondPrm - Custom comparator lambda.
     *
     */
    template<typename X>
    void insertionSort(vector<X> &sortThese,
                              function<bool(X, X)> comparatorWhereFirstComesBeforeSecondPrm);

    /**
     * @brief Constructor.
     */
    CustomSorts();
};

#endif // CUSTOMSORTS_H


CustomSorts::CustomSorts()
{}

template<typename X>
void CustomSorts::insertionSort(vector<X> &sortThese,
                                function<bool(X, X)> comparatorWhereFirstComesBeforeSecondPrm)
{
    //There's gotta be something to sort
    if (sortThese.size() < 1) {return;}

    X holder;  //Holds onto an element being moved
    int cursor = 0;  //Cursor for element that's going to be shifted
    int shifter = 0; //Shifts elements until the correct spot for holder is found
    int finder = 0;  //Finds place to insert into

    //Loop until sorted
    while (cursor < sortThese.size())
    {
        //Pick up the cursor element
        holder = sortThese[cursor];

        //Look for spot to insert into
        finder = cursor - 1;
        while (finder > -1 && comparatorWhereFirstComesBeforeSecondPrm(holder, sortThese[finder]))
        {
            --finder;
        }
        //Now that a spot has been found, shift everything over to make room for the cursor element
        shifter = cursor - 1;
        while (shifter > finder)
        {
            sortThese[shifter + 1] = sortThese[shifter];
            --shifter;
        }
        //Insert into the found spot
        sortThese[finder + 1] = holder;

        //Advance for next loop
        ++cursor;
    }
}
