#include <bits/stdc++.h>
using namespace std;
#define all(v) v.begin(),v.end()
#define enl "\n"

struct Process {
    int arrival_time,burst_time,completetion_time,turn_around_time,waiting_time,idx;

    Process() {}

    Process(int arrival_time,int burst_time,int idx) {
        this->arrival_time = arrival_time;
        this->burst_time = burst_time;
        this->idx = idx;
    }
};

int main() {
    
    int n;
    cin>>n;

    vector<Process>processes;
    for(int i=0;i<n;i++) {
        int arrival_time,burst_time;
        cin>>arrival_time>>burst_time;
        processes.push_back(Process(arrival_time,burst_time,i));
    }

    sort(all(processes),[&](Process &u,Process &v) {
        return u.arrival_time < v.arrival_time;
    });

    int tme = 1e9;
    queue<int>ready_queue;
    vector<bool>vis(n,0);

    for(auto u:processes) tme = min(tme,u.arrival_time);

    for(int i=0;i<n;i++) {
        if(processes[i].arrival_time == tme) {
            vis[i] = true;
            ready_queue.push(i);
        }
    }

    while(!ready_queue.empty()) {
        int i = ready_queue.front();
        ready_queue.pop();

        auto s = processes[i];

        s.completetion_time = tme + s.burst_time;
        s.turn_around_time = s.completetion_time - s.arrival_time;
        s.waiting_time = s.turn_around_time - s.burst_time;
        processes[i] = s;

        tme += s.burst_time;

        for(int i=0;i<n;i++) {
            if(!vis[i] and tme>=processes[i].arrival_time) {
                ready_queue.push(i);
                vis[i] = true;
            }
        }

        if(ready_queue.empty()) {
            for(int i=0;i<n;i++) {
                if(!vis[i]) tme = min(tme,processes[i].arrival_time);
            }

            for(int i=0;i<n;i++) {
                if(!vis[i] and tme == processes[i].arrival_time) {
                    vis[i] = true;
                    ready_queue.push(i);
                }
            }
        }
    }

    sort(all(processes),[&](Process &u,Process &v) {
        return u.idx < v.idx;
    });

    for(auto u:processes) {
        cout<<u.arrival_time<<' '<<u.burst_time<<' '<<u.completetion_time<<' '<<u.turn_around_time<<' '<<u.waiting_time<<"\n";
    }

    return 0;
}