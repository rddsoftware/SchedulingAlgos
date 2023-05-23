/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority.h
 * @author Rusty Dillard
 * @brief This Scheduler class implements the Priority scheduling algorithm.
 * @version 0.1
 */
// Remember to add sufficient and clear comments to your code


#ifndef ASSIGN3_SCHEDULER_PRIORITY_H
#define ASSIGN3_SCHEDULER_PRIORITY_H

#include <deque>
#include "scheduler.h"

class SchedulerPriority : public Scheduler {
private:
deque<PCB> priority_queue;
float avg_wait_time = 0;
float avg_turn_around = 0;
unsigned int queue_length = 0;

public:
/**
 * @brief Construct a new SchedulerPriority object
 */
SchedulerPriority();

/**
 * @brief Destroy the SchedulerPriority object
 */
~SchedulerPriority() override;

/**
 * @brief This function is called once before the simulation starts.
 *        It is used to initialize the scheduler.
 * @param process_list The list of processes in the simulation.
 */
void init(std::vector<PCB>& process_list) override;

/**
 * @brief This function is called once after the simulation ends.
 *        It is used to print out the results of the simulation.
 */
void print_results() override;

/**
 * @brief This function simulates the scheduling of processes in the ready queue.
 *        It stops when all processes are finished.
 */
void simulate() override;

/**
 * @brief This is an overloaded function to help with the sorting of the queue.
 * @param right: The contents of the right side of the "<" statement must be a PCB reference.
 */
bool operator<(const PCB& right) const;
};


#endif //ASSIGN3_SCHEDULER_PRIORITY_H
