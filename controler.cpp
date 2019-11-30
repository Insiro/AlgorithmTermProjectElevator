#include "controler.h"
#include "Elevator.h"
using namespace std;

Controller::Controller(int floors, int elevatorCount, int maxPerson, distributers dis)
{
    dist = dis;
    this->maxPerson = maxPerson;
    this->maxFloor = maxFloor;
    this->elevatorCount = elevatorCount;
    timer = 0;
    for (int i = 0; i < elevatorCount; i++)
    {
        elevators.insert(make_pair(i, new Elevator(maxPerson, maxFloor)));
    }
}
bool Controller ::IsJobEmpty()
{

    for (int i = 0; i < maxFloor; i++)
    {
        if (jobsCountPerFloor[i] != 0)
        {
            return true;
        }
    }
    return false;
}
int Controller::InsertJob()
{

    if (timer == get<0>(tempQueue))
    {
        jobsPerFloor[get<2>(tempQueue)].push_back(get<3>(tempQueue));
    }
    else if (timer != -1)
    {
        return 0;
    }
    int time, Count, init, target;
    while (true)
    {
        fscanf(inputFile, "%d %d %d %d", &time, &Count, &init, &target);
        if (time != timer)
        {
            tempQueue = make_tuple(time, Count, init, target);
            break;
        }
        jobsPerFloor[init].push_back(target);
    }
}
int Controller::Excutes()
{
    timer = 0;
    //TODO : Make excuter code and return finished Time
    while (!bAllFinished())
    {
        InsertJob();
        DistributeJobs();
        for (int i = 0; i < elevatorCount; i++)
        {
            elevators[i]->DoWork();
        }
        addLog();
        timer++;
    }
    fclose(inputFile);
    fclose(logFile);
    //fin
}
bool Controller::bAllFinished()
{
    //TODO : Check all work is finished
    for (int i = 0; i < elevatorCount; i++)
    {
        if ((elevators[i])->GetmiddleTarget() != NULL)
        {
            return false;
        }
    }
    return (IsJobEmpty()) ? true : false;
}
void Controller::DistributeJobs()
{
    switch (dist)
    {
    case OurWay:
        ourWay();
        break;
    case originalWay:
    originalWay();
        break;
    default:
    printf("Error ");
        exit(0);
        break;
    }
    //TODO: make distribue on jobs
}
void Controller::makeLogFile()
{

    string fileName = "log";
    switch (dist)
    {
    case originalWay:
        fileName += "_origin";
        break;
    case OurWay:
        fileName += "_ours";
    default:
        exit(0);
        break;
    }
    fileName += ".txt";
    logFile = fopen(fileName.c_str(), "w");
    // status can use Elevator -> status, getWorks
}
void Controller::addLog()
{
    vector<int> queue;
    fprintf(logFile, "TIME %d\n", timer);
    fprintf(logFile, "Queue");
    //print queue
    for (int i = 0; i < maxFloor; i++)
    {
        fprintf(logFile, "\n%d ", i);
        queue = jobsPerFloor.at(i);
        for (int i = 0; i < queue.size(); i++)
        {
            fprintf(logFile, "%d ", jobsPerFloor);
        }
    }
    //print elevator info
    Elevator *ele;
    vector<int> eleque;
    for (int i = 0; i < elevatorCount; i++)
    {
        ele = elevators[i];
        fprintf(logFile, "\nElevator %d %d", i, ele->GetStatus());
        eleque = ele->GetWorks();
        for (int i = 0; i < eleque.size(); i++)
        {
            fprintf(logFile, "%d ", eleque[i]);
        }
    }
    fprintf(logFile, "\n");
}

void Controller::PushData(int elNum, pair<int, int> data)
{

    (elevators[elNum])->AddWork(data.first, data.second);
    //(elevators.find(elNum))->AddWork(data.first, data.second);
    jobsCountPerFloor[data.first] -= data.second; // 엘리베이터에 더해준 만큼 남아있는 사람 수를 줄인다.
}

void Controller::AddElevator()
{
    elevators.insert(make_pair(elevatorCount++, new Elevator(maxPerson, maxFloor)));
}
int Controller::GetmaxFloor()
{
    return maxFloor;
}
int Controller::GetElevatorCount()
{
    return elevatorCount;
}
vector<int> Controller::GetJobCount()
{
    return jobsCountPerFloor;
}

int Controller::GetJobCount(int floor)
{
    if (floor >= maxFloor || floor < 0)
    {
        return -1;
    }
    return jobsCountPerFloor[floor];
}
int Controller::SetInputFile(FILE *fptr)
{
    inputFile = fptr;
    if (inputFile == NULL)
    {
        return -1;
    }
    return 0;
}
int Controller::SetInputFile(string fileName)
{
    inputFile = fopen(fileName.c_str(), "r");
    if (inputFile == NULL)
    {
        return -1;
    }
    return 0;
}
void Controller::ourWay()
{
    //TODO:make algorithm for distribute works
}
void Controller::originalWay()
{
    //TODO:make algorithm for distribute works
}
int main()
{
    //Controller con(25, 2, 8, OurWay);
    Controller con(25, 2, 8, origianlWay);
    con.SetInputFile("input.txt");
    con.Excutes();
}
