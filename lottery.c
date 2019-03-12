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
    struct priority_proc procs[320];
    int last_index;
} tickets;



struct {
    struct priority_proc procs[NPROC];
} proc_priorities;



void build_heap(struct proc procs[], int length);
struct proc* extract(void);
int calc_left_child(int index);
int calc_right_child(int index);
int calc_parent(int index);
double random(double base, double bound);



void build_heap(struct proc procs[], int length)
{
    //Read init 

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
    return (index << 1) + 1
}
int calc_right_child(int index);
int calc_parent(int index);
double random(double base, double bound);

void lottery_scheduler()
{

}