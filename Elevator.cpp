#include <stdio.h>
enum ElevatorStatus{ STOP = 0, UpWard, DownWard, Open};
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
Elevator ::Elevator(int Max){
    this->MAX = Max;
    peopleCount = 0;
    status = STOP;
}
ElevatorStatus Elevator :: GetStatus(){
    return status;
}
bool Elevator :: IsFull(){
    return peopleCount == MAX;
}
int main(){

}