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
bool scheduleWork(DailySchedule& sched, vector<int>& shiftCounter, const size_t maxShifts, const AvailabilityMatrix& avail);

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
    vector<int> shiftCounter(sched[0].size());
    
    sched = std::vector<std::vector<Worker_T>>(avail.size());
    for(int i = 0;i<avail.size();i++){
        std::vector<Worker_T> temp(dailyNeed);
        for(int j = 0;j<dailyNeed;j++){
            temp[j] = INVALID_ID;
            shiftCounter[j] = 0;
        }
        sched[i] = temp;
    }

    return scheduleWork(sched, shiftCounter, maxShifts, avail);


}
  
bool scheduleWork(DailySchedule& sched, vector<int>& shiftCounter, const size_t maxShifts, const AvailabilityMatrix& avail){
    for(int i = 0;i<sched.size();i++){
        for(int j = 0;j<sched[0].size();j++){
            if(sched[i][j] == INVALID_ID){
                for(int k = 0;k<avail[0].size();k++){
                    if(avail[i][k] == 1 && find(sched[i].begin(), sched[i].end(), k) == sched[i].end()){
                        sched[i][j] = k;
                        shiftCounter[k]++;
                        if(shiftCounter[k] <= maxShifts){
                         if(scheduleWork(sched, shiftCounter, maxShifts, avail)){return true;}   
                        }
                        shiftCounter[k]--;
                    }
                }
                sched[i][j] = INVALID_ID;
                return false;
            }
        }
    }
    return true;
}

