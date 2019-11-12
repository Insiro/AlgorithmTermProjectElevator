#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <Elevator.h>
#include <vector>
using namespace std;

class Controller
{
private:
    int elevatorCount, floors;
    map<int, Elevator *> elevators;
    vector<int> job;

public:
    Controller(int floors, int elevatorCount, int maxPerson);
    void addElevator(int maxPerson);
    void PushData(pair<int, int> *data);
    bool EmptyJob();
    void insertJob(string jobs);
};
Controller::Controller(int floors, int elevatorCount, int maxPerson)
{
    this->floors = floors;
    this->elevatorCount = elevatorCount;
    for (int i = 0; i < elevatorCount; i++)
    {
        elevators.insert(make_pair(i, new Elevator(maxPerson)));
    }
}
void Controller::insertJob(string jobs)
{
    // jobs format : target floor 2char, start floor 2char
    for(int i=0;i<jobs.length/4;i++){
        
    }
}
void Controller::addElevator(int maxPerson)
{
    elevators.insert(make_pair(++elevatorCount, new Elevator(maxPerson)));
}
int main()
{
}