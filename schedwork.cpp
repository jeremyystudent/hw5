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
bool scheduleWork(DailySchedule& sched, const size_t workerCount, const size_t maxShifts, const AvailabilityMatrix& avail);
bool checkShiftValid(const size_t workerCount, const size_t maxShifts, const DailySchedule& sched);

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
    
    sched = std::vector<std::vector<Worker_T>>(avail.size());
    for(int i = 0;i<avail.size();i++){
        std::vector<Worker_T> temp(dailyNeed);
        for(int j = 0;j<dailyNeed;j++){
            temp[j] = INVALID_ID;
        }
        sched[i] = temp;
    }

    return scheduleWork(sched, avail.size(), maxShifts, avail);


}

bool checkShiftValid(const size_t workerCount, const size_t maxShifts, const DailySchedule& sched){
    std::vector<int> counter(workerCount);
    for(int i = 0;i<workerCount;i++){counter[i] = 0;}
    for(int i = 0;i<sched.size();i++){
        std::vector<bool> dailyCounter(sched[0].size());
        for(int j = 0;j<sched[0].size();j++){dailyCounter[j] = false;}
        for(int j = 0;j<sched[i].size();j++){
            counter[sched[i][j]]++;
            if(dailyCounter[sched[i][j]]){return false;}
            dailyCounter[sched[i][j]] = true;
        }
    }
    for(int i = 0;i<workerCount;i++){
        if(counter[i] > maxShifts){return false;}
    }
    return true;
}

bool scheduleWork(DailySchedule& sched, const size_t workerCount, const size_t maxShifts, const AvailabilityMatrix& avail){
    for(int i = 0;i<sched.size();i++){
        for(int j = 0;j<sched[0].size();j++){
            if(sched[i][j] == INVALID_ID){
                for(int k = 0;k<workerCount;k++){
                    if(avail[i][k] == 1){
                        sched[i][j] = k;
                        if(scheduleWork(sched, workerCount, maxShifts, avail)){return true;}
                        sched[i][j] = INVALID_ID;
                        return false;
                    }
                }
            }
        }
    }
    return checkShiftValid(workerCount, maxShifts, sched, avail);
}