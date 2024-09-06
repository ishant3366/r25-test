#include <stdint.h>
#include <stdio.h>
#include <serial.h>
#include <parsing.h>

int main(int argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <SBUS_PORT> <SABERTOOTH_PORT>\n", argv[0]);
        return 1;
    }

    char *port_name_1 = argv[1]; // SBUS 
    char *port_name_2 = argv[2]; // Sabertooth1

    FILE *sbus; 
    FILE *sabertooth;

    // to store sbus packets
    uint8_t sbus_packet[15];

    // to store value of individual RC channel
    uint16_t *channel;

    // pwm value after interpolation 
    int pwm;

    // opening serial port for serial communication with Sabertooth and SBUS
    sbus = open_file(port_name_1, "rb");
    if (sbus == NULL) {
        perror("Failed to open SBUS port");
        return 1;
    }
    sabertooth = open_file(port_name_2, "w+");
    if (sabertooth == NULL) {
        perror("Failed to open Sabertooth port");
        close_file(sbus);
        return 1;
    }

    // read data from RC transmitter using sbus
    read_SBUS(sbus_packet, sizeof(sbus_packet), sbus);

    // parsing sbus packet
    channel = parse_buffer(sbus_packet);

    // get pwm range for Sabertooth 1			 
    pwm = interpolation(channel[0]);

    // write data to Sabertooth 1
    write_to_SB(sabertooth, "%d", pwm);

    // closing all serial ports
    close_file(sbus);
    close_file(sabertooth);

    return 0;
}
