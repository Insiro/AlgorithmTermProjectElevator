#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include "controler.h"
#include <time.h>
using namespace std;

Controller::Controller(int maxFloor, int elevatorCount, int maxPerson)
{

    this->maxPerson = maxPerson;
    this->maxFloor = maxFloor;
    this->elevatorCount = elevatorCount;
    timer = 0;
    for (int i = 0; i < elevatorCount; i++)
    {
        elevators.insert(make_pair(i, new Elevator(maxPerson, maxFloor)));
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
    if (target<1||target >= maxFloor||floor<1 || floor >= maxFloor)
        return -1;
    //TODO:make InsertJobs
}
int Controller::Excutes()
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
void Controller::makeLogFile()
{

    //TODO:make logs following elevator status and job queue
    // status can use Elevator -> status, getWorks
}
void Controller::addLog()
{
    vector<int> queue;
    fprintf(logFile, "TIME %d\n", timer);
    fprintf(logFile, "Queue");
    //print queue
    for (int i = 0; i < maxFloor; i++)
    {
        fprintf(logFile, "\n%d ", i);
        queue = jobsPerFloor.at(i);
        for (int i = 0; i < queue.size(); i++)
        {
            fprintf(logFile, "%d ", jobsPerFloor);
        }
    }
    //print elevator info
    Elevator *ele;
    vector<int> eleque;
    for (int i = 0; i < elevatorCount; i++)
    {
        ele = elevators[i];
        fprintf(logFile, "\nElevator %d %d", i, ele->GetStatus());
        eleque = ele->GetWorks();
        for (int i = 0; i < eleque.size(); i++)
        {
            fprintf(logFile, "%d ", eleque[i]);
        }
    }
    fprintf(logFile,"\n");
}
void Controller::ourWay()
{
    //TODO:make algorithm for distribute works
}

void Controller::AddElevator()
{
    elevators.insert(make_pair(elevatorCount++, new Elevator(maxPerson, maxFloor)));
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