#include "LCD.h"

// the time is in the registers in decimal form
int LCD::bcdToDec(char b) { return (b/16)*10 + (b%16); }

void LCD::write_word(int data)
{
   int temp = data;
   temp |= 0x08;

   wiringPiI2CWrite(LCD::fd, temp);
}

void LCD::send_command(int comm)
{
   int buffer;
   // bit7-4
   buffer = comm & 0xF0;
   buffer |= 0x04;   // reg select 0, enable 1
   write_word(buffer);
   this_thread::sleep_for(chrono::milliseconds(2));

   buffer &= 0xFB;   // disable
   write_word(buffer);

   // bit3-0
   buffer = (comm & 0x0F) << 4;
   buffer |= 0x04;   // reg select 0, enable 1
   write_word(buffer);
   this_thread::sleep_for(chrono::milliseconds(2));

   buffer &= 0xFB;   // disable
   write_word(buffer);
}

void LCD::send_data(int data)
{
   int buffer;
   // bit7-4
   buffer = data & 0xF0;
   buffer |= 0x05;   // reg select 1, enable 1
   write_word(buffer);
   this_thread::sleep_for(chrono::milliseconds(2));

   buffer &= 0xFB;   // disable
   write_word(buffer);

   // bit3-0
   buffer = (data & 0x0F) << 4;
   buffer |= 0x05;   // reg select 1, enable 1
   write_word(buffer);
   this_thread::sleep_for(chrono::milliseconds(2));

   buffer &= 0xFB;   // disable
   write_word(buffer);
}

void LCD::init()
{
   send_command(0x33);  // 8-line mode
   this_thread::sleep_for(chrono::milliseconds(5));
   send_command(0x32);  // 4-line mode
   this_thread::sleep_for(chrono::milliseconds(5));
   send_command(0x28);  // 2 Lines with 5*7 dots
   this_thread::sleep_for(chrono::milliseconds(5));
   send_command(0x0C);  // disable cursor
   this_thread::sleep_for(chrono::milliseconds(5));
   send_command(0x01);  // clear screen

   wiringPiI2CWrite(LCD::fd, 0x08);
}

void LCD::clear()
{
   send_command(0x01);  //clear screen
}


void LCD::lcd_write(int x, int y, char data[])
{
   int addr;
   if (x < 0)  x = 0;
   if (x > 15) x = 15;
   if (y < 0)  y = 0;
   if (y > 1)  y = 1;

   // determine where to write in order to write at selected spot
   addr = 0x80 + 0x40 * y + x;
   send_command(addr);
   
   int dataLength = strlen(data);
   for (int i = 0; i < dataLength; i++)
      send_data(data[i]);
   
}

void LCD::setup()
{
   LCD::fd = wiringPiI2CSetup(LCD_ADDR);
   init();
}

// int main(){
//    printf("Starting RTC/LCD program\n");

//    fd = wiringPiI2CSetup(LCD_ADDR);
//    init();

//    for(int i = 0; i < 30; i++)
//    {

//       lcd_write(0, 0, "Welcome!");
//       lcd_write(0, 1, "Please Sign in:");

//       sleep(1);
//    }

//    printf("All done :)\n");
   //this_thread::sleep_for(chrono::milliseconds(2));
//    clear();

//    return 0;
// }
