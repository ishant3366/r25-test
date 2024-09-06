#include <stdint.h>
#include <stdio.h>
#include <parsing.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: %s <SBUS_port> <Sabertooth_port>\n", argv[0]);
        return 1;
    }

    char *port_name_1 = argv[1]; // SBUS 
    char *port_name_2 = argv[2]; // Sabertooth1

    FILE *sbus; 
    FILE *sabertooth;

    // to store sbus packets
    uint8_t sbus_packet[25]; // Adjust the size if necessary

    // to store value of individual RC channel
    uint16_t *channel;

    // pwm value after interpolation 
    int pwm;

    // opening serial port for serial communication with Sabertooth and SBUS
    sbus = open_file(port_name_1, "rb");
    sabertooth = open_file(port_name_2, "w+");
    
    if (sbus == NULL || sabertooth == NULL) {
        return 1;
    }
    
    // read data from RC transmitter using sbus
    read_SBUS(sbus_packet, sizeof(uint8_t), 25, sbus);

    // parsing sbus packet
    channel = parse_buffer(sbus_packet);

    // get pwm range for Sabertooth 1
    pwm = interpolation(channel[0]);

    // write data to Sabertooth 1
    write_to_SB(sabertooth, "%d\n", pwm);

    // closing all serial port 
    close_file(sbus);
    close_file(sabertooth);

    return 0;
}

