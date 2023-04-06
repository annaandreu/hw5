#ifndef RECCHECK
#include <set>
//#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
//modeled after sudoku lab - check if valid, if not backtrack
bool schedule_helper(
	const AvailabilityMatrix& avail,
  const size_t dailyNeed,
  const size_t maxShifts,
  DailySchedule& sched,
  size_t curr_day,
  size_t curr_worker
);
  

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
    // Add your code below
    /*const size_t total_days = avail.size(); // n
    const size_t possible_workers = avail[0].size(); // k
	const size_t workers_needed = sched[0].size(); // d */

// SCHEDULE SOLUTION n x d
// make a vector with spots for as many workers needed and their id's
    std::vector<Worker_T> workers_needed(dailyNeed, INVALID_ID);
    // ^ for columns- how many workers needed
    
    // vector of vectors to indicating the d workers (col)
    //who are scheduled to work on each of the n days (rows)
    //for(unsigned int row = 0; row < avail.size(); row++){ // for loop in set up 
        // populate schedule based on how many workers needed each day
        //sched.push_back(workers_needed);
    //}
		sched.resize(avail.size(), workers_needed); 

	return schedule_helper(avail, dailyNeed, maxShifts, sched, 0, 0);
}

bool schedule_helper(
	const AvailabilityMatrix& avail,
  const size_t dailyNeed,
  const size_t maxShifts,
  DailySchedule& sched,
  size_t curr_day,
  size_t curr_worker
)
{
    //const size_t total_days = avail.size(); // n
    const size_t total_workers = avail[0].size(); // k
    //const size_t workers_needed = sched[0].size(); // d
    
    // BC end recursive cases - all complete
    if(curr_day == sched.size()){
        return true;
    }

		//iterate through all workers 
    for(size_t x= 0; x < total_workers; x++){ // one loop for recursive solution
			 // if worker on sched today already 
				if(avail[curr_day][x]){ 
            if(find(sched[curr_day].begin(), sched[curr_day].end(), x) != sched[curr_day].end()){
							continue; // if already scheduled- dont do anything
						}
				
				//else schedule worker 
				sched[curr_day][curr_worker] = x;
				//if that position is valid for this and next round

				size_t shift_count = 0;
				bool isValid = false; 
				//go through whole sched and note how many times 
				// current worker has been scheduled for
				for(size_t y = 0; y < sched.size(); y++){
					for(size_t z = 0; z < dailyNeed; z++){
						if(sched[y][z] == x) // x would be the curr worker id
						shift_count++;
					}
					}

				// if shift count is less than or equal to max shifts 
				if(shift_count <= maxShifts){
					isValid = true; 
				}
				
				if(isValid == true){
					if(curr_worker == dailyNeed - 1){ // if reach end of colum
						if(schedule_helper(avail, dailyNeed, maxShifts, sched, curr_day + 1, 0)){
							return true; 
						}
					}
					//if have space in the row- recurse to next worker 
					else{
						if(schedule_helper(avail, dailyNeed, maxShifts, sched, curr_day, curr_worker +1)){
							return true; 
						}
					}
				}
    }
		}
// not valid after trying all workers- set back to OG 
		sched[curr_day][curr_worker]= INVALID_ID;
		return false; 

}
