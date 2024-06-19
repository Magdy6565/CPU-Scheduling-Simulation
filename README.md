CPU-Scheduling-Simulation
CPU scheduling simulation using java, Multilevel Feedback Queue implemented using 3 Queues using RR round Robbin algorithm and First Come First Serve (FCFS) algorithm.

Implementation:
---------------
Multilevel Feedback Queue:

Queue 1: RoundRobbin (RR), quantum = 8 .
Queue 2: RoundRobbin (RR), quantum = 16.
Queue 3: First Come First Serve (FCFS).
CPU will serve Queue 1 by 50%

CPU will serve Queue 2 by 30%

CPU will serve Queue 3 by 20%

Promotion or Demotion is done by randomness of 50%

Assumed CPU time = 160 (a number it's 50% is multiple of 8 and it's 30% is mul;tiple of 16)

I generate 100 random pocesses each has ID and burst time

------------------------------------------------------------------------------------------------------------------

