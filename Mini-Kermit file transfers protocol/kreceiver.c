#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "lib.h"

#define HOST "127.0.0.1"
#define PORT 10001

int main(int argc, char **argv) {
    msg t;
    int out;
    char *sDATA, SEQ = 0, type, name[20] = "recv_";
    int jump;

    init(HOST, PORT);

    msg *y = receive_message_timeout(15000);
    if (y == NULL) {
        perror("receive error");
        return -1;
    }
    SEQ = (getSEQ(y) + 1) % 64;

    sDATA = getDATA(y);
    t = createMSG(SEQ, 'Y', 11, sDATA);
    send_message(&t);
    int count = 0;

    while (1) {
        y = receive_message_timeout(1000 * sDATA[1]);
        if (y == NULL) {
            count++;
            if (count == 3)
                return 0;

            continue;
        }
        count = 0;
        SEQ = (getSEQ(y) + 1) % 64;

        if (CHECKmsg(y) == 1)
            sendACK(SEQ);
        else {
            sendNAK(SEQ);
            continue;
        }

        type = getTYPE(y);
        if (type == 'F')
            jump = 1;
        else if (type == 'D')
            jump = 2;
        else if (type == 'Z')
            jump = 3;
        else if (type == 'B')
            jump = 4;
        else
            jump = 5;


        switch (jump) {
            case 1:
                strncat(name, getDATA(y), getDATALEN(y));
                out = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (out == -1) {
                    printf("Eroare la deschiderea fisierului.\n");
                    return -1;
                }
                strcpy(name, "recv_");
                break;

            case 2:
                write(out, getDATA(y), (unsigned char) getDATALEN(y));
                break;

            case 3:
                close(out);
                break;


            case 4:
                return 0;
                break;


            default:
                break;
        }
    }
    return 0;
}
