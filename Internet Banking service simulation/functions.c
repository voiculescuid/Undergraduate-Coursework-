#include "head.h"

//ERROR

void error(char *msg) {
    perror(msg);
    exit(0);
}

//TRIMITERE ANUNT DE INCHIDERE
void sendQ(int fdmax) {
    for (int i = 0; i < fdmax; i++) {
        send(i, "quit\n", 5, 0);
    }

}

//CLIENT DUPA NR
client *getClientbyNR(int nr, struct client users[]) {

    for (int i = 0; i < 1000; i++) {
        if (users[i].nr == nr)
            return &users[i];
    }
    return NULL;
}

//SINCRONIZARE VECTORI CLIENTI
void syncc(struct client users[], struct client logged[], struct client locked[]) {
    for (int i = 0; i < 1000; i++) {
        if (getClientbyNR(users[i].nr, logged) != NULL)
            memcpy(getClientbyNR(users[i].nr, logged), &users[i], sizeof(struct client));

        if (getClientbyNR(users[i].nr, locked) != NULL)
            memcpy(getClientbyNR(users[i].nr, locked), &users[i], sizeof(struct client));
    }
}

//BLOCARE CARD

void lock(int nr, struct client locked[], struct client users[]) {
    for (int i = 0; i < 1000; i++) {
        if (locked[i].nr == 0)
            memcpy(&locked[i], getClientbyNR(nr, users), sizeof(struct client));
    }

}


//CONTOAR EROARE PIN

int wrongpin(int nr, short pin, struct log wrong[]) {
    for (int i = 0; i < 1000; i++) {

        if (wrong[i].nr == nr)
            wrong[i].pin++;
        if (nr == wrong[i].nr && wrong[i].pin == 3)
            return -1;
    }


    for (int i = 0; i < 1000; i++) {
        if (wrong[i].nr == 0) {
            wrong[i].nr = nr;
            wrong[i].pin = 1;
            return 0;
        }
    }
    return 0;
}

//ERORI
void sendERR(int sockfd, int err) {
    int check;

    if (err == -1)
        check = send(sockfd, "-1 : Clientul nu este autentificat\n", 35, 0);
    if (check < 0)
        error("ERROR writing to socket");
    if (err == -2)
        check = send(sockfd, "-2 : Sesiune deja deschisa'\n", 27, 0);
    if (check < 0)
        error("ERROR writing to socket");
    if (err == -3)
        check = send(sockfd, "-3 : Pin gresit\n", 16, 0);
    if (check < 0)
        error("ERROR writing to socket");
    if (err == -4)
        check = send(sockfd, "-4 : Numar card inexistent\n", 27, 0);
    if (check < 0)
        error("ERROR writing to socket");
    if (err == -5)
        check = send(sockfd, "-5 : Card blocat\n", 17, 0);
    if (check < 0)
        error("ERROR writing to socket");
    if (err == -6)
        check = send(sockfd, "-6 : Operatie esuata\n", 21, 0);
    if (check < 0)
        error("ERROR writing to socket");
    if (err == -7)
        check = send(sockfd, "-7 : Deblocare esuata\n", 21, 0);
    if (check < 0)
        error("ERROR writing to socket");
    if (err == -8)
        check = send(sockfd, "-8 : Fonduri insuficiente\n", 26, 0);
    if (check < 0)
        error("ERROR writing to socket");
    if (err == -9)
        check = send(sockfd, "-9 : Operatie anulata\n", 22, 0);
    if (check < 0)
        error("ERROR writing to socket");
    if (err == -10)
        check = send(sockfd, "-10 : Eroare la apel nume-functie\n", 33, 0);
    if (check < 0)
        error("ERROR writing to socket");
}

//LOGIN

int trytologin(int sockfd, int NR_USERS, int pinU, int nrU, struct client users[], struct client logged[]) {
    char buffer[BUFLEN];

    struct log login;
    login.nr = nrU;
    login.pin = pinU;
    for (int i = 0; i < 1000; i++) {
        if (login.nr == logged[i].nr) {
            sendERR(sockfd, -2);
            return 0;
        }
    }

    for (int i = 0; i < NR_USERS; i++) {
        if (login.nr == users[i].nr) {
            if (login.pin != users[i].pin) {
                sendERR(sockfd, -3);
                return -1;
            } else {
                memcpy(&logged[sockfd], &users[i], sizeof(struct client));
                sprintf(buffer, "Welcome %s %s \n", users[i].nume, users[i].prenume);
                send(sockfd, buffer, BUFLEN, 0);
                return 0;
            }
        }
    }
    sendERR(sockfd, -4);
    return 0;

}
