/*
    Copyright (C) 2019 Rasmus Lindegaard
*/

#include "lottery.h"

#include "user.h"
#include "proc.h"

#define TICKET_COUNT 320
#define NPROC 64

struct priority_proc{

    struct proc* process;
    double priority;
};

struct{
    struct priority_proc procs[TICKET_COUNT];
    int last_index;
} tickets;



struct {
    struct priority_proc procs[NPROC];
} proc_ticket_priorities;



void build_heap(struct proc procs[], int length);
struct proc* extract(void);
int calc_left_child(int index);
int calc_right_child(int index);
int calc_parent(int index);
double random();
double get_proc_priority_weight(double priority);

double get_proc_priority_weight(double priority)
{
    double total = 0.0;
    for(int i = 0; i < NPROC; i++)
    {
        if(proc_ticket_priorities.procs[i].process->state == RUNNABLE)
        {
            total += proc_ticket_priorities.procs[i].priority;
        }
    }

    return (100 / total) * priority;
}

void assign_proc_priorities(struct proc procs[])
{
    static int call_counter = 0;

    for(int i = 0; i < NPROC; i++)
    {
        proc_ticket_priorities.procs[i].priority = 5;
        proc_ticket_priorities.procs[i].process = &procs[i];
    }
}

void build_heap(struct proc procs[], int length)
{
    

    for(int i = (TICKET_COUNT >> 1); i > 0; i--)
    {
        max_heapify(i);
    }
}

void max_heapify(int index)
{
    if(index < tickets.last_index)
    {
        int largest = index;
        int left_child = calc_left_child(index);
        int right_child = calc_right_child(index);

        if(left_child < tickets.last_index && tickets.procs[left_child].priority > tickets.procs[largest].priority)
        {
            largest = left_child;
        }

        if(right_child < tickets.last_index && tickets.procs[right_child].priority > tickets.procs[largest].priority)
        {
            largest = right_child;
        }

        if(index != largest)
        {
            struct priority_proc* temp = &(tickets.procs[largest]);

            tickets.procs[largest] = tickets.procs[index];
            tickets.procs[index] = *temp;
            max_heapify(largest);
        }
    }
}

struct proc* extract(void)
{
    struct proc* pri_one = tickets.procs[0].process;

    tickets.procs[0] = tickets.procs[tickets.last_index];
    tickets.last_index--;

    max_heapify(0);

    return pri_one;
}

int calc_left_child(int index)
{
    return (index << 1) + 1;
}

int calc_right_child(int index)
{
    return (index << 1) + 2;
}

int calc_parent(int index)
{
    if(index % 2 > 0)
    {
        index -= 1;
    }
    else
    {
        index -= 2;
    }
    
    return index >> 1;
}

double random()
{
    double result = uptime() / (uptime() << 2);
    result += ((uptime() % 17) * 0.314581) + ((uptime() << 3) / (uptime() * 0.0019453));
}

void lottery_scheduler()
{

}