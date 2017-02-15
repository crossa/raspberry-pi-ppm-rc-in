/*
 * main.cpp
 *
 *  Created on: 2017年1月9日
 *      Author: secondstupid
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <pigpio.h>
//-----------IPC 共享内存头文件------------//
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
//--------------------------------------//
#include "ppmdecode.h"
//--------------------------------------//
void ppmOnEdge(int gpio, int level, uint32_t tick) {
	if (level == 0) {
		deltaTime = tick - previousTick;
		previousTick = tick;

		if (deltaTime >= ppmSyncLength) { // Sync
			currentChannel = 0;
			for(int j=0;j<ppmChannelsNumber;++j){
				 *(mem+j) = channels[j];
			}
			return;
		}

		if (currentChannel < ppmChannelsNumber) {
			channels[currentChannel++] = deltaTime;
		}
		return;
	}
}
//-------------------main函数-----------------------//
void *start_ppm_listener(void *p){
	printf("Start PPM listener\n");
	gpioCfgClock(samplingRate, PI_DEFAULT_CLK_PERIPHERAL, 0); /* last parameter is deprecated now */
	gpioInitialise();
	previousTick = gpioTick();
	gpioSetAlertFunc(ppmInputGpio, ppmOnEdge);
	pthread_detach (pthread_self ());
	while(1)
		sleep(30);
}


int main(int argc, char *argv[]) {

	if (argc < 2) {
		printf("用法: ppmdecode [L/P]\n");
		return 1;
	}
	//printf("Argv1:%s\n",argv[1]);
	if(0==strcmp("P",argv[1])){
		//拷贝ROMFS目录;
		//fs = argv[1];
		static const uint8_t outputEnablePin = RPI_GPIO_27;
		//::Pin pin(outputEnablePin);
		//---------------内存共享区---------------//
		if ((shmid = shmget(key, sizeof(int*)*8, IPC_CREAT | 0666)) < 0) {
			printf("无法创建内存共享区\n");
			return 0x01;
		}

			/*
			 * Now we attach the segment to our data space.
			 */
		void *p;
		if ((p = shmat(shmid, NULL, 0)) == (void*)-1) {
				printf("无法映射共享内存区块\n");
				return 0x02;
		}
		mem=(int*)p;
		//--------------------------------------//

		pthread_t thread;
		pthread_create(&thread,NULL,start_ppm_listener,NULL);
		pthread_join(thread,NULL);
		return 0x00;
	}

	if(0==strcmp("L",argv[1])){

		    /*
		     * Locate the segment.
		     */
		    if ((shmid = shmget(key, sizeof(int*)*8, 0444)) < 0) {
		        perror("shmget");
		        exit(1);
		    }

		    /*
		     * Now we attach the segment to our data space.
		     */
				void *p;
		    if ((p = shmat(shmid, NULL, 0)) == (void*) -1) {
		        perror("shmat");
		        exit(1);
		    }
				int *w = (int*)p;
				while(1){
					for(int j=0;j<ppmChannelsNumber;++j){
							printf("PWM%d:%d\n",j,*(w+j));
					}
					sleep(1);
				}
	}
	return 0x00;
}
