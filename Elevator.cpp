#include "elevator.h"
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
                currentFloor ++;
            }
            else if (i < currentFloor)
            {
                status = DownWard;
                currentFloor --;
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
   // ElevatorStatus status = this->status;
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
            if(floorTarget != currentFloor){
                //updateStatus to move Target
                // 일이 있으나 stop 상태 -> 일을 방금 받은 상태
                status = (currentFloor > floorTarget) ? DownWard : UpWard;
            }
            else 
            {
                //if (floorTarget == -1 || floorTarget == currentFloor)
                //Elevator IDLE or Find new Target in list
                FindNewTarget();
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
Elevator ::Elevator(int max, int maxFloor)
{
    this->maxPerson = max;
    this->maxFloor = maxFloor;
    this->peopleCount = 0;
    status = STOP;
    this->currentFloor = 0;
}
ElevatorStatus Elevator ::GetStatus()
{
    return status;
}
bool Elevator ::IsFull()
{
    return peopleCount >=maxPerson;
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
int Elevator::GetMiddleTarget()
{
    return middleTarget;
}
void Elevator::SetMiddleTarget(int MTarget)
{
    middleTarget = MTarget;
}