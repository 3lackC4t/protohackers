#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 32
#define PORT 9999

void handleError(const char *message, int socket_fd, int exitingFlag) {
  perror(message);

  if (socket_fd >= 0 && exitingFlag == 1) {
    close(socket_fd);
  }

  exit(EXIT_FAILURE);
}

void handleCommunication(int client_fd) {
  char buffer[BUFFER_SIZE];
  ssize_t bytes_recieved;

  while ((bytes_recieved = recv(client_fd, buffer, BUFFER_SIZE - 1, 0)) > 0) {

    buffer[bytes_recieved] = '\0';
    printf("Received %s\n", buffer);

    send(client_fd, buffer, bytes_recieved, 0);
  }

  if (bytes_recieved == 0) {
    printf("Client Disconnected.\n");
  } else {
    perror("recv() error");
  }

  close(client_fd);
}

void echoServer() {
  int server_fd, client_fd;
  struct sockaddr_in server_addr, client_addr;
  socklen_t addrlen = sizeof(client_addr);

  server_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (server_fd < 0) {
    handleError("Socket Failure", server_fd, 1);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    handleError("Socket Bind Failuer", server_fd, 1);
  }

  if (listen(server_fd, 10) < 0) {
    handleError("Socket Listen Failuer", server_fd, 1);
  }

  for (;;) {
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addrlen);

    if (client_fd < 0) {
      handleError("Server accept failure", client_fd, 0);
    }

    handleCommunication(client_fd);
  }

  close(server_fd);
}

int main(int argc, char const *argv[]) {
  echoServer();
  return 0;
}
