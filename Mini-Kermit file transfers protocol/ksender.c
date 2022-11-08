#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "lib.h"

#define HOST "127.0.0.1"
#define PORT 10000

int main(int argc, char **argv) {
    msg t;
    int MAXL = 250, i, round;
    char SEQ = 0;
    unsigned char len;
    char sDATA[MAXL], buff[250];

    sDATA[0] = MAXL;    // DIMENSIUNE MAXL
    sDATA[1] = 5;       // TIME
    sDATA[2] = 0x00;    // NPAD
    sDATA[3] = 0x00;    // PADC
    sDATA[4] = 0x0D;    // EOL
    sDATA[5] = 0x00;    // QCTL
    sDATA[6] = 0x00;    // QBIN
    sDATA[7] = 0x00;    // QCHKT
    sDATA[8] = 0x00;    // REPT
    sDATA[9] = 0x00;    // CAPA
    sDATA[10] = 0x00;   // R

    init(HOST, PORT);

    t = createMSG(SEQ, 'S', 11, sDATA);
    send_message(&t);


    for (i = 0; i <= 3; i++) {
        if (i == 3) {
            endTRANSMISION(SEQ);
            return 0;
        }
        msg *y = receive_message_timeout(1000 * sDATA[1]);
        if (y == NULL) {
            send_message(&t);
        } else if (getTYPE(y) == 'N' ||
                   (strcmp(sDATA, getDATA(y)) != 0)) {
            SEQ = (SEQ + 1) % 64;
            t = createMSG(SEQ, 'S', 11, sDATA);
            send_message(&t);
        } else {
            SEQ = (SEQ + 1) % 64;
            break;
        }

    }


    for (round = 1; round < argc; round++) {
        t = createMSG(SEQ, 'F', strlen(argv[round]), argv[round]);
        send_message(&t);

        for (i = 0; i <= 3; i++) {
            if (i == 3) {
                endTRANSMISION(SEQ);
                return 0;
            }
            msg *y = receive_message_timeout(5000);
            if (y == NULL) {
                send_message(&t);
            } else if (getTYPE(y) == 'N') {
                SEQ = (SEQ + 1) % 64;
                t = createMSG(SEQ, 'F', strlen(argv[round]), argv[round]);
                send_message(&t);
		i = 0;
            } else {
                SEQ = (SEQ + 1) % 64;
                break;
            }

        }


        int in = open(argv[round], O_RDONLY);
        if (in == -1) {
            printf("Eroare la deschiderea fisierului.\n");
            return -1;
        }

        while (1) {
            len = read(in, buff, 250);
            if (len <= 0) {
                break;
            }

            t = createMSG(SEQ, 'D', len, buff);
            send_message(&t);

            for (i = 0; i <= 3; i++) {
                if (i == 3) {
                    endTRANSMISION(SEQ);
                    return 0;
                }
                msg *y = receive_message_timeout(5000);
                if (y == NULL) {
                    send_message(&t);
                } else if (getTYPE(y) == 'N') {
                    SEQ = (SEQ + 1) % 64;
                    t = createMSG(SEQ, 'D', len, buff);
                    send_message(&t);
                    i = 0;
                } else {
                    SEQ = (SEQ + 1) % 64;
                    break;
                }

            }

        }
        close(in);
        t = createMSG(SEQ, 'Z', 0, "");
        send_message(&t);

        for (i = 0; i <= 3; i++) {
            if (i == 3) {
                endTRANSMISION(SEQ);
                return 0;
            }
            msg *y = receive_message_timeout(5000);
            if (y == NULL) {
                send_message(&t);
            } else if (getTYPE(y) == 'N') {
                SEQ = (SEQ + 1) % 64;
                t = createMSG(SEQ, 'Z', 0, "");
                send_message(&t);
		i = 0;
            } else {
                SEQ = (SEQ + 1) % 64;
                break;
            }
        }
    }

    endTRANSMISION(SEQ);

    return 0;
}
