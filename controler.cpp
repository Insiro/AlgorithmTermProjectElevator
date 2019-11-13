#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <controler.h>
#include <time.h>
using namespace std;
time_t Controller::GetStartTime()
{
    return startTime;
}
Controller::Controller(int maxFloor, int elevatorCount, int maxPerson)
{
    startTime = time(NULL);
    this->maxFloor = maxFloor;
    this->elevatorCount = elevatorCount;
    for (int i = 0; i < elevatorCount; i++)
    {
        elevators.insert(make_pair(i, new Elevator(maxPerson)));
    }
}
bool Controller ::IsJobEmpty()
{

    for (int i = 0; i < maxFloor; i++)
    {
        if (jobsCountPerFloor[i] != 0)
        {
            return true;
        }
    }
    return false;
}
int Controller::InsertJob(int floor, int target)
{
    if (target >= maxFloor || floor >= maxFloor)
        return -1;
    //TODO:make InsertJobs
}
time_t Controller::Excutes()
{
    //TODO : Make excuter code and return finished Time
}
bool Controller::bAllFinished()
{
    //TODO : Check all work is finished
    return true;
}
void Controller::DistributeJobs(distributers distributerName)
{
    if (distributerName == OurWay)
    {
        ourWay();
    }
    //TODO: make distribue on jobs
}
void Controller::makeLog()
{
    //TODO:make logs following elevator status and job queue
}
void Controller::ourWay()
{
    //TODO:make algorithm for distribute works
}

void Controller::AddElevator(int maxPerson)
{
    elevators.insert(make_pair(++elevatorCount, new Elevator(maxPerson)));
}
int Controller::GetmaxFloor()
{
    return maxFloor;
}
int Controller::GetElevatorCount()
{
    return elevatorCount;
}
vector<int> Controller::GetJobCount()
{
    return jobsCountPerFloor;
}
int Controller::GetJobCount(int floor)
{
    if (floor >= maxFloor)
    {
        return -1;
    }
    return jobsCountPerFloor[floor];
}
int Controller::SetInputFile(FILE *fptr)
{
    inputFile = fptr;
    if (inputFile == NULL)
    {
        return -1;
    }
    return 0;
}
int Controller::SetInputFile(string fileName)
{
    inputFile = fopen(fileName.c_str(), "r");
    if (inputFile == NULL)
    {
        return -1;
    }
    return 0;
}
int main()
{
}