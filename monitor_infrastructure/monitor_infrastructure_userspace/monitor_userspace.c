





#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

// Sched for affinity macros
#define  __USE_GNU
//#include <sched.h>

#include <sched.h>
#include <unistd.h>
#include <string.h>

#include <sys/syscall.h>
#include <pthread.h>

#include <sys/wait.h> //for wait()

#define CPU_SETSIZE 1024
#define __NCPUBITS  (8 * sizeof (unsigned long))
typedef struct
{
   unsigned long __bits[CPU_SETSIZE / __NCPUBITS];
} cpu_set_t;

#define CPU_SET(cpu, cpusetp) \
  ((cpusetp)->__bits[(cpu)/__NCPUBITS] |= (1UL << ((cpu) % __NCPUBITS)))
#define CPU_ZERO(cpusetp) \
  memset((cpusetp), 0, sizeof(cpu_set_t))


/*
define the structure of data that is passed
it must be the same as the one defined in reliability.h
*/
struct reliability_stats_data {
		unsigned long int cpu;
		unsigned long int j; //jiffies
		unsigned long int cycles;
		unsigned long int instructions;
};


/*
define the length of the buffer to export data
the length must be the same of the one defined in reliability_stats_module.
*/
#define RELIABILITY_EXPORT_LENGTH 1024	
#define NUM_CPU 4

// ---------------- MAIN FUNCTION ----------------- //

void main(int argc, char ** argv){
	


}











