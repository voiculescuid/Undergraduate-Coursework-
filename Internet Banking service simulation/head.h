#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_CLIENTS    5
#define BUFLEN 256

//  <nume> <prenume> <numar card> <pin> <parola secreta> <sold>

typedef struct client {
    char nume[12];
    char prenume[12];
    int nr;
    short pin;
    char password[8];
    double sold;
} client;

typedef struct log {
    int nr;
    short pin;
} log;

void error(char *msg);
void sendQ(int fdmax);
client *getClientbyNR(int nr, struct client users[]);
void syncc(struct client users[], struct client logged[], struct client locked[]);
void lock(int nr, struct client locked[], struct client users[]);
int wrongpin(int nr, short pin, struct log wrong[]);
void sendERR(int sockfd, int err);
int trytologin(int sockfd, int NR_USERS, int pinU, int nrU, struct client users[], struct client logged[]);
