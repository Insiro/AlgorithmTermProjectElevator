#include <stdio.h>
#include <vector>
#include<tuple>
enum ElevatorStatus;
class Elevator
{
private:
    ElevatorStatus status;
    int currentFloor;
    int MAX;
    int floorTarget;
    int peopleCount;
    int maxFloor;
    int queuePersonCount;
    int newWorksCount;
    int middleTarget;
    vector<int> works;
    vector<tuple<int, int,int>> newWorks;
    void FindNewTarget();
public:
    Elevator(int Max, int maxFloor);
    ElevatorStatus GetStatus();
    bool IsFull();
    void DoWork();
    vector<int> GetTargets();
    vector<int> GetWorks();
    void AddWork(int target,int personCount);
    void AddWork(vector<pair<int, int>>newWorks);
    int GetPeopleCount();
    int GetCurrentFloor();
    int GetFloorTarget();
    int GetmiddleTarget();
};
enum ElevatorStatus
{
    STOP = 0,
    UpWard,
    DownWard,
    Open
};