#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
/*
Brust time : actual time of cpu usage
Waiting time : difference between the arrival time and time at which process first recives the CPU

*/


class ProcessData{
    public:
    int id;
    bool state=0;
    int burst_time;
    int arrival_time;
    int waiting_time;
    int finishing_time;
};

bool operator <(const ProcessData &a, const ProcessData &b){
    return a.burst_time>b.burst_time;
}

bool compFCFS(const ProcessData &a,const ProcessData &b){
    return a.arrival_time<b.arrival_time;
}

bool compSJF(const ProcessData &a, const ProcessData &b){
    return a.burst_time<b.burst_time;
}


float FCFS(ProcessData process[],int size){
    /*
        executes processes on the basis of first come and first serve
        returns average waiting time for the given list of processes
    */
    if(size==0)return 0;
    int completed_process=0;
    int time=0;

    int i=0;
    sort(process,process+size,compFCFS);  //sorting processes on basis of arrival time;

    for(int i=0; i<size; i++){
        process[i].state=1;

        time = max(time, process[i].arrival_time);
        time += process[i].burst_time;
        process[i].finishing_time = time;
        process[i].waiting_time = process[i].finishing_time - process[i].arrival_time - process[i].burst_time;
    }

    float avg_waiting_time = 0;
    for(int i=0; i<size; i++){

        // printf("%d ",process[i].waiting_time);
        avg_waiting_time += process[i].waiting_time;
    }
    // cout<<endl;
    avg_waiting_time/=size;
    return avg_waiting_time;
}

float SJF(ProcessData process[], int size){
    /*
    Performs the shortest task first given a group of programs
    */
   if(size==0)return 0;
    ProcessData process2[size];
    sort(process,process+size, compFCFS);
    priority_queue<ProcessData> que;

    int time=0;

    int index=0;
    for(index=0; index<size; index++){
        if(process[index].arrival_time<=time){
            que.push(process[index]);
        }
        else{
            break;
        }
    }
    // cout<<"$"<<size<<endl;
    float avg_waiting_time = 0;

    ProcessData tmp;
    while(que.size()!=0){
        tmp = que.top();
        que.pop();
        time+=tmp.burst_time;
        tmp.finishing_time = time;
        tmp.waiting_time = tmp.finishing_time - tmp.arrival_time -tmp.burst_time;
        // cout<<tmp.id<<"#"<<tmp.waiting_time<<endl;

        avg_waiting_time+=tmp.waiting_time;
        for(index=index; index<size; index++){
            // cout<<index<<" #"<<endl;
            if(process[index].arrival_time<=time){
                que.push(process[index]);
            }
            else break;
        }
    }
    avg_waiting_time/=size;
    return avg_waiting_time;

}

float roundRobin(ProcessData process[], int size, int time_quantum){
    int no_incomplete = size;
    int end=0;
    int time=0;
    sort(process,process+size,compFCFS); //sorting on basis of arival time

    int burst[size];

    for(int i=0; i<size; i++){
        burst[i] = process[i].burst_time;
    }


    for(int i=0; i<size; i++){
        if(process[i].arrival_time<=time)end++;
        else break;
    }

    while(1){
        bool flag=1;
        for(int i=0; i<size; i++){ 
            if(burst[i]>0){
                flag=0;
                if(burst[i]<=time_quantum){
                    burst[i]=0;
                    time+=burst[i];
                    process[i].finishing_time=time;
                    process[i].waiting_time = process[i].finishing_time - process[i].arrival_time -process[i].burst_time;
                }
                else{
                    burst[i]-=time_quantum;
                    time+=time_quantum;
                }
            }
        }
        if(flag)break;
    }


    float avg_waiting_time = 0;
    for(int i=0; i<size; i++){
        printf("%d %d\n",process[i].id,process[i].waiting_time);
        avg_waiting_time += process[i].waiting_time;
    }
    // cout<<endl;
    avg_waiting_time/=size;
    return avg_waiting_time;
}


int main(){

    int size=5;
    ProcessData processes[size];

    processes[0].burst_time = 10;
    processes[0].arrival_time = 0;
    processes[0].state=1;
    processes[0].id = 0;

    processes[1].burst_time = 1;
    processes[1].arrival_time = 0;
    processes[1].state=1;
    processes[1].id = 1;


    processes[2].burst_time = 15;
    processes[2].arrival_time = 0;
    processes[2].state=1;
    processes[2].id = 2;

    processes[3].burst_time = 6;
    processes[3].arrival_time = 0;
    processes[3].state=1;
    processes[3].id = 3;


    processes[4].burst_time = 4;
    processes[4].arrival_time = 0;
    processes[4].state=1;
    processes[4].id = 4;


    // printf("Average waiting time for FCFS: %.2f\n",FCFS(processes,size));
    // printf("Average waiting time for SJF: %.2f\n",SJF(processes,size));
    printf("Average waiting time for roundRobin: %.2f\n",roundRobin(processes,size,1));

    return 0;
}