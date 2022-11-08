#ifndef LIB
#define LIB

typedef struct {
    int len;
    char payload[1400];
} msg;

void init(char *remote, int remote_port);

void set_local_port(int port);

void set_remote(char *ip, int port);

int send_message(const msg *m);

int recv_message(msg *r);

msg *receive_message_timeout(int timeout); //timeout in milliseconds

unsigned short crc16_ccitt(const void *buf, int len);

char getSEQ(msg *t);

void setSEQ(msg *t, char SEQ);

char getTYPE(msg *t);

void setTYPE(msg *t, char TYPE);

void setDATA(msg *t, char DATA[], unsigned char len);

char *getDATA(msg *t);

void setLEN(msg *t, unsigned char len);

char getDATALEN(msg *t);

void setMARK(msg *t);

char getMARK(msg *t);

msg createMSG(char SEQ, char TYPE, unsigned char LEN, char DATA[]);

unsigned short getCHECK(msg *t);

int CHECKmsg(msg *t);

int sendACK(char SEQ);

int sendNAK(char SEQ);

void endTRANSMISION(char SEQ);


#endif

