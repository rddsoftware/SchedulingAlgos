/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority_rr.cpp
 * @author Rusty Dillard
 * @brief This Scheduler class implements the Priority RR scheduling algorithm.
 * @version 0.1
 */
// Remember to add sufficient and clear comments to your code

#include "scheduler_priority_rr.h"
using namespace std;

SchedulerPriorityRR::SchedulerPriorityRR(int time_quantum) { this->time_quantum = time_quantum; }

SchedulerPriorityRR::~SchedulerPriorityRR() { }

void SchedulerPriorityRR::init(std::vector<PCB>& process_list) 
{
	//	Since this implementation is using pointers, the raw process list can be copied using the operator=
    init_proc_list = process_list;

	//	Update the number of PCBs in the priority round robin queue 
	process_total = process_list.size();
	
	//	The processes queue is meant to be used as the global temporary container for the PCBs and the individual PCBs are only erased after the given PCB has reached 0 burst time
    for (PCB& p : process_list) 
	{
        processes.push_back(&p);
    }
}

void SchedulerPriorityRR::simulate() 
{
    int elapsed_time = 0;
    int finished_processes = 0;
	
	//	This is the main loop that drives the priority rr simulation and runs until the number of finished processes matches the number of total processes
    while (finished_processes < process_total) 
	{
		//	
        for (unsigned int priority = 20; priority >= 0; priority--) 
		{
			if (priority == 0)
			{
				break;
			}

			//	Each priority level get its own queue container and will run this container through the round robin algorithm until it's empty
			vector<PCB*> current_priority;

			//	This loop pushes the processes p that match the current priority level into the current priority vector
			for (PCB* p : processes)
			{
				if (p->priority == priority)
				{
					current_priority.push_back(p);
				}
			}

			//	This loop run the round robin on the current priority level vector that was constructed previously until it is empty
			while(!current_priority.empty())
			{

				//	This loop iterates through the current priority vector from begin to end
	            for (auto iter = current_priority.begin(); iter != current_priority.end(); iter++) 
				{
					//	Creates a PCB pointer called "current process" for easier visualization of the code
	                PCB* current_process = *iter;

					//	Determine and display which number will be subtracted from the burst time of the current process (minimum of given PCB's burst time and the time quantum)
					int time_to_execute = std::min(current_process->burst_time, static_cast<unsigned int>(time_quantum));
					cout << "Running process " << current_process->name << " for " << time_to_execute << " time units"<< endl;

					//	Subtract the time determination from the current PCB's burst time and add the time determination to the total elapsed time
					current_process->burst_time -= time_to_execute;
					elapsed_time += time_to_execute;

					//	When the current PCB's burst time reaches 0, increment the number of finished processes, update the average wait and turn-around times, and erase the PCB from the current priority's rr queue
					if (current_process->burst_time == 0)
					{
						finished_processes++;
						avg_wait_time += elapsed_time - init_proc_list[current_process->id].burst_time;
						avg_turn_around += elapsed_time;
						current_priority.erase(iter);
						break;
					}
	            }
			}

			//	Clear out the pointers in the current priority's rr queue
			for (auto iter = current_priority.begin(); iter != current_priority.end(); iter--)
			{
				current_priority.erase(iter);
			}
        }
    }


	//	Calculate the average wait and turn-around times respectively
    avg_wait_time /= process_total;
    avg_turn_around /= process_total;
}

void SchedulerPriorityRR::print_results() 
{
	//	Dispplay the average wait and turn-around times respectively
    cout << "Average turn-around time = " << avg_turn_around << ", Average waiting time = " << avg_wait_time << endl;
}

bool PCB::operator<(const PCB& right) const
{
	//	This is to prevent the sorting algorithm from changing the positions of two PCBs with the same priority levels
	if (this->priority != right.priority)
		return this->priority < right.priority;
	return false;
}