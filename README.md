# LoadBalancer

## About
in this project, we explore basic socket communication in C.

the load balancer gets requests from the internet, and forwards them to be processed on backend servers, instead of proccessing them itself.

## How-to
For this you will need 2+ terminals, (one for the servers, and one for the load balancer)

from the first terminal navigate to this project's directory and start the LB.
note - the LB generates a random port number and places it inside the file `server_port` and `http_port`, we will use them later.

```
make
./lb
```

Now from a different terminal, start the server

```
./server `cat server_port`
```

Now you can use your browser and check if it works!

in your browser navigate to 
```
127.0.0.1:<http_port>/counter
```
if for example the number in the file `http_port` is 41571:

```
127.0.0.1:41571/counter
```

Each server will return how many times it got the `counter` request.


# if you want more than one server

- you can use extra terminals and from each terminal run the above commmands

- or from the same terminal:

    ```
    ./server `cat server_port`
    disown
    ./server `cat server_port`
    disown
    ```
    which will result in 2 backend servers, Just make sure to kill the processes once you're done! 

    (you can view the processes with the `ps` command 
    and kill them with `kill <pid>`)





