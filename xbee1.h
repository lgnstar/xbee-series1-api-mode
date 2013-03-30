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

#ifndef XBEE1_H
#define XBEE1_H

// TODO: implement TX Request (64-bit address)
//                       _____Frame_Data_____
// start_delim  length   API_Identifier  Data  checksum
// 0x7E         MSB LSB  0x00            XXX   1 byte
struct tx_request {
    const unsigned char api_id = 0x00;
    unsigned char checksum;
    unsigned char rf_data;    // actual data payload
    const uint16_t length 12; // fixed length 12 to send one byte of data
    const unsigned char start_delim = 0x7E;

    const char frame_id 0x00;    // disable response frame
    unsigned long long dest_addr;  // 64 bit destination address
    tx_opts = 0x01; // disable ACK
};

void calculate_checksum(struct tx_request *tx);

// temp hardcoded length
// void calculate_length();
struct tx_request create_tx_request(unsigned char data);

#endif
