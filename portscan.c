#include <netdb.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 4) {
        fprintf(stderr,
                "Uso: %s <IP ou host> [porta_inicial] [porta_final]\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    const char *destino = argv[1];
    long inicio = 0;
    long fim = 65535;

    if (argc >= 3) {
        inicio = strtol(argv[2], NULL, 10);
    }
    if (argc == 4) {
        fim = strtol(argv[3], NULL, 10);
    }

    if (inicio < 0 || inicio > 65535 || fim < 0 || fim > 65535 || inicio > fim) {
        fprintf(stderr, "Intervalo de portas inválido: %ld-%ld\n", inicio, fim);
        return EXIT_FAILURE;
    }

    struct addrinfo hints;
    struct addrinfo *resultado;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;      // IPv4
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(destino, NULL, &hints, &resultado);
    if (status != 0) {
        fprintf(stderr, "Erro ao resolver host '%s': %s\n", destino,
                gai_strerror(status));
        return EXIT_FAILURE;
    }

    struct sockaddr_in alvo;
    memcpy(&alvo, resultado->ai_addr, sizeof(alvo));
    freeaddrinfo(resultado);

    for (long porta = inicio; porta <= fim; porta++) {
        int meusocket = socket(AF_INET, SOCK_STREAM, 0);
        if (meusocket < 0) {
            perror("socket");
            return EXIT_FAILURE;
        }

        alvo.sin_port = htons((uint16_t)porta);

        int conecta = connect(meusocket, (struct sockaddr *)&alvo, sizeof(alvo));

        if (conecta == 0) {
            printf("Porta %ld - status [ABERTA]\n", porta);
        }

        close(meusocket);
    }

    return EXIT_SUCCESS;
}
