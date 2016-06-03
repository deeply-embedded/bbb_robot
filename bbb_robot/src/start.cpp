#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <fstream>
#include <stdlib.h>
#include <sys/mman.h>

using namespace std;

// hier Konstanten fuer Speicheradressen etc.
#define GPIO1_START_ADDR 0x4804C000
#define GPIO1_END_ADDR 0x4804CFFF
#define GPIO1_SIZE (GPIO1_END_ADDR - GPIO1_START_ADDR)

#define GPIO_OUT_CONF 0x14d
#define GPIO_CLEARDATAOUT 0x64
#define GPIO_SETDATAOUT 0x65
#define PIN_P9_12 (1 << 16)
// ... weitere Konstanten

void writeToPinP9_12(int value) {
	volatile unsigned int *gpio_addr = NULL;
	int fd = open("/dev/mem", O_RDWR);

// Speicherereich fuer GPIO1 Controller mappen
	gpio_addr = (unsigned int *) mmap(0, GPIO1_SIZE, (PROT_READ | PROT_WRITE),
	MAP_SHARED, fd, GPIO1_START_ADDR);

// Richtung auf Output setzen
	*(gpio_addr + GPIO_OUT_CONF) &= ~PIN_P9_12;

// Wert setzen
	if (value > 0)
		*(gpio_addr + GPIO_SETDATAOUT) = PIN_P9_12;
	else
		*(gpio_addr + GPIO_CLEARDATAOUT) = PIN_P9_12;
}

void writeToPin(int gpioPin, int value) {
	fstream fileStream;
	string gpioPath;
	char buffer[3];
	sprintf(buffer, "%d", gpioPin);

// Pin exportieren
	fileStream.open("/sys/class/gpio/export", fstream::out);
	fileStream << gpioPin;
	cout << fileStream << endl;
	fileStream.close();
	gpioPath = "/sys/class/gpio/gpio" + (string) buffer;
	//cout << gpioPath << endl;

// Richtung auf Output setzen
	fileStream.open((gpioPath + "/direction").c_str(), fstream::out);
	fileStream << "out";
	fileStream.close();

// Wert setzen
	fileStream.open((gpioPath + "/value").c_str(), fstream::out);
	fileStream << value;
	fileStream.close();
}

void writeToPin1(int gpioPin, int value) {
	char buff[50];

	/* ===== set pin to the export =======*/
	int fd = open("/sys/class/gpio/export", O_WRONLY); //1	/* +1 == FWRITE */
	sprintf(buff, "%d", gpioPin);
	write(fd, buff, strlen(buff));
	close(fd);

	/*========= set the direction =========*/
	sprintf(buff, "/sys/class/gpio/gpio%d/direction", gpioPin);
	fd = open(buff, O_WRONLY); //O_WRONLY = only write
	write(fd, "out", 3);
	close(fd);

	/*====== set the value =======*/
	sprintf(buff, "/sys/class/gpio/gpio%d/value", gpioPin);
	fd = open(buff, O_WRONLY);
	sprintf(buff, "%d", value);
	write(fd, buff, 1);
	close(fd);
}

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	//writeToPin1(66, 1);
	writeToPinP9_12(1);
	return 0;
}
