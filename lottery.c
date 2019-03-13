/*
    Copyright (C) 2019 Rasmus Lindegaard
*/

#include "lottery.h"

#include "user.h"
#include "proc.h"

#define TICKET_COUNT 320
#define NPROC 64

/*
    Structs and stuff
*/

static int recount_total = 1;

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



/*
    Prototypes
*/

void build_heap();
void check_or_reset(void);
struct proc* extract(void);
int calc_left_child(int index);
int calc_right_child(int index);
int calc_parent(int index);
int get_number_of_tickets(double percentage);
double random();
double get_proc_priority_weight(double priority);


/*
    Functions
*/

void assign_proc_priorities(struct proc procs[])
{
    for(int i = 0; i < NPROC; i++)
    {
        proc_ticket_priorities.procs[i].priority = 5;
        proc_ticket_priorities.procs[i].process = &procs[i];
    }

    tickets.last_index = -1;
}

void build_heap()
{
    for(int i = 0; i < NPROC; i++)
    {
        if(proc_ticket_priorities.procs[i].process->state == RUNNABLE)
        {
            int proc_ticket_percentage = get_proc_priority_weight(proc_ticket_priorities.procs[i].priority);
            int proc_ticket_number = get_number_of_tickets(proc_ticket_percentage);
            for(int j = 0; j < proc_ticket_number; j++)
            {
                tickets.last_index++;
                tickets.procs[tickets.last_index].priority = random();
                tickets.procs[tickets.last_index].process = proc_ticket_priorities.procs[i].process;
            }
        }
    }

    for(int i = (TICKET_COUNT >> 1); i > 0; i--)
    {
        max_heapify(i);
    }
}

double get_proc_priority_weight(double priority)
{
    static double total = 0.0;
    if(recount_total == 1)
    {
        for(int i = 0; i < NPROC; i++)
        {
            if(proc_ticket_priorities.procs[i].process->state == RUNNABLE)
            {
                total += proc_ticket_priorities.procs[i].priority;
            }
        }
        recount_total = 0;
    }

    return (100 / total) * priority;
}

void reset_proc_priorities()
{
    for(int i = 0; i < NPROC; i++)
    {
        proc_ticket_priorities.procs[i].priority = 5;
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

void check_or_reset(void)
{
    static int cycle_counter = 0;
    if(tickets.last_index < 0)
    {
        if(cycle_counter > 5)
        {
            reset_proc_priorities();
        }

        build_heap();
        cycle_counter++;
    }
}

struct proc* extract(void)
{
    check_or_reset();

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
    static int seed = 0;
    if(seed == 0)
    {
        seed = uptime();
    }

    double result = seed / (seed << 2);

    result += (seed % 17) * 0.314581;
    result += (seed << 3) / (uptime() * 0.0019453);

    seed = uptime() * (result * 0.0043);

    return result;
}

int get_number_of_tickets(double percentage)
{
    return 3.2 * percentage;
}
