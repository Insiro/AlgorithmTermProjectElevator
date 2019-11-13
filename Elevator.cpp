#include <stdio.h>
#include <vector>
#include <Elevator.h>
using namespace std;


int Elevator::GetFloorTarget(){
    return floorTarget;
}
int Elevator::GetCurrentFloor(){
    return currentFloor;
}
void Elevator ::DoWork(){
    //TODO : change status that peoplecount, targets, and things following status
}
Elevator ::Elevator(int Max)
{
    this->MAX = Max;
    peopleCount = 0;
    status = STOP;
    currentFloor = 0;
}
ElevatorStatus Elevator ::GetStatus()
{
    return status;
}
bool Elevator ::IsFull()
{
    return peopleCount == MAX;
}
vector<int> Elevator::GetWorks()
{
    return works;
}
int Elevator::AddWork(int target) {
    //TODO:add person who in elevator
}
int Elevator::AddWork(vector<int> targets) {
    //TODO:add person who in elevator as list
}
int Elevator::GetPeopleCount(){
    return peopleCount;
}
vector<int> Elevator::GetTargets(){
    //TODO:make GetTargets
    vector<int> a;
    return a;
}
int main()
{
}