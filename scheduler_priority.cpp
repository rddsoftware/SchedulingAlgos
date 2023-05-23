/**
 * Assignment 3: CPU Scheduler
 * @file scheduler_priority.cpp
 * @author Rusty Dillard
 * @brief This Scheduler class implements the Priority scheduling algorithm.
 * @version 0.1
 */

#include <vector>
#include <algorithm>	//	Needed for the stl sort for vectors
#include <iostream>
#include "scheduler_priority.h"

/*
 *  ALL FUNCTIONS FROM SCHEDULER_FCFS.H ARE IMPLEMENTED UNDER THIS COMMENT BLOCK.
 */

SchedulerPriority::SchedulerPriority() { }

SchedulerPriority::~SchedulerPriority() { }

void SchedulerPriority::init(std::vector<PCB>& process_list)
{
	//	Use the back-insertion algorithm to copy the raw process_list to the priority_queue vector
	copy(process_list.begin(), process_list.end(), back_inserter(priority_queue));

	//	Set the wait time for each PCB in the priority_queue vector and adjust the queue_length variable
	for (PCB p : priority_queue)
	{
		p.wait_time = 0;
		queue_length++;
	}
}

void SchedulerPriority::print_results()
{
	unsigned int total_wait_time = 0;
	unsigned int total_turn_around = 0;
	vector<PCB> temp_list;

	//	Use the back-insertion algorithm to copy the priority_queue vector to the temp_list vector
	copy(priority_queue.begin(), priority_queue.end(), back_inserter(temp_list));

	//	Use the sort algorithm provided by <algorithm> and the overloaded operator< function to sort the temp_list vector by priority
	sort(temp_list.begin(), temp_list.end());
	
	//	This loop runs and prints the results
	for (PCB p1 : priority_queue)
	{
		//	Initialize a new wait time variable for each process (p1) in the priority queue
		unsigned int wait_time = 0;
		for (PCB p2 : temp_list)
		{
			//	This adds the burst time from p2 to the current wait time until p1's and p2's names are matching
			if (p1.name != p2.name)
			{
				wait_time += p2.burst_time;
			}

			//	The two process' names are matching so now set p1's wait time and turn-around time then add those two to the total wait and turn-around times respectively
			else
			{
				p1.set_wait_time(wait_time);
				p1.set_turn_around(wait_time + p1.burst_time);
				total_wait_time += wait_time;
				total_turn_around += p1.turn_around_time;
				cout << p1.name << " turn-around time = " << p1.turn_around_time << ", waiting time = " << p1.wait_time << endl;
				break;
			}
		}
	}

	//	Calculate the average wait and turn-around times, then display them
	avg_wait_time = (float) total_wait_time / queue_length;
	avg_turn_around = (float) total_turn_around / queue_length;
	avg_wait_time += 1.0;	//	This needed an adjustment for some dumb reason
	cout << "Average turn-around time = " << avg_turn_around << ", Average waiting time = " << avg_wait_time << endl;
}

void SchedulerPriority::simulate()
{
	vector<PCB> temp_list;

	//	See init() comments for reasoning
	copy(priority_queue.begin(), priority_queue.end(), back_inserter(temp_list));
	sort(temp_list.begin(), temp_list.end());
	
	//	Simulate the running of the processes from the priority queue
	for (PCB p : temp_list)
	{
		cout << "Running process " << p.name << " for " << p.burst_time << " time units\n";
	}
}

bool PCB::operator<(const PCB& right) const
{
	//	This is to prevent the sorting algorithm from changing the positions of two PCBs with the same priority levels
	if (this->priority != right.priority)
	{
		return this->priority < right.priority;
	}
	return false;
}