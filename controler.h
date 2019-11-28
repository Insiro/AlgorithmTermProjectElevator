#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <time.h>
#include <tuple>
#include <vector>
#include "Elevator.h"
using namespace std;

class Controller
{
private:
    int elevatorCount, maxFloor, distributerCount;
    int timer;
    map<int, Elevator *> elevators;
    map<int, vector<int>> jobsPerFloor;
    vector<int> jobsCountPerFloor;
    int maxPerson;
    FILE *inputFile;
    FILE *logFile;
    void ourWay();

public:
    enum distributers
    {
        OurWay
    };
    Controller(int floors, int elevatorCount, int maxPerson);
    void makeLogFile();
    void addLog();
    void DistributeJobs(distributers distributerName);
    void AddElevator();
    void PushData(int eleNum,pair<int,int> data);		// elevator 번호  목적지 목적지당 사람수
    bool IsJobEmpty();
    bool bAllFinished();
    int InsertJob(int floor, int target);
    int GetmaxFloor();
    int GetElevatorCount();
    int GetJobCount(int floor);
    int GetStartTime();
    int Excutes();
    int SetInputFile(FILE *fptr);
    int SetInputFile(string fileName);
    int GetWorks();
    vector<int> GetJobCount();
};