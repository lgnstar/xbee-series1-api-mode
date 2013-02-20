/*
 * Copyright (c) 2013 Sean Malloy
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    - Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    - Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials provided
 *      with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <stdint.h>
#include <avr/io.h>
#include <avr/iotn2313.h>
#include <avr/interrupt.h>

void calc_checksum();
void calc_length();

ISR(USART_RX_vect) {
	uint8_t usart_input = UDR;

	// Exit if we did not get ASCII S
	if (usart_input != 0x53) {
		return;
	}

	// TODO: remove the LED toggle test
	PORTB ^= _BV(PB4);

	// read input
	if (bit_is_clear(PIND, PD2)) {
		// 3.3V between PD2 and VCC, turn LED on
		PORTD |= _BV(PD3);
		UDR = 0x59; // ASCII Y
	} else {
		// voltage between VCC and PD2 is 0V, turn LED off
		PORTD &= ~_BV(PD3);
		UDR = 0x4E; // ASCII N
	}
}

//
// Implement API mode 2
//

// TODO calculate checksum byte
// for API mode
unsigned char calculate_checksum(unsigned char data[]) {
    // From the Xbee datasheet ...
    //
    // To test data integrity, a checksum is calculated and verified on non-escaped data.
    //
    // To calculate: Not including frame delimiters and length, add all bytes keeping only the lowest 8
    // bits of the result and subtract from 0xFF.
    unsigned char sum = 0;
    for (unsigned int i = 0; i != sizeof(data); ++i) {
        sum += data[i];
    }
    // START
    // TODO: get lowest 8 bits of sum
    unsigned char lower8 = 0;
    // TODO: subtract lowest 8 bit of sum from 0xFF
    return 0xff - lower8;
}


// TODO verify checksum byte
// for API mode
void verify_checksum() {
    // From the Xbee datasheet ...
    //
    // To test data integrity, a checksum is calculated and verified on non-escaped data.
    //
    // To verify: Add all bytes (include checksum, but not the delimiter and length). If the checksum is
    // correct, the sum will equal 0xFF.
}


// TODO calculate length(MSB + LSB)
// TODO figure out how to calculate the length (what is the length?)
void calculate_length() {

}


// TODO: implement TX Request (64-bit address)
//                       _____Frame_Data_____
// start_delim  length   API_Identifier  Data  checksum
// 0x7E         MSB LSB  0x00            XXX   1 byte

// TODO: implement RX Packet (64-bit address)
//                       _____Frame_Data_____
// start_delim  length   API_Identifier  Data checksum
// 0x7E         MSB LSB  0x80            XXX  1 byte

