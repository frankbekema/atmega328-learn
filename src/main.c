#include <SPI.h>
#include "command.h"

#define MASTER 0
#define SLAVE 1

#define TRANSFER_SPEED 16000000

#define MODE MASTER
//#define MODE SLAVE

command_object_t c_object;

SPISettings main_spi(TRANSFER_SPEED, MSBFIRST, SPI_MODE1);

void TestFunction() {
  Serial.println("Test function called");
}

void spi_send_message(const char* message) { 
  
}

const char* spi_read_message() {

}

void send_hello() {
  spi_send_message("Hello World!");
}

void read_hello() {
  spi_read_message()
}

void master_setup() {
  command_add(&c_object, "sendHello", send_hello);
}

void master_loop() {
  
}

void slave_setup() {

}

void slave_loop() {

}

void setup() {
  Serial.begin(9600);
  SPI.begin();

  c_object = command_get_object();
  
  command_add(&c_object, "test", TestFunction);

  switch(MODE) {
    case MASTER:
      master_setup();
      break;
    case SLAVE:
      slave_setup();
      break;
  }
}

void loop() {
  switch(MODE) {
    case MASTER:
      master_loop();
      break;
    case SLAVE:
      slave_loop();
      break;
  }
  command_handler(&c_object);
}
