  
// --------------- MONITOR INFRASTRUCTURE - USERSPACE DAEMON -----------------
/*
 * 
 * Author: Andrea Bartolini
 *
 * Modified by : Pietro Mercati
 * email : pimercat@eng.ucsd.edu
 * 
 * If using this code for research purposes, include 
 * references to the following publications
 * 
 * 1) P.Mercati, A. Bartolini, F. Paterna, T. Rosing and L. Benini; A Linux-governor based 
 *    Dynamic Reliability Manager for android mobile devices. DATE 2014.
 * 2) P.Mercati, A. Bartolini, F. Paterna, L. Benini and T. Rosing; An On-line Reliability 
 *    Emulation Framework. EUC 2014
 * 
	This file is part of DRM.
        DRM is free software: you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
        the Free Software Foundation, either version 3 of the License, or
        (at your option) any later version.

        DRM is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU General Public License for more details.

        You should have received a copy of the GNU General Public License
        along with DRM.  If not, see <http://www.gnu.org/licenses/>.


*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sched.h>
#include <unistd.h>
#include <string.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <sys/wait.h> //for wait()

#define DEBUG // enables printf for debugging
#define NUM_CPU 8 // number of cpu of the target platform
#define SLEEP_TIME 1

// Pietro : the following needs to be the same as in monitor_infrastructure_driver.c
#define MONITOR_EXPORT_PAGE 6   	// Number of pages allocated for each buffer
#define MONITOR_EXPORT_LENGTH 1024      // Number of enries of kind "monitor_stats_data" inside the allocated buffer
// Macros for ioctl
#define SELECT_CPU 	1
#define READY 		2
#define S_READY		3

struct monitor_stats_data {
                unsigned int cpu;
                unsigned long int j; 	//jiffies
                unsigned long int cycles;
                unsigned long int instructions;
};

// ---------------- MAIN FUNCTION ----------------- //

int main(int argc, char ** argv){

	int fd;	
	int cpu;	
	char *log;
	int ready[NUM_CPU];
	int ready_old[NUM_CPU];
	int len;
	struct monitor_stats_data *log_struct;
	char buf[3];
	char file_name[60];
	FILE *fp;
	int i;

	// remove previous files (this is required as files are opened with the append option)
	system("rm /data/PIETRO/MONITOR_STATS/monitor_stats_data_cpu_*");


	#ifdef DEBUG
	printf("\n\nStarting Serial Reading\n\n");
	#endif // DEBUG

	// open monitor driver
	fd = open("/dev/monitor",O_RDWR);
	if( fd == -1) {
                printf("Monitor driver open error...\n");
                exit(0);
        }

	// save the current status of ready flags	
	for (cpu = 0 ; cpu < NUM_CPU ; cpu++){
		ioctl(fd, READY, &ready[cpu]);
		ready_old[cpu] = ready[cpu]; 
	}
		
	// Main Loop
	while(1){
		
		// sleep to reduce overhead	
		sleep(SLEEP_TIME);			

		// check each cpu
		for (cpu = 0 ; cpu < NUM_CPU ; cpu++){
			
			// select cpu and get the ready flag
			ioctl(fd, SELECT_CPU, &cpu);
			ioctl(fd, S_READY, &ready[cpu]);

			if ( (ready[cpu] == ready_old[cpu])  &&   (ready[cpu] != 0) ){ // in case these two are verified, then the buffer is not ready
				#ifdef DEBUG
                        	printf("CPU %u Not ready yet...\n", cpu);
                        	printf("READY = %u\n", ready[cpu]);
				#endif // DEBUG
                	} else { // if enters this else, it means the buffer for that cpu is ready

				// allocate log buffer
				log = malloc (sizeof(struct monitor_stats_data)*MONITOR_EXPORT_LENGTH);

				// read the buffer and store into log
				len = read(fd , log , MONITOR_EXPORT_LENGTH);
				
				// verify correct reading
		                if (len == -1){
                		        printf("Error while reading buffer...\n");
                        		exit(1);
                		}

				// writing log data to file
				#ifdef DEBUG
				printf("Start writing data on file !! \n");
				#endif
				// re-initialize log struct
                		log_struct = (struct monitor_stats_data *)log;

				// open file
				sprintf(buf,"%d",cpu);
				strcpy(file_name,"/data/PIETRO/MONITOR_STATS/monitor_stats_data_cpu_");
				strcat(file_name,buf);
				fp = fopen(file_name,"a");
				
				// write data to file in the right format
				for(i = MONITOR_EXPORT_LENGTH-1 ; i>=0 ; i--){
                        		fprintf(
						fp,
                                        	"%lu\t%lu\t%lu\t%lu\n",
                                                log_struct[i].cpu,
                                                log_struct[i].j,
                                                log_struct[i].cycles,
                                                log_struct[i].instructions
						);
				}
				
				// close file
				fclose(fp);				

				// update ready_old
		                ready_old[cpu] = ready[cpu];

				// free log buffer
				free(log);

			} // end of reading
		} // end of for cpu
	} // end of Main loop

	return 0;
} 











