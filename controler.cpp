#include "controler.h"
//#include "elevator.h"
using namespace std;

Controller::Controller(int floors, int elevatorCount, int maxPerson, distributers dis)
{
    dist = dis;
    tempQueue = make_tuple(-1,0,0,0);
    this->maxPerson = maxPerson;
    this->maxFloor = maxFloor;
    this->elevatorCount = elevatorCount;
    timer = 0;
    for (int i = 0; i < elevatorCount; i++)
    {
        elevators.push_back(new Elevator(maxPerson, maxFloor));
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
        jobsCountPerFloor[get<2>(tempQueue)]++;
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
        jobsCountPerFloor[init]++;
    }
    for(int i=0;i<maxFloor;i++)
        sort(jobsPerFloor.at(i).begin(),jobsPerFloor.at(i).end());
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
    return timer;
}
bool Controller::bAllFinished()
{
    //TODO : Check all work is finished
    for (int i = 0; i < elevatorCount; i++)
    {
        if ((elevators[i])->GetMiddleTarget() != -1)
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
        OriginalWay();
        break;
    default:
        printf("Error ");
        exit(0);
        break;
    }
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
    for (int i = 0; i < data.second; i++)
    {
        if (elevators[elNum]->IsFull())
            return;
        (elevators[elNum])->AddWork(data.first, 1);
        //(elevators.find(elNum))->AddWork(data.first, data.second);
        jobsCountPerFloor[data.first] -= 1; // 엘리베이터에 더해준 만큼 남아있는 사람 수를 줄인다.
    }
}

void Controller::PushData(int elNum, int targetFloor)
{
    if (!elevators[elNum]->IsFull())
    {
        (elevators[elNum])->AddWork(targetFloor, 1);
        jobsCountPerFloor[targetFloor] -= 1;
    }
}

