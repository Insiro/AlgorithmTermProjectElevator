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
    status = STOP;
    for (int i = 0; i < maxFloor; i++)
    {
        if (works[i] != 0)
        {
            floorTarget = i;
            if (i > currentFloor)
            {
                status = UpWard;
            }
            else if (i < currentFloor)
            {
                status = DownWard;
            }
            break;
        }
    }
    if (status == STOP)
    {
        if (middleTarget != NULL)
        {
            if (currentFloor > middleTarget)
                status = UpWard;
            else if (currentFloor < middleTarget)
                status = DownWard;
        }
    }
    
}
void Elevator ::DoWork()
{
    int tempPersonCount;
    //change status that peoplecount, targets, and things following status
    if (status == STOP)
    {
        
        //teat works
        if (works[currentFloor] != 0)
        {
            //GET ,output
            peopleCount - works[currentFloor];
            works[currentFloor] = 0;
            status = (currentFloor > floorTarget) ? DownWard : UpWard;
        }
        // not have Wroks
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
    }
    else if (status == UpWard)
    {
        currentFloor++;
    }
    else
    {
        currentFloor--;
    }

    if (currentFloor == floorTarget || currentFloor == middleTarget)
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
void Elevator::AddWork(int target, int personCount)
{
    works.at(target) += personCount;
    peopleCount += personCount;
    if (middleTarget == floorTarget)
        middleTarget = NULL;
}
void Elevator::AddWork(vector<pair<int, int>> newWorks)
{
    for (int i = 0; i < newWorks.size(); i++)
    {
        works.at(newWorks.at(i).first) += newWorks.at(i).second;
        peopleCount += newWorks.at(i).second;
    }
    if (middleTarget == floorTarget)
        middleTarget = NULL;
}
int Elevator::GetPeopleCount()
{
    return peopleCount;
}
vector<int> Elevator::GetTargets()
{
    return works;
}
int Elevator::GetmiddleTarget()
{
    return middleTarget;
}
void Elevator::setMiddleTarget(int MTarget)
{
    middleTarget = MTarget;
}
int main()
{
}