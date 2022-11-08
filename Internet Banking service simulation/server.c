#include"head.h"

int main(int argc, char *argv[]) {
    int sockfd, newsockfd, portno, clilen;
    char buffer[BUFLEN], sender[BUFLEN];
    char *token;
    struct sockaddr_in serv_addr, cli_addr;
    int n, i, NR_USERS, ok, nr, check = 0, change, sum;
    short pin;

    fd_set read_fds;    //multimea de citire folosita in select()
    fd_set tmp_fds;    //multime folosita temporar
    int fdmax;        //valoare maxima file descriptor din multimea read_fds

    if (argc < 3) {
        fprintf(stderr, "./server <port_server> <users_data_file>");
        exit(1);
    }

    FILE *in = fopen(argv[2], "rt");
    if (in == NULL)
        error("Nu s-a putut deschide fisierul");

    fscanf(in, "%d", &NR_USERS);
    struct client logged[1000];
    struct client locked[1000];
    struct client users[1000];
    struct client *aux1, *aux2;
    struct log notpin[1000];

    for (i = 0; i < NR_USERS; i++) {
        fscanf(in, "%s", users[i].nume);
        fscanf(in, "%s", users[i].prenume);
        fscanf(in, "%d", &users[i].nr);
        fscanf(in, "%hd", &users[i].pin);
        fscanf(in, "%s", users[i].password);
        fscanf(in, "%lf", &users[i].sold);
    }
    fclose(in);


    //golim multimea de descriptori de citire (read_fds) si multimea tmp_fds
    FD_ZERO(&read_fds);
    FD_ZERO(&tmp_fds);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    portno = atoi(argv[1]);

    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;    // foloseste adresa IP a masinii
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr)) < 0)
        error("ERROR on binding");

    listen(sockfd, MAX_CLIENTS);

    //adaugam noul file descriptor (socketul pe care se asculta conexiuni) in multimea read_fds
    FD_SET(sockfd, &read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    fdmax = sockfd;

    // main loop
    while (1) {
        tmp_fds = read_fds;
        if (select(fdmax + 1, &tmp_fds, NULL, NULL, NULL) == -1)
            error("ERROR in select");

        for (i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &tmp_fds)) {
                if (i == STDIN_FILENO) {
                    scanf("%s", buffer);
                    if (buffer[0] == 'q') {
                        sendQ(fdmax);
                        close(sockfd);
                        return 0;
                    } else
                        printf("Wrong command m8! \n");
                } else if (i == sockfd) {
                    // a venit ceva pe socketul inactiv(cel cu listen) = o noua conexiune
                    // actiunea serverului: accept()
                    clilen = sizeof(cli_addr);
                    if ((newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen)) == -1) {
                        error("ERROR in accept");
                    } else {
                        //adaug noul socket intors de accept() la multimea descriptorilor de citire
                        FD_SET(newsockfd, &read_fds);
                        if (newsockfd > fdmax) {
                            fdmax = newsockfd;
                        }
                    }
                    printf("Noua conexiune de la %s, port %d, socket_client %d\n ", inet_ntoa(cli_addr.sin_addr),
                           ntohs(cli_addr.sin_port), newsockfd);
                } else {
                    // am primit date pe unul din socketii cu care vorbesc cu clientii
                    //actiunea serverului: recv()
                    memset(buffer, 0, BUFLEN);
                    if ((n = recv(i, buffer, sizeof(buffer), 0)) <= 0) {
                        if (n == 0) {
                            //conexiunea s-a inchis
                            printf("selectserver: socket %d hung up\n", i);
                        } else {
                            error("ERROR in recv");
                        }
                        close(i);
                        FD_CLR(i, &read_fds); // scoatem din multimea de citire socketul pe care
                    } else { //recv intoarce >0
                        printf("Am primit de la clientul de pe socketul %d, mesajul: %s\n", i, buffer);

                        buffer[strlen(buffer) - 1] = ' ';
                        token = strtok(buffer, " ");

                        if (strcmp(token, "login") == 0)
                            change = 1;
                        else if (strcmp(token, "logout") == 0)
                            change = 2;
                        else if (strcmp(token, "listsold") == 0)
                            change = 3;
                        else if (strcmp(token, "transfer") == 0)
                            change = 4;
                        else if (strcmp(token, "unlock") == 0)
                            change = 5;
                        else if (strcmp(token, "quit") == 0)
                            change = 6;
                        else
                            change = 100;

                        switch (change) {


                            case 1:
                                nr = atoi(strtok(NULL, " "));
                                pin = atoi(strtok(NULL, " "));
                                if (getClientbyNR(nr, locked) != NULL) {
                                    sendERR(i, -5);
                                    continue;
                                }

                                if (logged[i].nr != 0) {
                                    sendERR(i, -2);
                                    continue;
                                }
                                ok = trytologin(i, NR_USERS, pin, nr, users, logged);
                                if (ok == -1)
                                    check = wrongpin(nr, pin, notpin);
                                if (check == -1) {
                                    lock(nr, locked, users);
                                    check = 0;
                                    sendERR(i, -5);
                                }
                                break;


                            case 2:
                                if (logged[i].nr != 0) {
                                    memset(&logged[i], 0, sizeof(struct client));
                                    sprintf(sender, "Clientul a fost deconectat \n");
                                    send(i, sender, BUFLEN, 0);
                                } else {
                                    sendERR(i, -1);
                                }
                                break;

                            case 3:
                                if (logged[i].nr != 0) {
                                    sprintf(sender, "%.2f\n", logged[i].sold);
                                    send(i, sender, BUFLEN, 0);
                                } else {
                                    sendERR(i, -1);
                                }
                                break;

                            case 4:
                                nr = atoi(strtok(NULL, " "));
                                sum = atoi(strtok(NULL, " "));
                                if (logged[i].nr != 0) {
                                    if (getClientbyNR(nr, users) == NULL) {
                                        sendERR(i, -4);
                                        continue;
                                    }

                                    if (logged[i].sold < sum) {
                                        sendERR(i, -8);
                                        continue;
                                    }

                                    sprintf(sender, "Transfer %d catre %s %s? [y/n] \n", sum,
                                            getClientbyNR(nr, users)->nume, getClientbyNR(nr, users)->prenume);
                                    send(i, sender, BUFLEN, 0);
                                    memset(sender, 0, BUFLEN);
                                    memset(buffer, 0, BUFLEN);
                                    recv(i, buffer, sizeof(buffer), 0);
                                    if (buffer[0] == 'y') {
                                        aux1 = getClientbyNR(nr, users);
                                        aux2 = getClientbyNR(logged[i].nr, users);
                                        aux1->sold += sum;
                                        aux2->sold -= sum;

                                        syncc(users, logged, locked);

                                        sprintf(sender, "Transfer realizat cu succes \n");
                                        send(i, sender, BUFLEN, 0);
                                    } else {
                                        sendERR(i, -9);
                                    }

                                } else {
                                    sendERR(i, -1);
                                }
                                break;

                            case 5:
                                //TODO
                                break;

                            case 6:
                                memset(&logged[i], 0, sizeof(struct client));
                                break;

                            default:
                                printf("Wrong command m8! \n");
                                break;
                        }

                    }
                }
            }
        }
    }


    close(sockfd);

    return 0;
}


