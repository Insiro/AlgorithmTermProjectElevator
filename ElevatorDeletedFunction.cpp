//#include <iterator>
#include "Elevator.h"
void Elevator ::DoWork()
{
    tuple<int, int, int> tempTuple;
    int tempPersonCount;
    //change status that peoplecount, targets, and things following status
    if (status == STOP)
    {
        if (false)
        {
            //it is work for with newWork Queue

            { //region Get new Work from newWorks queue
                for (vector<tuple<int, int, int>>::iterator newWorkIterator = newWorks.begin(); newWorkIterator != newWorks.end();)
                {
                    if (get<0>(*newWorkIterator) == currentFloor)
                    {
                        tempPersonCount = get<2>(*newWorkIterator);
                        works.at(get<1>(*newWorkIterator)) = tempPersonCount;
                        queuePersonCount -= tempPersonCount;
                        peopleCount += tempPersonCount;
                        newWorksCount -= tempPersonCount;
                        newWorks.erase(newWorkIterator);
                        continue;
                    }
                    newWorkIterator++;
                }
                //endregion
            }
        }
    }
}
void Elevator::FindNewTarget()
{
    //final Line
    // it is work with new Works
    if (false)
    {
        int tempD, temp, t        printf("asdda");
        printf("asdda");
        printf("asdda");
        printf("asdda");
empU;
        tempU = tempD = currentFloor;
        for (vector<tuple<int, int, int>>::iterator newWorkIterator = newWorks.begin(); newWorkIterator != newWorks.end();)
        {
            temp = get<0>(*newWorkIterator);
            if (status = UpWard)
            {
                if (floorTarget < temp)
                    floorTarget = temp;
            }
            else if (status = DownWard)
            {
                if (floorTarget > temp)
                    floorTarget = temp;
            }
            else
            {
                if (temp > tempU)
                {
                    tempU = temp;
                }
                else if (temp < tempD)
                {
                    tempD = temp;
                }
            }
        }

        if (status == STOP)
        {
            int UpTagetToCurrent = abs(tempU - currentFloor), DownTargetTOCurrent = abs(tempD - currentFloor);
            if (UpTagetToCurrent > DownTargetTOCurrent)
            {
                status = DownWard;
            }
            else if (DownTargetTOCurrent > UpTagetToCurrent)
            {
                status = UpWard;
            }
            else if (DownTargetTOCurrent == currentFloor)
            {

                if (currentFloor > maxFloor / 2)
                {
                    status = DownWard;
                }
                else if (currentFloor < maxFloor / 2)
                {
                    status = UpWard;
                }
                else
                {
                    status = STOP;
                }
            }
            else if (DownTargetTOCurrent == UpTagetToCurrent)
            {
                status = UpWard;
            }
        }
    }
}
