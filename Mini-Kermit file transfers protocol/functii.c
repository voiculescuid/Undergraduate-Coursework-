#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

char getSEQ(msg *t) {
    return t->payload[2];
}

void setSEQ(msg *t, char SEQ) {
    t->payload[2] = SEQ;
}

void setLEN(msg *t, unsigned char len) {
    t->payload[1] = (unsigned char) len;
}

char getTYPE(msg *t) {
    return t->payload[3];
}

void setTYPE(msg *t, char TYPE) {
    t->payload[3] = TYPE;
}

void setDATA(msg *t, char DATA[], unsigned char len) {
    memcpy(&t->payload[4], DATA, len);
}


void setSOH(msg *t) {
    t->payload[0] = 0x01;
}


char getDATALEN(msg *t) {
    return t->payload[1];
}

char *getDATA(msg *t) {
    return &t->payload[4];
}


void setCHECK(msg *t) {
    unsigned short crc = crc16_ccitt(t->payload, (unsigned char) getDATALEN(t) + 4);
    memcpy(&t->payload[(unsigned char) getDATALEN(t) + 6], &crc, 2);
}

unsigned short getCHECK(msg *t) {
    unsigned short crc;
//crc = *((unsigned short*) &t->payload[(unsigned char)getDATALEN(t)+6]);
//memcpy(&crc, &t->payload[(unsigned char)getDATALEN(t)+6], sizeof(short));
    crc = (t->payload[(unsigned char) getDATALEN(t) + 6] & 0x00ff) |
          (t->payload[(unsigned char) getDATALEN(t) + 7] << 8);
    return crc;
}


void setMARK(msg *t) {
    t->payload[(unsigned char) getDATALEN(t) + 8] = '4';
}

char getMARK(msg *t) {
    return t->payload[strlen(getDATA(t)) + 7];
}

msg createMSG(char SEQ, char TYPE, unsigned char LEN, char DATA[]) {
    msg t;

    setSOH(&t);
    setSEQ(&t, SEQ);
    setTYPE(&t, TYPE);
    setLEN(&t, LEN);
    setDATA(&t, DATA, LEN);
    setCHECK(&t);
    setMARK(&t);

    t.len = strlen(t.payload);
    return t;
}

int CHECKmsg(msg *t) {
    if (getCHECK(t) == crc16_ccitt(t->payload, (unsigned char) getDATALEN(t) + 4))
        return 1;
    return -1;
}

int sendACK(char SEQ) {
    msg t = createMSG(SEQ, 'Y', 0, "");
    send_message(&t);
    return 1;
}

int sendNAK(char SEQ) {
    msg t = createMSG(SEQ, 'N', 0, "");
    send_message(&t);
    return 1;
}

void endTRANSMISION(char SEQ) {
    msg t;
    t = createMSG(SEQ, 'B', 0, "");
    send_message(&t);
}

