#include <stdio.h>
#include "p3.h"

extern int TraceLevel;
extern float clocktime;

struct distance_table {
  int costs[MAX_NODES][MAX_NODES];
};
struct distance_table distance_T3;
struct NeighborCosts   *N3;

/* students to write the following two routines, and maybe some others */

// local vars
struct RoutePacket RPACKET;

// prototype functions
void printdt3( int MyNodeNumber, struct NeighborCosts *neighbor, struct distance_table *dtptr );

void rtinit3() {
    int i, j;
    struct distance_table *thisnode3;

    thisnode3 = &distance_T3;

    // set the temporary packet mincosts to INFINITY
    RPACKET.mincost[0] = INF;
    RPACKET.mincost[1] = INF;
    RPACKET.mincost[2] = INF;
    RPACKET.mincost[3] = INF;

    printf("At time t = %f, rtinit3() called\n", clocktime);

    // set links from node i to node j as INFINITY
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            thisnode3->costs[i][j]= INF;
        }
    }

    N3 = getNeighborCosts(3);

    // link weight from node 0
    thisnode3->costs[0][0] = N3->NodeCosts[0];
    thisnode3->costs[1][1] = N3->NodeCosts[1];
    thisnode3->costs[2][2] = N3->NodeCosts[2];
    thisnode3->costs[3][3] = N3->NodeCosts[3];

    // check each distance from node i to node j in comparison to our somePacket
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (RPACKET.mincost[i] > thisnode3->costs[i][j]) {
                RPACKET.mincost[i] = thisnode3->costs[i][j];
            }
        }
    }

    // set somePacket's sourceID to 3 (we're in node3)
    // use tolayer2 to send to another node, depending on the destID
    RPACKET.sourceid = 3;
    RPACKET.destid = 0;
    toLayer2(RPACKET);
    printf("At time t = %f, node 3 sends packet to node 0 with: %d %d %d %d\n", clocktime, RPACKET.mincost[0], RPACKET.mincost[1], RPACKET.mincost[2], RPACKET.mincost[3]);

    RPACKET.destid = 1;
    toLayer2(RPACKET);
    printf("At time t = %f, node 3 sends packet to node 1 with: %d %d %d %d\n", clocktime, RPACKET.mincost[0], RPACKET.mincost[1], RPACKET.mincost[2], RPACKET.mincost[3]);

    RPACKET.destid = 2;
    toLayer2(RPACKET);
    printf("At time t = %f, node 3 sends packet to node 2 with: %d %d %d %d\n", clocktime, RPACKET.mincost[0], RPACKET.mincost[1], RPACKET.mincost[2], RPACKET.mincost[3]);

    printdt3(3, N3, thisnode3);
    printf("We are done with rtinit3 routine\n");
}


void rtupdate3( struct RoutePacket *rcvdpkt ) {
    int i, j, rcvdSource, update = 0;
    struct distance_table *thisnode3;

    thisnode3 = &distance_T3;

    for (i = 0; i < 4; i++) {
            RPACKET.mincost[i] = INF;
    }

    printf("Now we are in rtupdate3()\n");

    // check what sourceID of received packet is
    rcvdSource = rcvdpkt->sourceid;
    printf("Received packet's source ID is %d\n", rcvdSource);

    for (i = 0; i < 4; i++) {
        // go through and see if we need to update distance-table with new mincost
        if (thisnode3->costs[i][rcvdSource] > (thisnode3->costs[rcvdSource][rcvdSource] + rcvdpkt->mincost[i])) {
            thisnode3->costs[i][rcvdSource] = (thisnode3->costs[rcvdSource][rcvdSource] + rcvdpkt->mincost[i]);
            update = 1;
        }
    }

    // for this case, we update distance table
    if (update == 1) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (RPACKET.mincost[i] > thisnode3->costs[i][j]) {
                    RPACKET.mincost[i] = thisnode3->costs[i][j];
                }
            }
        }
        printf("We updated distance table from rtupdate3()\n");

        // set somePacket's sourceID to 3 (we're in node3)
        // use tolayer2 to send to another node, depending on the destID
        RPACKET.sourceid = 3;
        RPACKET.destid = 0;
        toLayer2(RPACKET);
        printf("At time t = %f, node 3 sends packet to node 0 with: %d %d %d %d\n", clocktime, RPACKET.mincost[0], RPACKET.mincost[1], RPACKET.mincost[2], RPACKET.mincost[3]);

        RPACKET.destid = 1;
        toLayer2(RPACKET);
        printf("At time t = %f, node 3 sends packet to node 1 with: %d %d %d %d\n", clocktime, RPACKET.mincost[0], RPACKET.mincost[1], RPACKET.mincost[2], RPACKET.mincost[3]);

        RPACKET.destid = 2;
        toLayer2(RPACKET);
        printf("At time t = %f, node 3 sends packet to node 2 with: %d %d %d %d\n", clocktime, RPACKET.mincost[0], RPACKET.mincost[1], RPACKET.mincost[2], RPACKET.mincost[3]);
    }

    printdt3(3, N3, thisnode3);

    printf("We are done with rtupdate3()\n");
}


/////////////////////////////////////////////////////////////////////
//  printdt
//  This routine is being supplied to you.  It is the same code in
//  each node and is tailored based on the input arguments.
//  Required arguments:
//  MyNodeNumber:  This routine assumes that you know your node
//                 number and supply it when making this call.
//  struct NeighborCosts *neighbor:  A pointer to the structure 
//                 that's supplied via a call to getNeighborCosts().
//                 It tells this print routine the configuration
//                 of nodes surrounding the node we're working on.
//  struct distance_table *dtptr: This is the running record of the
//                 current costs as seen by this node.  It is 
//                 constantly updated as the node gets new
//                 messages from other nodes.
/////////////////////////////////////////////////////////////////////
void printdt3( int MyNodeNumber, struct NeighborCosts *neighbor, 
		struct distance_table *dtptr ) {
    int       i, j;
    int       TotalNodes = neighbor->NodesInNetwork;     // Total nodes in network
    int       NumberOfNeighbors = 0;                     // How many neighbors
    int       Neighbors[MAX_NODES];                      // Who are the neighbors

    // Determine our neighbors 
    for ( i = 0; i < TotalNodes; i++ )  {
        if (( neighbor->NodeCosts[i] != INF ) && i != MyNodeNumber )  {
            Neighbors[NumberOfNeighbors] = i;
            NumberOfNeighbors++;
        }
    }
    // Print the header
    printf("                via     \n");
    printf("   D%d |", MyNodeNumber );
    for ( i = 0; i < NumberOfNeighbors; i++ )
        printf("     %d", Neighbors[i]);
    printf("\n");
    printf("  ----|-------------------------------\n");

    // For each node, print the cost by travelling thru each of our neighbors
    for ( i = 0; i < TotalNodes; i++ )   {
        if ( i != MyNodeNumber )  {
            printf("dest %d|", i );
            for ( j = 0; j < NumberOfNeighbors; j++ )  {
                    printf( "  %4d", dtptr->costs[i][Neighbors[j]] );
            }
            printf("\n");
        }
    }
    printf("\n");
}    // End of printdt3

