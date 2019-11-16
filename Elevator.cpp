#include <stdio.h>
#include <vector>
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
    for (int i = 0; i < maxFloor; i++)
    {
        if (works[i] != 0)
        {
            if (i > currentFloor)
            {
                status = UpWard;
                currentFloor++;
            }
            else if (i < currentFloor)
            {
                status = DownWard;
                currentFloor--;
            }
            return;
        }
    }
    status = STOP;
    floorTarget = -1;
}
void Elevator ::DoWork()
{

    //change status that peoplecount, targets, and things following status
    // not have Wroks
    if (works[currentFloor] != 0)
    {
        //GET ,output
        peopleCount - works[currentFloor];
        works[currentFloor] = 0;
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
            //MoveToTargetFloor
            if (currentFloor > floorTarget)
            {
                status = DownWard;
                currentFloor--;
            }
            else if (currentFloor < floorTarget)
            {
                status = UpWard;
                currentFloor++;
            }
        }
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
void Elevator::AddWork(int target, int fromFloor)
{
    newWorks.push_back(make_pair(target, fromFloor));
    //TODO:add person who in elevator
}
void Elevator::AddWork(vector<pair<int, int>> newWorks)
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