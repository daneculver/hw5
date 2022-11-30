#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool buildSchedule(size_t rows, size_t columns, size_t count, size_t need, vector<size_t> shifts, 
	const AvailabilityMatrix& avail, DailySchedule& sched);
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
		//Add code below
		//creates a vector using the amount of shifts
	vector<size_t> shifts(avail[0].size(), 0);
    //creates a schedule
	vector<Worker_T> vec(dailyNeed);
	DailySchedule tempsched(avail.size(), vec);
	//recursively builds the schedule
	bool answer = buildSchedule(0, 0, maxShifts, dailyNeed, shifts, avail, tempsched);
	sched = tempsched;
	return  answer;
}
bool buildSchedule(size_t rows, size_t columns, size_t count, size_t need, vector<size_t> shifts, 
	const AvailabilityMatrix& avail, DailySchedule& sched){
	//base case that check if it has reached end.
	if(rows == avail.size()){
		return true;
	}
	else{
		for(size_t x = 0; x < avail[0].size(); x++){
			//checks availability of the person
			if(avail[rows][x] == 1){
				//conditional to check if max was reached
				if(count == shifts[x]){
				    continue;
				}
				//increases number of shifts and adds to schedule
				sched[rows][columns] = x;
				shifts[x]++;
				//fills the rest of schedule
				size_t columnSize = (columns+1) % sched[0].size();
				size_t rowSize = rows+(columns+1)/sched[0].size();
				bool tempBool = buildSchedule(rowSize, columnSize, count, need, shifts, avail, sched);
				//returns true if they are scheduled correctly
				if(tempBool == true){
				    return true;
				}
				//removes schedule and shifts
				shifts[x]--;
				sched[rows][columns] = 0;
			}
		}		
	}
	return false;
}
