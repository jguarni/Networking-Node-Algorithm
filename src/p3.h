#define LINKCHANGES 0
#define   Y           1
#define   N            0
#define   INF   9999
#define   MAX_FILENAME_LENGTH  80
//Max number of nodes
#define  MAX_NODES    4

struct NeighborCosts   {
    int  NodesInNetwork;
    int  NodeCosts[MAX_NODES];
};

// Route packet sent to layer 3

struct RoutePacket {
   int sourceid;               // source sending this pkt
   int destid;                 // reciver ID of pkt being sent

   int mincost[MAX_NODES];     // 0..N Cost
};


void                  toLayer2( struct RoutePacket packet );
struct NeighborCosts *getNeighborCosts(int myNodeNumber);
