#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <time.h>
#include <tuple>
#include <vector>
#include<algorithm>
#include "Elevator.h"
using namespace std;

class Controller
{
    enum distributers
    {
        originalWay,
        OurWay
    };

private:
    int elevatorCount, maxFloor, distributerCount;
    int timer;
    int maxPerson;
    map<int, Elevator *> elevators;
    map<int, vector<int>> jobsPerFloor;
    vector<int> jobsCountPerFloor;
    FILE *inputFile;
    FILE *logFile;
    tuple<int /*timestamp*/, int/*Count*/,int/*start floor*/,int/*target floor*/> tempQueue;
    distributers dist;
    void ourWay();
    void originalWay();

public:
    Controller(int floors, int elevatorCount, int maxPerson, distributers dis);
    void makeLogFile();
    void addLog();
    void DistributeJobs();
    void AddElevator();
    void PushData(int eleNum, pair<int/*target floor*/, int/*person Count*/> data);
    bool IsJobEmpty();
    bool bAllFinished();
    int InsertJob(); //get data from input files
    int GetmaxFloor();
    int GetElevatorCount();
    int GetJobCount(int floor);
    int Excutes();
    int SetInputFile(FILE *fptr);
    int SetInputFile(string fileName);
    int GetWorks();
    int GetClosestFloor(int CurrentFloor, ElevatorStatus status, bool includeOtherWay);
    vector<int> GetJobCount();
};