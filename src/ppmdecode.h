/*
 * ppmencode.h
 *
 *  Created on: 2017年1月13日
 *      Author: secondstupid
 */

#ifndef SRC_PPMDECODE_H_
#define SRC_PPMDECODE_H_
#define RPI_GPIO_2    2    // Pin 3     SDA
#define RPI_GPIO_3    3    // Pin 5     SCL
#define RPI_GPIO_4    4    // Pin 7             NAVIO_PPM_INPUT
#define RPI_GPIO_7    7    // Pin 26    CE1     NAVIO_MPU9250_CS
#define RPI_GPIO_8    8    // Pin 24    CE0     NAVIO_UBLOX_CS
#define RPI_GPIO_9    9    // Pin 21    MISO
#define RPI_GPIO_10   10   // Pin 19    MOSI
#define RPI_GPIO_11   11   // Pin 23    SCLK
#define RPI_GPIO_14   14   // Pin 8     TxD
#define RPI_GPIO_15   15   // Pin 10    RxD
#define RPI_GPIO_17   17   // Pin 11            NAVIO_UART_PORT_5
#define RPI_GPIO_18   18   // Pin 12            NAVIO_UART_PORT_4
#define RPI_GPIO_22   22   // Pin 15            NAVIO_UBLOX_PPS
#define RPI_GPIO_23   23   // Pin 16            NAVIO_MPU9250_DRDY
#define RPI_GPIO_24   24   // Pin 18            NAVIO_SPI_PORT_6
#define RPI_GPIO_25   25   // Pin 22            NAVIO_SPI_PORT_5
#define RPI_GPIO_27   27   // Pin 13            NAVIO_PCA9685_OE
#define RPI_GPIO_28   28   // Pin 3
#define RPI_GPIO_29   29   // Pin 4
#define RPI_GPIO_30   30   // Pin 5
#define RPI_GPIO_31   31   // Pin 6

//================================ Options =====================================//
unsigned int samplingRate = 1;      // 1 microsecond (can be 1,2,4,5,10)
unsigned int ppmInputGpio = 4;      // PPM input on Navio's 2.54 header
unsigned int ppmSyncLength = 4000;   // Length of PPM sync pause
unsigned int ppmChannelsNumber = 8;      // Number of channels packed in PPM
unsigned int servoFrequency = 50;     // Servo control frequency
bool verboseOutputEnabled = true;   // Output channels values to console
float channels[8];
//============================ Objects & data ==================================//
int shmid;
int *mem;
key_t key=4096;
unsigned int currentChannel = 0;
unsigned int previousTick;
unsigned int deltaTime;
//============================== PPM decoder ===================================//
void *start_ppm_listener(void *);
void ppmOnEdge(int gpio, int level, uint32_t);
#endif /* SRC_PPMDECODE_H_ */
