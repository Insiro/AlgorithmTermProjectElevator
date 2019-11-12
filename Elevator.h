enum ElevatorStatus;
class Elevator{
    private :
        ElevatorStatus status;
        int MAX;
        int peopleCount;
    public : 
        Elevator(int Max);
    ElevatorStatus GetStatus();
    bool IsFull();
    void DoWork();
};