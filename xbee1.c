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

// #include <stdint.h>
// #include <avr/io.h>
// #include <avr/iotn2313.h>
// #include <avr/interrupt.h>
#include "xbee1.h"

//
// Xbee Series 1 API mode 1 implementation
//

// Calculate checksum byte for API mode
unsigned char calculate_checksum(tx_request16 tx) {
    // From the Xbee datasheet ...
    //
    // To test data integrity, a checksum is calculated and verified on non-escaped data.
    //
    // To calculate: Not including frame delimiters and length, add all bytes keeping only the lowest 8
    // bits of the result and subtract from 0xFF.

    unsigned long sum = tx.api_id + tx.frame_id + tx.dest_addr + tx.tx_opts;
    for (unsigned int i = 0; i != 3; ++i) {
        sum += tx.rf_data[i];
     }

    // Get lowest 8 bits of sum
    unsigned char lsb = sum & 0xFF;

    // subtract lowest 8 bit of sum from 0xFF
    return 0xFF - lsb;
}

tx_request16 create_tx_request16(unsigned char data[], unsigned int address) {
    // TODO: data array should only have three elements. How do a check for this?
    const unsigned char PAD_SIZE = 5; /// always add 5 to data to get length
    tx_request16 tx;
    tx.api_id      = 0x01;
    tx.start_delim = 0x7E;
    tx.frame_id    = 0x00;
    tx.tx_opts     = 0x01;
    tx.dest_addr   = address;
    
    // TODO; is there a better way to do this?
    for (unsigned int i=0; i != 3; i++) {
        tx.rf_data[i] = data[i];
    }

    tx.length      = PAD_SIZE + 3;
    tx.checksum    = calculate_checksum(tx);
    return tx;
}

// verify checksum byte for API mode
unsigned char verify_checksum(tx_request16 tx) {
    // From the Xbee datasheet ...
    //
    // To test data integrity, a checksum is calculated and verified on non-escaped data.
    //
    // To verify: Add all bytes (include checksum, but not the delimiter and length). If the checksum is
    // correct, the sum will equal 0xFF.
    unsigned long sum = tx.api_id + tx.frame_id + tx.dest_addr + tx.tx_opts + tx.checksum;
    for (unsigned int i = 0; i != 3; ++i) {
        sum += tx.rf_data[i];
     }

     if (sum == 0xFF) {
        // checksum valid
        return 1;
     } else {
        // checksum invalid
        return 0;
     }
}

