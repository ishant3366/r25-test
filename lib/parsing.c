#include <stdint.h>
#include <parsing.h>

// Implement the interpolation function
int interpolation(uint16_t channel) {
    const uint16_t input_min = 0;    // Minimum value of the input channel
    const uint16_t input_max = 2047; // Maximum value of the input channel
    const int output_min = 0;        // Minimum PWM value
    const int output_max = 255;      // Maximum PWM value

    // Interpolate the channel value into the PWM range
    int pwm = (int)((((float)(channel - input_min) / (input_max - input_min)) * (output_max - output_min)) + output_min);

    return pwm;
}

// Implement the parse_buffer function
uint16_t *parse_buffer(uint8_t buff[]) { 
    // to store channels
    static uint16_t channel[16];

    // masking byte shiftings bits (value in hexa '0x07FF')
    uint16_t mask = 0x7ff;

    // creating channels 
    channel[0]  = ((buff[1] | buff[2]<<8)                 & mask);
    channel[1]  = ((buff[2]>>3 | buff[3]<<5)              & mask);
    channel[2]  = ((buff[3]>>6 | buff[4]<<2 | buff[5]<<10) & mask);
    channel[3]  = ((buff[5]>>1 | buff[6]<<7)              & mask);
    channel[4]  = ((buff[6]>>4 | buff[7]<<4)              & mask);
    channel[5]  = ((buff[7]>>7 | buff[8]<<1 | buff[9]<<9)  & mask);
    channel[6]  = ((buff[9]>>2 | buff[10]<<6)             & mask);
    channel[7]  = ((buff[10]>>5| buff[11]<<3)             & mask);
    channel[8]  = ((buff[12]   | buff[13]<<8)             & mask);
    channel[9]  = ((buff[13]>>3| buff[14]<<5)             & mask);
    channel[10] = ((buff[14]>>6| buff[15]<<2| buff[16]<<10)& mask);
    channel[11] = ((buff[16]>>1| buff[17]<<7)             & mask);
    channel[12] = ((buff[17]>>4| buff[18]<<4)             & mask);
    channel[13] = ((buff[18]>>7| buff[19]<<1| buff[20]<<9) & mask);
    channel[14] = ((buff[20]>>2| buff[21]<<6)             & mask);
    channel[15] = ((buff[21]>>5| buff[22]<<3)             & mask);

    return channel;
}



