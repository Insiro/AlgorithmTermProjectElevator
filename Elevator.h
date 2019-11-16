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
    vector<int> works;
    vector<pair<int, int>> newWorks;
    void FindNewTarget();
public:
    Elevator(int Max, int maxFloor);
    ElevatorStatus GetStatus();
    bool IsFull();
    void DoWork();
    vector<int> GetTargets();
    vector<int> GetWorks();
    void AddWork(int target, int fromFloor);
    void AddWork(vector<pair<int, int>>newWorks);
    int GetPeopleCount();
    int GetCurrentFloor();
    int GetFloorTarget();
    
    void UpdateStatus(ElevatorStatus status);
};
enum ElevatorStatus
{
    STOP = 0,
    UpWard,
    DownWard,
    Open
};