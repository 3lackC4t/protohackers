# protohackers
## Smoke Test:
Smoke test is a simple echo server. The basic process of which, in C, is to `socket()` create a socket, `bind()` the socket to a sockaddr_in type address and port, have the socket `listen()` on a the port, and then run an infinitely loop where the socket `accecpt()` connections and pass them off to a handler function. The handler function will `recv()` the data from the client and then immediately `send()` the data back

## Prime Time:
