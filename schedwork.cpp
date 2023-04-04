#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleWork(DailySchedule& sched, vector<int>& shiftCounter, const size_t maxShifts, const AvailabilityMatrix& avail, pair<int,int> curr);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    
    if(dailyNeed*avail.size() > maxShifts*avail[0].size()){return false;}
    vector<int> shiftCounter(avail[0].size());
    
    sched = std::vector<std::vector<Worker_T>>(avail.size());
    for(int i = 0;i<avail.size();i++){
        std::vector<Worker_T> temp(dailyNeed);
        for(int j = 0;j<dailyNeed;j++){
            temp[j] = INVALID_ID;
            shiftCounter[j] = 0;
        }
        sched[i] = temp;
    }

    return scheduleWork(sched, shiftCounter, maxShifts, avail, make_pair<int,int>(0,0));


}
  
bool scheduleWork(DailySchedule& sched, vector<int>& shiftCounter, const size_t maxShifts, const AvailabilityMatrix& avail, pair<int,int> curr){
    for(int k = 0;k<avail[0].size();k++){
        if(avail[curr.first][k] == 1 && find(sched[curr.first].begin(), sched[curr.first].end(), k) == sched[curr.first].end()){
            sched[curr.first][curr.second] = k;
            shiftCounter[k]++;
            if(shiftCounter[k] <= maxShifts){
                if(scheduleWork(sched, shiftCounter, maxShifts, avail, make_pair<int,int>(curr.first + curr.second/avail[0].size(),(curr.second+1)%avail[0].size()))){return true;}   
            }
            shiftCounter[k]--;
        }
    }
    sched[curr.first][curr.second] = INVALID_ID;
    return false;
}

