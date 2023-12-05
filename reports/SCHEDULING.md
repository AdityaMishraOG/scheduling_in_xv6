# FCFS

## finding the right process

- Acquire the lock for each process.
- Check if the process is RUNNABLE.
- If execute_flag is unset, select the current process.
- If execute_flag is set, select the process with the earliest creation time (ctime).
- Release the lock for the current process.

## run the selected process

- Acquire the lock for the chosen process.
- Set its state to RUNNING.
- Update the CPU context for execution.
- Release the lock after execution.

## average running time and waiting time

- Average rtime 14, wtime 128

---

# MLFQ

## priority boost (proc.c)

- We go through all processes and see which processes have waited for longer than the max wait time.
- Those processes are added to a queue with one higher priority

## finding the right process (proc.c)

- Loop through processes
- Check if the process is RUNNABLE.
- If execute_flag is unset, select the current process.
- If execute_flag is set, select the process with the higher priority.
  - If the two processes have the same priority, then go select the process with the higher wait time.

## run the selected process (proc.c)

- Acquire the lock for the chosen process.
- Set its state to RUNNING.
- Update the CPU context for execution.
- Release the lock after execution.

## priority reduction (trap.c)

- Check how long the process has run until now.
- Depending on how long it has run, it is demoted to a new queue, or it stays at its current queue.
- The longer it has run, the lower is its priority.

## average running time and waiting time

- Average rtime 14, wtime 128

---

# RR

## finding the right process

- Acquire the lock for each process.
- Loop through processes.
- Check if the process is RUNNABLE.
- If it is RUNNABLE, select this process.
- Else release the lock and carry on with the loop.

## run the selected process (proc.c)

- Set its state to RUNNING.
- Update the CPU context for execution.
- Release the lock after execution.

## average running time and waiting time

- Average rtime 13, wtime 127
