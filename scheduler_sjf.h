/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.h
 * @author Rusty Dillard
 * @brief This Scheduler class implements the SJF scheduling algorithm.
 * @version 0.1
 */
// Remember to add sufficient and clear comments to your code
#ifndef ASSIGN3_SCHEDULER_SJF_H
#define ASSIGN3_SCHEDULER_SJF_H

#include "scheduler.h"

class SchedulerSJF : public Scheduler
{
private:
    unsigned int queue_length = 0;
    float avg_wait_time = 0;
    float avg_turn_around = 0;
    vector<PCB> sjf_queue;

public:
    /**
    * @brief Construct a new SchedulerSJF object
    */
    SchedulerSJF();
    /**
    * @brief Destroy the SchedulerSJF object
    */
    ~SchedulerSJF() override;
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
    * @brief This is an overloaded function to help with the sorting of the sjf queue.
    * @param right: The contents of the right side of the "<" statement must be a PCB reference.
    */
    bool operator<(const PCB& right) const;
};
#endif //ASSIGN3_SCHEDULER_SJF_H
