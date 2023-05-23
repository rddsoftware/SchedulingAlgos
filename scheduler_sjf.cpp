/**
* Assignment 3: CPU Scheduler
 * @file scheduler_sjf.cpp
 * @author Rusty Dillard
 * @brief This Scheduler class implements the SJF scheduling algorithm.
 * @version 0.1
 */
// Remember to add sufficient and clear comments to your code
#include <iostream>
#include <algorithm>	//	Needed for the stl sort algorithm for vectors
#include "scheduler_sjf.h"

using namespace std;

SchedulerSJF::SchedulerSJF() { }

SchedulerSJF::~SchedulerSJF() { }

void SchedulerSJF::init(std::vector<PCB>& process_list)
{
	//	Copy the contents of the raw process list into the class's sjf_queue container
	copy(process_list.begin(), process_list.end(), back_inserter(sjf_queue));

	//	Set the wait times for each PCB to 0 and update the size of the queue
	for (PCB p : sjf_queue)
	{
		p.wait_time = 0;
		queue_length++;
	}
}

void SchedulerSJF::print_results()
{
	unsigned int total_wait_time = 0;
	unsigned int total_turn_around = 0;
	vector<PCB> temp_list;

	//	Copy the sjf queue's contents into a temporary vector and sort the temp_list by burst time using the overloaded operator<
	copy(sjf_queue.begin(), sjf_queue.end(), back_inserter(temp_list));
	sort(temp_list.begin(), temp_list.end());
	
	//	This loop calculates the amount of wait and turn-around time for each process (p1) by comparing the names of p1 and p2 until they match
	for (PCB p1 : sjf_queue)
	{
		//	Initialize the wait time for each new process in the sjf queue
		unsigned int wait_time = 0;
		for (PCB p2 : temp_list)
		{
			//	If the names are different, add p2's wait time to the current running wait time
			if (p1.name != p2.name)
			{
				wait_time += p2.burst_time;
			}
	
			//	When the names match, set p1's wait and turn-around times, update the running totals, and display the results of each process when completed
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

	//	Calculate and print the average wait and turn-around times and display them
	avg_wait_time = (float) total_wait_time / queue_length;
	avg_turn_around = (float) total_turn_around / queue_length;
	cout << "Average turn-around time = " << avg_turn_around << ", Average waiting time = " << avg_wait_time << endl;
}

void SchedulerSJF::simulate()
{
	//	Copy the sjf queue's contents into a temporary vector and sort the temp_list by burst time using the overloaded operator<
	vector<PCB> temp_list;
	copy(sjf_queue.begin(), sjf_queue.end(), back_inserter(temp_list));
	sort(temp_list.begin(), temp_list.end());
	
	//	Run the simulation
	for (PCB p : temp_list)
	{
		cout << "Running process " << p.name << " for " << p.burst_time << " time units\n";
	}
}

bool PCB::operator<(const PCB& right) const
{
	//	This is to prevent the sorting algorithm from changing the positions of two PCBs with the same burst times
	if (this->burst_time != right.burst_time)
	{
		return this->burst_time < right.burst_time;
	}
	return false;
}