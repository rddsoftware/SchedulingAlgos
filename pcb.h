/**
 * Assignment 1: priority queue of processes
 * @file pcb.h
 * @author Rusty Dillard
 * @brief This is the header file for the PCB class, a process control block.
 * @version 0.1
 */
// Remember to addPCB sufficient comments to your code

#pragma once
#include <iostream>
#include <string>
using namespace std;

/**
 * @brief A process control block (PCB) Process control block(PCB) is a data structure representing a process in the system.
 *       It contains the following fields:
 *       - process ID (PID)
 *       - process name
 *       - burst time
 *       - priority
 *      You may add more fields if you need.
 */
class PCB {
public:
	// Name of the process
	string name;
	// The unique process ID
	unsigned int id;
	// The priority of a process. Larger number represents higher priority
	unsigned int priority;
	// The CPU burst time of the process
	unsigned int burst_time;
	// The arrival time of the process
	unsigned int arrival_time;
	// The wait time of an individual process.
	unsigned int wait_time;
	// The turn-around time of an individual process.
	unsigned int turn_around_time;

	/**
	* @brief Construct a new PCB object
	* @param id: each process has a unique ID
	* @param priority: the priority of the process in the range 1-50. Larger number represents higher priority
	* @param state the state of the process.
	*/
	PCB(string name, unsigned int id = 0, unsigned int priority = 1, unsigned int burst_time = 0)
	{
		this->id = id;
		this->name = name;
		this->priority = priority;
		this->burst_time = burst_time;
		this->arrival_time = 0;
		this->wait_time = 0;
		this->turn_around_time = 0;
	}

	/**
	* @brief Destroy the PCB object.
	*
	*/
	~PCB() {}

	/**
	* @brief Print the PCB object.
	*/
	void print()
	{
		cout << "Process " << id << ": " << name << " has priority " << priority << " and burst time " << burst_time << endl;
	}

	/**
	 * @brief This is a setter for the wait time of a PCB
	 * @param wait_time: The wait time to be stored in the PCB's wait_time variable
	 */
	void set_wait_time(unsigned int wait_time) { this->wait_time = wait_time; }

	/**
	 * @brief This is a setter for the turn-around time of a PCB
	 * @param turn_around: The turn-around time to be stored in the PCB's turn_around_time variable
	 */
	void set_turn_around(unsigned int turn_around) { this->turn_around_time = turn_around; }

	/**
	 * @brief This is an operator< overloader to be used by the SJF and priority algorithms
	 * @param right: The contents of the right side of the "<" statement must be a reference to PCB reference
	 */
	virtual bool operator<(const PCB& right) const;
};