#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <chrono>
#include <thread>

#define BUFFER_SIZE 4
#define RTC_ADDR 0x68
#define LCD_ADDR 0x27

using namespace std;


class LCD 
{
	private:
		static inline int fd;

		static int bcdToDec(char b);
		static void write_word(int data);
		static void send_command(int comm);
		static void send_data(int data);
		static void init();


	public:
		static void setup();
		static void lcd_write(int x, int y, char data[]);
		static void clear();

};