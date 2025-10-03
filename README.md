# PortScan em C

Implementação simples de um scanner de portas TCP escrito em C.

## Requisitos

- Compilador C compatível com o padrão C99 ou superior (por exemplo `gcc`).
- Sistema operacional baseado em Unix (Linux, macOS ou WSL) com a biblioteca de sockets BSD.

## Compilação

```bash
gcc -O2 -Wall -Wextra -pedantic portscan.c -o portscan
```

## Uso

```bash
./portscan <host> [porta_inicial] [porta_final]
```

- `host`: endereço IPv4 ou nome DNS do alvo.
- `porta_inicial`: (opcional) porta inicial do intervalo. Padrão: `0`.
- `porta_final`: (opcional) porta final do intervalo. Padrão: `65535`.

Exemplo, para escanear as portas de 20 a 1024 de `scanme.nmap.org`:

```bash
./portscan scanme.nmap.org 20 1024
```

O programa mostra na saída padrão apenas as portas que foram encontradas abertas.

## Aviso legal

Utilize este programa apenas em redes e sistemas para os quais você tem autorização.
O uso não autorizado de ferramentas de varredura de portas pode violar leis locais ou
políticas de uso aceitável da rede.
