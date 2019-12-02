#include <stdio.h>
#include <vector>
#include<tuple>
enum ElevatorStatus;
class Elevator
{
private:
    ElevatorStatus status;
    ElevatorStatus preStatus;
    int currentFloor;
    int MAX;
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
    void AddWork(int target,int personCount);
    void AddWork(vector<pair<int , int >>newWorks);
    void SetMiddleTarget(int MTarget);
	int GetPeopleCount();
    int GetCurrentFloor();
    int GetFloorTarget();   //최고 층이나 최저 층  
    int GetMiddleTarget();  // 중간에 거치는 층
};
enum ElevatorStatus
{
    STOP = 0,
    UpWard,
    DownWard,
    Open
};


