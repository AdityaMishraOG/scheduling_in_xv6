# xv6
# Examining the Efficacy of Static Priority (SP) and Recent Behaviour Index (RBI)

## Static Priority (SP):

- SP signifies the initial priority assigned to a process, inversely proportional to its value (lower SP indicates higher priority).
- Processes with lower SP values are endowed with higher DP values, increasing their likelihood of execution.
- The adaptability of SP is demonstrated through the `set_priority` system call, allowing real-time adjustments during execution.

## Recent Behaviour Index (RBI):

- RBI draws influence from three key components: Running Time (RTime), Sleeping Time (STime), and Waiting Time (WTime).
- The RBI formula, which ensures a non-negative outcome, considers recent behavior by weighting RTime and penalizing excessive STime and WTime.
- This index encapsulates a process's recent history, reflecting both activity and responsiveness.

## Dynamic Priority (DP):

- DP emerges as the sum of SP and RBI, offering a holistic measure of a process's priority.
- Higher DP values indicate increased priority, shaping the likelihood of a process being scheduled for execution.
- The interplay between SP and RBI in DP underscores the system's nuanced approach to prioritizing processes.

## Observations on Multiple Processes Scheduling:

### Initial Priority (SP):

- Lower SP values confer an immediate advantage, emphasizing initial priorities.
- The flexibility to dynamically adjust SP through `set_priority` enables responsive changes during execution.
- Processes with lower SP or those subject to dynamic adjustments may outpace those with higher SP values.

### Recent Behaviour Index (RBI):

- RBI captures recent behavior, favoring processes with higher activity levels and less idle time.
- This index, factored into DP, elevates the significance of recent actions, steering the scheduler toward processes that exhibit greater recent activity.

### Dynamic Priority (DP):

- DP, as the amalgamation of SP and RBI, becomes the pivotal factor in scheduling decisions.
- Lower SP values or higher RBI values propel processes to higher DP, shaping their prominence in the scheduling queue.

### Impact on Scheduling:

- Processes with lower DP values ascend in the scheduling hierarchy, with ties resolved based on Running Time and start time.
- The system's adaptability to changes in SP and dynamic behavior metrics (RTime, STime, WTime) influences the scheduling order, ensuring responsiveness to evolving process conditions.

### Balancing Priority:

- The synergy between SP and RBI engenders a balanced approach to priority management.
- The scheduler accommodates shifts in process behavior or priority adjustments, fostering adaptability and fairness in the scheduling process.
## Testing and Results

- *Test Environment:*
  - Tested using 2 CPU.

- *PBS Results:*
    - Average rtime 9,  wtime 123
