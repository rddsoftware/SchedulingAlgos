/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.cpp
 * @author Rusty Dillard
 * @brief This Scheduler class implements the FCSF scheduling algorithm.
 * @version 0.1
 */
// Remember to add sufficient and clear comments to your code
#include <iostream>
#include "scheduler_fcfs.h"

using namespace std;

/*
 *  ALL FUNCTIONS FROM SCHEDULER_FCFS.H ARE IMPLEMENTED UNDER THIS COMMENT BLOCK.
 */

SchedulerFCFS::SchedulerFCFS() { }

SchedulerFCFS::~SchedulerFCFS() { }

void SchedulerFCFS::init(std::vector<PCB>& process_list)
{
	//	Use the back-insertion algorithm to copy the raw process_list to the fcfs_queue vector
	copy(process_list.begin(), process_list.end(), back_inserter(fcfs_queue));
	queue_length = fcfs_queue.size();
}

void SchedulerFCFS::print_results()
{
    unsigned int wait_time = 0;
    unsigned int turn_around_time = 0;
	unsigned int total_wait = 0;
	unsigned int total_turn_around = 0;
	unsigned int process_num = 0;
	
	//	This loop displays the resulting fcfs_queue vector
    for (PCB p : fcfs_queue)
    {
		//	Add the burst time of the current PCB to the total turn around time
        turn_around_time += p.burst_time;

        cout << p.name << " turn-around time = " << turn_around_time;
        cout << ", waiting time = " << wait_time << endl;

		//	Add the burst time to the current wait time
        wait_time += p.burst_time;

		//	Only add wait time's for the first n-1 PCBs to the total wait time
		if (process_num < queue_length - 1)
		{
			total_wait += wait_time;
		}

		//	add the current turn around time to the total turn around time
		total_turn_around += turn_around_time;
		process_num++;
    }

	//	Calculate the average wait time and average turn around time
	avg_wait = (float) total_wait / queue_length;
	avg_turn_around = (float) total_turn_around / queue_length;
	cout << "Average turn-around time = " << avg_turn_around << ", Average waiting time = " << avg_wait << endl;
}

void SchedulerFCFS::simulate()
{
	//	This loop displays the simulation of the FCFS scheduling algorithm
    for (PCB p : fcfs_queue)
    {
        cout << "Running Process " << p.name;
        cout << " for " << p.burst_time << " time units" << endl;
    }
}

//	This isn't used in this file, but it needed an implementation.
bool PCB::operator<(const PCB& right) const
{
    return true;
}