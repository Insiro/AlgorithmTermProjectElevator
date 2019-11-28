#include "Elevator.h"
using namespace std;

int Elevator::GetFloorTarget()
{
    return floorTarget;
}
int Elevator::GetCurrentFloor()
{
    return currentFloor;
}
void Elevator::FindNewTarget()
{
    //TODO:checking newWorkQueue is must be excuted
    for (int i = 0; i < maxFloor; i++)
    {
        if (works[i] != 0)
        {
            if (i > currentFloor)
            {
                status = UpWard;
            }
            else if (i < currentFloor)
            {
                status = DownWard;
            }
            return;
        }
    }
    status = STOP;
}
void Elevator ::DoWork()
{
    tuple<int, int, int> tempTuple;
    int tempPersonCount;
    //change status that peoplecount, targets, and things following status
    // not have Wroks
    //FIXME : check there are works in newWorks to stop for input
    if (status == STOP)
    {
        if (works[currentFloor] != 0)
        {
            //GET ,output
            peopleCount - works[currentFloor];
            works[currentFloor] = 0;
            //Get new Work from newWorks queue
            for (vector<tuple<int, int, int>>::iterator newWorkIterator = newWorks.begin(); newWorkIterator != newWorks.end();)
            {
                if (get<0>(*newWorkIterator) == currentFloor)
                {
                    tempPersonCount = get<2>(*newWorkIterator);
                    works.at(get<1>(*newWorkIterator)) = tempPersonCount;
                    queuePersonCount -= tempPersonCount;
                    peopleCount += tempPersonCount;
                    newWorks.erase(newWorkIterator);
                    continue;
                }
                newWorkIterator++;
            }
        }
        else
        {
            if (floorTarget == -1 || floorTarget == currentFloor)
            {
                //Elevator IDLE or Find new Target in list
                FindNewTarget();
            }
            else
            {
                //updateStatus to move Target
                status = (currentFloor > floorTarget) ? DownWard : UpWard;
            }
        }
        return;
    }
    else if (status == UpWard)
    {
        currentFloor++;
    }
    else
    {
        currentFloor--;
    }

    if (currentFloor == floorTarget)
    {
        status = STOP;
    }
}
Elevator ::Elevator(int Max, int maxFloor)
{
    this->MAX = Max;
    this->maxFloor = maxFloor;
    peopleCount = 0;
    status = STOP;
    currentFloor = 0;
}
ElevatorStatus Elevator ::GetStatus()
{
    return status;
}
bool Elevator ::IsFull()
{
    return peopleCount == MAX;
}
vector<int> Elevator::GetWorks()
{
    return works;
}
void Elevator::AddWork(int target, int fromFloor, int personCount)
{
    newWorks.push_back(make_tuple(target, fromFloor, personCount));
    //TODO:add person who in elevator
}
void Elevator::AddWork(vector<tuple<int, int, int>> newWorks)
{
    //TODO:add person who in elevator as list
}
int Elevator::GetPeopleCount()
{
    return peopleCount;
}
vector<int> Elevator::GetTargets()
{
    //TODO:check return is available that vector types
    return works;
}
void Elevator::UpdateStatus(ElevatorStatus status)
{
    this->status = status;
}

int main()
{
}