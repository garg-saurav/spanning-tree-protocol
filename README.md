# Spanning Tree Protocol
You can read about the protocol in this wikipedia [article](https://en.wikipedia.org/wiki/Spanning_Tree_Protocol).


### How to run the simulation?
Compilation command:
`g++ -o bsim main.cpp bridgesim.cpp bridge.cpp`

Running with input file:
`./bsim < ./Input/inp1`

### Input format
See example input files given in [Input](./Input/) folder.
The first line is the trace flag (set to 1 for detailed trace). Next line has the number of bridges. Each of the next line contains the bridge name followe by the LANs to which it is connected directly. I have assumed that bridge names are in the format B1, B2, etc. and LAN names are single characters. Bridge list is to be given in the order of its ID.
This is follwed by a list of host IDs per LAN and a set of data transfers.


### Output format
Each of the line contains a bridge name followed by the state of each port. State will be one of DP for designated port, RP for root port and NP for null port. If trace is ON, each of the output line in the trace is of the format `t s|r Bk (Bi, d, Bj)` Here t is time, Bk is the node ID, and (Bi, d, Bj) is the message indicating that Bridge Bj thinks Bridge Bi is the root and it is at a
distance d from the root.<br><br> This is followed by the forwarding tables at each bridge after each data transfer. Again, if the trace is ON. Each of the trace output line is of the format 
`t s|r Bk X --> Y` which means at time t, at Bridge Bk, a packet arrived (r) or was sent (s), where the packet source address was on LAN X and packet destination address was on LAN Y.

### License
This project is licensed under the MIT License. See the [LICENSE](./LICENSE.txt) file for the full license text.