void Controller::AddElevator()
{
    elevatorCount++;
    elevators.push_back(new Elevator(maxPerson, maxFloor));
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

    for (int i = 0; i < elevatorCount; i++)
    {
int j,tempFloor;
ElevatorStatus tempStatus;
        if (!elevators[i]->IsFull())
        {
             tempFloor = elevators[i]->GetCurrentFloor();
             tempStatus = elevators[i]->GetStatus();
            //TODO:make algorithm for distribute works
            if (tempStatus == UpWard)
            {
                for (j = 0; j < tempFloor; j++)
                    ;
                while (j < jobsPerFloor[tempFloor].size())
                {
                    if (elevators[i]->IsFull())
                    {
                        goto changeMiddleTarget;
                    }
                    PushData(i, jobsPerFloor[tempFloor].at(j));
                    jobsPerFloor[tempFloor].erase(jobsPerFloor[tempFloor].begin() + j);
                    //CheckMe : Counting is work?
                }
                for (j = 0; jobsPerFloor[tempFloor].at(j) != tempFloor - 1; j++)
                    ;
                for (; j >= 0 || elevators[i]->IsFull(); j--)
                {
                    PushData(i, jobsPerFloor[tempFloor].at(j));
                    jobsPerFloor[tempFloor].erase(jobsPerFloor[tempFloor].begin() + j);
                }
            }
            else if (tempStatus == DownWard)
            {
                for (j = 0; jobsPerFloor[tempFloor].at(j) != tempFloor - 1; j++)
                    ;
                for (; j >= 0; j--)
                {
                    if (elevators[i]->IsFull())
                        goto changeMiddleTarget;
                    PushData(i, jobsPerFloor[tempFloor].at(j));
                    jobsPerFloor[tempFloor].erase(jobsPerFloor[tempFloor].begin() + j);
                }
                for (; j < tempFloor; j++)
                    ;
                while (j < jobsPerFloor[tempFloor].size() || elevators[i]->IsFull())
                {
                    PushData(i, jobsPerFloor[tempFloor].at(j));
                    jobsPerFloor[tempFloor].erase(jobsPerFloor[tempFloor].begin() + j);
                    //CheckMe : Counting is work?
                }
            }
            else
            {
                if (tempFloor < elevators[i]->GetFloorTarget())
                {
                    for (j = 0; j < tempFloor; j++)
                        ;
                    while (j < jobsPerFloor[tempFloor].size())
                    {
                        if (elevators[i]->IsFull())
                        {
                            goto changeMiddleTarget;
                        }
                        PushData(i, jobsPerFloor[tempFloor].at(j));
                        jobsPerFloor[tempFloor].erase(jobsPerFloor[tempFloor].begin() + j);
                        //CheckMe : Counting is work?
                    }
                    for (j = 0; jobsPerFloor[tempFloor].at(j) != tempFloor - 1; j++)
                        ;
                    for (; j >= 0 || elevators[i]->IsFull(); j--)
                    {
                        PushData(i, jobsPerFloor[tempFloor].at(j));
                        jobsPerFloor[tempFloor].erase(jobsPerFloor[tempFloor].begin() + j);
                    }
                }
                else if (tempFloor > elevators[i]->GetFloorTarget())
                {
                    for (j = 0; jobsPerFloor[tempFloor].at(j) != tempFloor - 1; j++)
                        ;
                    for (; j >= 0; j--)
                    {
                        if (elevators[i]->IsFull())
                            goto changeMiddleTarget;
                        PushData(i, jobsPerFloor[tempFloor].at(j));
                        jobsPerFloor[tempFloor].erase(jobsPerFloor[tempFloor].begin() + j);
                    }
                    for (; j < tempFloor; j++)
                        ;
                    while (j < jobsPerFloor[tempFloor].size() || elevators[i]->IsFull())
                    {
                        PushData(i, jobsPerFloor[tempFloor].at(j));
                        jobsPerFloor[tempFloor].erase(jobsPerFloor[tempFloor].begin() + j);
                        //CheckMe : Counting is work?
                    }
                }
                else
                {
                    for (j = 0; jobsPerFloor[tempFloor].at(j) < tempFloor; j++)
                        ;
                    int pre = j;
                    for (; jobsPerFloor[tempFloor].at(j) < tempFloor + 1; j++)
                        ;
                    int next = jobsPerFloor[tempFloor].size() - j;
                    if (pre < next)
                    {
                        for (j = 0; j < tempFloor; j++)
                            ;
                        while (j < jobsPerFloor[tempFloor].size())
                        {
                            if (elevators[i]->IsFull())
                            {
                                goto changeMiddleTarget;
                            }
                            PushData(i, jobsPerFloor[tempFloor].at(j));
                            jobsPerFloor[tempFloor].erase(jobsPerFloor[tempFloor].begin() + j);
                            //CheckMe : Counting is work?
                        }
                        for (j = 0; jobsPerFloor[tempFloor].at(j) != tempFloor - 1; j++)
                            ;
                        for (; j >= 0 || elevators[i]->IsFull(); j--)
                        {
                            PushData(i, jobsPerFloor[tempFloor].at(j));
                            jobsPerFloor[tempFloor].erase(jobsPerFloor[tempFloor].begin() + j);
                        }
                    }
                    else if (pre > next)
                    {
                        for (j = 0; jobsPerFloor[tempFloor].at(j) != tempFloor - 1; j++)
                            ;
                        for (; j >= 0; j--)
                        {
                            if (elevators[i]->IsFull())
                                goto changeMiddleTarget;
                            PushData(i, jobsPerFloor[tempFloor].at(j));
                            jobsPerFloor[tempFloor].erase(jobsPerFloor[tempFloor].begin() + j);
                        }
                        for (; j < tempFloor; j++)
                            ;
                        while (j < jobsPerFloor[tempFloor].size() || elevators[i]->IsFull())
                        {
                            PushData(i, jobsPerFloor[tempFloor].at(j));
                            jobsPerFloor[tempFloor].erase(jobsPerFloor[tempFloor].begin() + j);
                            //CheckMe : Counting is work?
                        }
                    }
                }
            }
        //make change middle Target
        changeMiddleTarget:
            elevators[i]->SetMiddleTarget(
                GetClosestFloor(elevators[i]->GetCurrentFloor(), elevators[i]->GetStatus(), true));
        }
    }
}
void Controller::OriginalWay()
{
    int tempFloor, j;
    ElevatorStatus tempStatus;
    for (int i = 0; i < elevatorCount; i++)
    {
        if (!(elevators.at(i)->IsFull()))
        {
            tempFloor = elevators[i]->GetCurrentFloor();
            tempStatus = elevators[i]->GetStatus();
            //TODO:make Inputs
            if (tempStatus == UpWard)
            {
                for (j = 0; j < tempFloor; j++)
                    ;
                while (j < jobsPerFloor[tempFloor].size())
                {
                    if (elevators[i]->IsFull())
                    {
                        break;
                    }
                    PushData(i, jobsPerFloor[tempFloor].at(j));
                    jobsPerFloor[tempFloor].erase(jobsPerFloor[tempFloor].begin() + j);
                    //CheckMe : Counting is work?
                }
            }
            else if (tempStatus == DownWard)
            {
                for (j = 0; jobsPerFloor[tempFloor].at(j) != tempFloor - 1; j++)
                    ;
                for (; j >= 0 || elevators[i]->IsFull(); j--)
                {
                    PushData(i, jobsPerFloor[tempFloor].at(j));
                    jobsPerFloor[tempFloor].erase(jobsPerFloor[tempFloor].begin() + j);
                }
            }
            else
            {
                if (tempFloor < elevators[i]->GetFloorTarget())
                {
                    for (j = 0; j < tempFloor; j++)
                        ;
                    while (j < jobsPerFloor[tempFloor].size())
                    {
                        if (elevators[i]->IsFull())
                        {
                            break;
                        }
                        PushData(i, jobsPerFloor[tempFloor].at(j));
                        jobsPerFloor[tempFloor].erase(jobsPerFloor[tempFloor].begin() + j);
                        //CheckMe : Counting is work?
                    }
                }
                else if (tempFloor > elevators[i]->GetFloorTarget())
                {
                    for (j = 0; jobsPerFloor[tempFloor].at(j) != tempFloor - 1; j++)
                        ;
                    for (; j >= 0 || elevators[i]->IsFull(); j--)
                    {
                        PushData(i, jobsPerFloor[tempFloor].at(j));
                        jobsPerFloor[tempFloor].erase(jobsPerFloor[tempFloor].begin() + j);
                    }
                }
                else
                {
                    for (j = 0; jobsPerFloor[tempFloor].at(j) < tempFloor; j++)
                        ;
                    int pre = j;
                    for (; jobsPerFloor[tempFloor].at(j) < tempFloor + 1; j++)
                        ;
                    int next = jobsPerFloor[tempFloor].size() - j;
                    if (pre < next)
                    {
                        for (j = 0; j < tempFloor; j++)
                            ;
                        while (j < jobsPerFloor[tempFloor].size())
                        {
                            if (elevators[i]->IsFull())
                            {
                                break;
                            }
                            PushData(i, jobsPerFloor[tempFloor].at(j));
                            jobsPerFloor[tempFloor].erase(jobsPerFloor[tempFloor].begin() + j);
                            //CheckMe : Counting is work?
                        }
                    }
                    else if (next > pre)
                    {
                        for (j = 0; jobsPerFloor[tempFloor].at(j) != tempFloor - 1; j++)
                            ;
                        for (; j >= 0 || elevators[i]->IsFull(); j--)
                        {
                            PushData(i, jobsPerFloor[tempFloor].at(j));
                            jobsPerFloor[tempFloor].erase(jobsPerFloor[tempFloor].begin() + j);
                        }
                    }
                }
            }
        //change middle Target
        changeMiddleTarget:
            elevators[i]->SetMiddleTarget(
                GetClosestFloor(tempStatus, tempStatus, false));
        }
    }
}
int Controller ::GetClosestFloor(int CurrentFloor, ElevatorStatus status, bool includeOtherWay)
{

    if (status == UpWard)
    {
        for (int i = CurrentFloor + 1; i < maxFloor; i++)
        {
            if (jobsPerFloor[i].size() != 0)
            {
                if (includeOtherWay)
                {
                    return i;
                }
                for (int j = 0; j < jobsPerFloor[i].size(); j++)
                {
                    if (jobsPerFloor[i].at(j) > i || jobsPerFloor[i].at(j) == maxFloor - 1)
                    {
                        return i;
                    }
                }
            }
        }
    }
    else if (status == DownWard)
    {
        for (int i = 0; i < CurrentFloor; i++)
        {
            if (jobsPerFloor[i].size() != 0)
            {
                if (includeOtherWay)
                {
                    return i;
                }
                for (int j = jobsPerFloor[i].size(); j > 0; j--)
                {
                    if (jobsPerFloor[i].at(j - 1) == 0 || jobsPerFloor[i].at(j - 1) < i)
                    {
                        return i;
                    }
                }
            }
        }
    }
    else //status == STOP
    {
        int checkPoint = (CurrentFloor > maxFloor - CurrentFloor) ? CurrentFloor : maxFloor - CurrentFloor;
        for (int i = 0; i < checkPoint; i++)
        {
            if (CurrentFloor + i < maxFloor && jobsPerFloor[CurrentFloor + i].size() != 0)
            {
                return i;
            }
            else if (CurrentFloor - i >= 0 && jobsPerFloor[CurrentFloor - i].size() != 0)
            {
                return i;
            }
        }
    }
    return -1;
}
int main()
{
    //Controller con(25, 2, 8, OurWay);
    Controller con(25, 2, 8, originalWay);
    con.SetInputFile("dataset/data1.txt");
    printf("%d", con.Excutes());
}
