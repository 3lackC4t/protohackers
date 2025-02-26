#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 32
#define PORT 9999

void handleCommunication() {
  // Will handle incoming communications
}

void echoServer() {
  int server_fd, bind_fd, listen_fd;
  struct sockaddr_in server_addr;
  socklen_t addrlen = sizeof(server_addr);
  char buffer[BUFFER_SIZE] = {0};

  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
    perror("Socket Failed");
    exit(EXIT_FAILURE);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  bind_fd = bind(server_fd, (struct sockaddr *)&server_addr,
                 sizeof(struct sockaddr_in));

  if (bind_fd < 0) {
    perror("Bind Failur");
    exit(EXIT_FAILURE);
  }

  listen_fd = listen(server_fd, 10);

  if (listen_fd < 0) {
    perror("Listen Failure");
    exit(EXIT_FAILURE);
  }

  for (;;) {
    accept_fd = accept(server_fd, (struct sockaddr *)&server_addr, addrlen);

    if (accept_fd == -1) {
      perror("Accept Failure");
      exit(EXIT_FAILURE);
    }
  }
}

int main(int argc, char const *argv[]) {
  echoServer();
  return 0;
}
