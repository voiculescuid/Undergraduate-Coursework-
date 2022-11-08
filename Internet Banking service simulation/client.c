#include"head.h"

int main(int argc, char *argv[]) {
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char name[100];
    sprintf(name, "client-%d.log", getpid());
    FILE *file = fopen(name, "wt");
    char buffer[BUFLEN], com[BUFLEN];
    if (argc < 3) {
        fprintf(stderr, "./client <IP_server> <port_server>\n");
        exit(0);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    inet_aton(argv[1], &serv_addr.sin_addr);


    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    while (1) {
        //citesc de la tastatura
        memset(buffer, 0, BUFLEN);
        fgets(buffer, BUFLEN - 1, stdin);
        strcpy(com, buffer);
        //trimit mesaj la server
        n = send(sockfd, buffer, strlen(buffer), 0);
        if (n < 0)
            error("ERROR writing to socket");

        if (buffer[0] == 'q'){
            fprintf(file, "%s", com);
            break;
	}

        memset(buffer, 0, BUFLEN);
        if ((n = recv(sockfd, buffer, sizeof(buffer), 0)) <= 0) {
            if (n == 0) {
                //conexiunea s-a inchis
                printf("Server is shuting down \n");
                fprintf(file, "iBANK> Server is shuting down \n");
                close(sockfd);
                return 0;
            } else {
                error("ERROR in recv");
            }
        }

        if (buffer[0] == 'q') {
            printf("Server is shuting down \n");
            close(sockfd);
            return 0;
        }
        printf("iBANK> %s", buffer);
        fprintf(file, "%s", com);
        fprintf(file, "iBANK> %s", buffer);

    }

    close(sockfd);
    return 0;
}


