enum ElevatorStatus;
class Elevator
{
private:
    ElevatorStatus status;
    int currentFloor;
    int MAX;
    int floorTarget;
    int peopleCount;
    vector<int> works;
    
public:
    Elevator(int Max);
    ElevatorStatus GetStatus();
    bool IsFull();
    void DoWork();
    vector<int> GetWorks();
    int AddWork(int);
    int AddWork(vector<int>);
    int GetPeopleCount();
    vector<int> GetTargets();
    int GetCurrentFloor();
    int GetFloorTarget();
};
enum ElevatorStatus
{
    STOP = 0,
    UpWard,
    DownWard,
    Open
};