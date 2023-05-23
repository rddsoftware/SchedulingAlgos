// /**
// * Assignment 3: CPU Scheduler
//  * @file scheduler_rr.h
//  * @author Rusty Dillard
//  * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
//  * @version 0.1
//  */
// // Remember to add sufficient and clear comments to your code
// //

#include "scheduler_rr.h"
#include <iostream>

using namespace std;

SchedulerRR::SchedulerRR(int time_quantum) { this->time_quantum = time_quantum; }

SchedulerRR::~SchedulerRR() { }

void SchedulerRR::init(std::vector<PCB>& process_list) {
    // Initialize the round-robin queue with processes from the process_list
    for (const auto& process : process_list) {
        rr.push(process);
    }
}

void SchedulerRR::print_results() {
    // Print the results of the simulation, such as average waiting time, average turnaround time, etc.
	for (PCB p : post_algo_vec)
	{
		cout << p.name << " turn-around time = " << p.turn_around_time << endl;
	}
    cout << "Average waiting time = " << avg_wait_time << ", Average turnaround time = " << avg_turn_around << endl;
}

void SchedulerRR::simulate() {
    // Implement the round-robin scheduling algorithm
    int time = 0;
    float total_wait_time = 0;
    float total_turnaround_time = 0;
    int finished_process_count = 0;

    //  This is the main loop of the round robin algorithm, that will run until all PCB burst times equal 0, after which, the PCB is popped off the rr, rendering the rr queue empty
    while (!rr.empty())
    {
        //  Store and pop the front PCB in the rr
        PCB current_process = rr.front();
        rr.pop();

        //  Calculate waiting time for the current process
        unsigned int wait_time = time - current_process.arrival_time;
        total_wait_time += wait_time;

        //  When the current PCB's burst time is lower than the time quantum, display the simulation under that circumstance, update the burst and turn around times, and push the process into the resulting vector
        if (current_process.burst_time <= time_quantum) 
        {
			cout << "Running process " << current_process.name << " for " << current_process.burst_time << " time units " << endl;
            time += current_process.burst_time;
            current_process.burst_time = 0;
            total_turnaround_time += time;
			current_process.turn_around_time = total_turnaround_time;
            finished_process_count++;
			post_algo_vec.push_back(current_process);
        } 
        
        //  When the burst time remaining is greater than the time quantum, display the simulation, update the burst and arrival times, and push the PCB into the back of the rr queue
        else 
        {
			cout << "Running process " << current_process.name << " for " << time_quantum << " time units " << endl;
            time += time_quantum;
            current_process.burst_time -= time_quantum;
            current_process.arrival_time = time;
            rr.push(current_process);
        }
    }

    //  Calculate the average wait and turn-around times
    avg_wait_time = total_wait_time / finished_process_count;
    avg_turn_around = total_turnaround_time / finished_process_count;
}

//  Unused operator< (necessary for compilation)
bool PCB::operator<(const PCB& right) const { return true; }
