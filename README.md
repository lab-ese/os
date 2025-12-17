# Operating System Lab Programs

Complete collection of 28 OS lab programs for exam preparation.

## 📚 Program List

### Shell Scripts (1-9)
1. **Palindrome Checker** - Check if a string is palindrome
2. **Linux Commands** - Study guide for common Linux commands
3. **Bubble Sort** - Sorting using bubble sort algorithm
4. **Student Report (AWK)** - Generate student result reports
5. **Substring Occurrence** - Find substring occurrences and positions
6. **Selection Sort** - Sorting using selection sort algorithm
7. **Insertion Sort** - Sorting using insertion sort algorithm
8. **Arithmetic Operations** - Calculator with case statement
9. **Database Operations** - CRUD operations on flat file

### CPU Scheduling Algorithms with Gantt Charts (10-15)
10. **FCFS** - First Come First Serve scheduling
11. **SJF Non-Preemptive** - Shortest Job First (NP)
12. **SJF Preemptive** - Shortest Remaining Time First (SRTF)
13. **Round Robin** - Time quantum-based scheduling
14. **Priority Non-Preemptive** - Priority-based scheduling (NP)
15. **Priority Preemptive** - Priority-based scheduling (P)

### Synchronization Problems (16-21)
16. **Producer-Consumer (Semaphore)** - Using semaphores
17. **Producer-Consumer (Mutex)** - Using mutex
18. **Reader-Writer (Semaphore)** - Using semaphores
19. **Reader-Writer (Mutex)** - Using mutex
20. **Dining Philosophers (Semaphore)** - Using semaphores
21. **Dining Philosophers (Mutex)** - Using mutex

### Deadlock & Memory Management (22-25)
22. **Banker's Algorithm** - Deadlock avoidance with safe sequence
23. **FIFO Page Replacement** - First In First Out
24. **LRU Page Replacement** - Least Recently Used
25. **Optimal Page Replacement** - Optimal algorithm

### Disk & Real-Time Scheduling (26-28)
26. **FCFS Disk Scheduling** - First Come First Serve for disk
27. **Earliest Deadline First** - EDF real-time scheduling
28. **RMS & LLF** - Rate Monotonic & Least Laxity First

## 🔧 Compilation & Execution

### Shell Scripts (.sh)
```bash
chmod +x script.sh
./script.sh
```

### AWK Programs (.awk)
```bash
awk -f program.awk input.txt
# OR
chmod +x program.awk
./program.awk input.txt
```

### C Programs (.c)
```bash
# For regular programs
gcc program.c -o program
./program

# For programs using pthread
gcc program.c -o program -lpthread
./program
```

## 📝 Key Features

### CPU Scheduling Programs Include:
- ✅ Gantt Chart visualization
- ✅ Average waiting time calculation
- ✅ Average turnaround time calculation
- ✅ Detailed process information

### Synchronization Programs Include:
- ✅ Deadlock prevention mechanisms
- ✅ Thread-safe implementations
- ✅ Clear output showing synchronization

### Page Replacement Programs Include:
- ✅ Page fault counting
- ✅ Hit ratio calculation
- ✅ Frame status visualization

## 🎯 Exam Tips

1. **Understand the algorithms** - Don't just memorize code
2. **Practice Gantt charts** - Draw them manually for CPU scheduling
3. **Know time complexities** - Important for viva
4. **Deadlock conditions** - Mutual exclusion, hold & wait, no preemption, circular wait
5. **Page replacement comparison** - FIFO vs LRU vs Optimal

## 📖 Important Concepts

### CPU Scheduling
- **FCFS**: Simple but can cause convoy effect
- **SJF**: Optimal for minimum average waiting time
- **Round Robin**: Fair scheduling with time quantum
- **Priority**: Can cause starvation (solved by aging)

### Synchronization
- **Semaphore**: Integer variable for synchronization
- **Mutex**: Binary lock for mutual exclusion
- **Critical Section**: Code that accesses shared resources

### Memory Management
- **Banker's Algorithm**: Avoids deadlock by checking safe state
- **Page Replacement**: Decides which page to remove when memory is full

## 🚀 Quick Start

```bash
# Clone repository
git clone <repository-url>
cd os

# Run a shell script
chmod +x 01_palindrome.sh
./01_palindrome.sh

# Compile and run C program
gcc 10_fcfs.c -o fcfs
./fcfs

# Compile and run threading program
gcc 16_producer_consumer_semaphore.c -o pc -lpthread
./pc
```

## 📌 Notes

- All C programs with threading require `-lpthread` flag
- Shell scripts need execute permission (`chmod +x`)
- AWK program includes sample data file
- Test with different inputs to understand behavior

## 🎓 Author

Created for Operating System Lab Exam preparation

## 📄 License

Free to use for educational purposes

---

**Good luck with your exams! 🎉**
