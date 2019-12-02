#include <stdio.h>
#include <vector>
#include <tuple>
using namespace std;

enum ElevatorStatus
{
    STOP = 0,
    UpWard,
    DownWard
};

class Elevator
{
private:
    ElevatorStatus status;
    ElevatorStatus preStatus;
    int currentFloor;
    int maxPerson;
    int floorTarget;
    int peopleCount;
    int maxFloor;
    int queuePersonCount;
    int newWorksCount;
    int middleTarget;
    vector<int> works;
    //vector<tuple<int, int,int>> newWorks;
    void FindNewTarget();

public:
    Elevator(int Max, int maxFloor);
    ElevatorStatus GetStatus();
    bool IsFull();
    void DoWork();
    vector<int> GetTargets();
    vector<int> GetWorks();
    void AddWork(int target, int personCount);
    void AddWork(vector<pair<int, int>> newWorks);
    void SetMiddleTarget(int MTarget);
    int GetPeopleCount();
    int GetCurrentFloor();
    int GetFloorTarget();
    int GetMiddleTarget();
};
