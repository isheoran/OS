#include <bits/stdc++.h>
using namespace std;

struct Process {
    int arrival_time,burst_time,completetion_time,turn_around_time,waiting_time,idx;

    Process() {}

    Process(int arrival_time,int burst_time,int idx) {
        this->arrival_time = arrival_time;
        this->burst_time = burst_time;
        this->idx = idx;
    }

    bool operator<(const Process &o) const {
        if(burst_time == o.burst_time) {
            return arrival_time > o.arrival_time;
        }
        
        return burst_time > o.burst_time;
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

    priority_queue<Process>q;
    vector<bool>vis(n,false);

    int tme = 1e9;
    
    for(auto &u:processes) {
        tme = min(tme,u.arrival_time);
    }

    for(int i=0;i<n;i++) {
        if(tme == processes[i].arrival_time) {
            q.push(processes[i]);
            vis[i] = true;
        }
    }

    while(!q.empty()) {
        auto s = q.top();
        q.pop();

        s.completetion_time = tme + s.burst_time;
        s.turn_around_time = s.completetion_time - s.arrival_time;
        s.waiting_time = s.turn_around_time - s.burst_time;
        processes[s.idx] = s;

        tme += s.burst_time;

        for(int i=0;i<n;i++) {
            if(!vis[i] and tme>=processes[i].arrival_time) {
                q.push(processes[i]);
                vis[i] = true;
            }
        }

        if(q.empty()) {
            for(int i=0;i<n;i++) {
                if(!vis[i]) tme = min(tme,processes[i].arrival_time);
            }

            for(int i=0;i<n;i++) {
                if(!vis[i] and tme == processes[i].arrival_time) {
                    vis[i] = true;
                    q.push(processes[i]);
                }
            }
        }
    }

    for(auto u:processes) {
        cout<<u.arrival_time<<' '<<u.burst_time<<' '<<u.completetion_time<<' '<<u.turn_around_time<<' '<<u.waiting_time<<"\n";
    }

    return 0;
}