﻿# UTBM-2019-SYSTEM_Round_robin_with_priority
 
 # Command # 


# Description #

This is to reproduce the behavior of the process scheduling algorithm seen in progress. This algorithm is based on the Round Robin with priorities model considering that each priority is associated with a turnstile. The flow of the algorithm is as follows: each process, identified by a unique number, has a priority of 1 to 10 (1 being considered the highest priority), a submission date and an execution time. The system then creates a turnstile by priority which corresponds for each priority to a waiting list containing the appropriate processes. During each quantum of time, a process of a certain priority is executed according to the CPU allocation table. If the priority of the next process to be executed is equivalent to the priority of the running process, the priority of the running process is lowered and the new process is processed. Consequently, the requisitioned process is inserted at the end of the turnstile corresponding to its new priority. If a target turnstile relative to the choice made is empty then the process of the turnstile of directly lower priority is elected. In the case where the priority 10 turnstile is chosen and it is empty, then the choice will relate to the priority 1 turnstile.
