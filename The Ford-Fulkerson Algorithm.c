
#include <stdio.h>
#include <string.h>
#define file_in "maxflow.in"
#define file_out "maxflow.out"
#define DIM 1111

int Capacity[DIM][DIM],
    Flow[DIM][DIM],
    nodes, edges,
    explored[DIM];

int min(int a, int b) {
    if(a < b) return a;
    else return b;
}

void displayCapacity() {

  for(int i = 1; i <= nodes; ++i) {

    for(int j = 1; j <= nodes; ++j) {

      printf("%d ", Capacity[i][j]);
    }

    printf("\n");
  }
}

int bfs() {

    int Queue[DIM],
        first, last,
        x;

    memset(explored, 0,sizeof(explored));

    Queue[0] = 1;
    explored[1] = -1;
    first = last = 0;

    while( first <= last ) {

          x = Queue[ first ];

          for(int node = 1; node <= nodes; ++node) {

              if(!explored[ node ] && Capacity[ x ][ node ] > Flow[ x ][ node ]) {

                  explored[ node ] = x;

                  Queue[ ++last ] = node;

                  if (node == nodes) {return 1;}
              }
          }

          first++;
    }

    return 0;
}

int furkeson() {

    int value_r,
        maxflow = 0,
        i, j;

    for(;bfs();) {

    for(i = 1; i <= nodes; ++i) {

        if(explored[i]<=0 || Capacity[i][nodes]<=Flow[i][nodes]) {
           continue;
        }

        value_r = Capacity[i][nodes] - Flow[i][nodes];

        for(j = i; j != 1; j = explored[ j ]) {

            value_r = min(value_r, Capacity[ explored[j] ][j] - Flow[ explored[j] ][ j ] );
        }

        if (value_r == 0) continue;

        Flow[i][nodes] += value_r;

        Flow[nodes][i] -= value_r;

        for( j = i; j != 1; j=explored[ j ] ) {

          Flow[ explored[j] ][ j ] += value_r;

          Flow[j][ explored[j] ] -= value_r;
        }

        maxflow += value_r;
    }
  }
  return maxflow;
}

int main(int argc, char const *argv[]) {

  int x, y, c;

  freopen(file_in, "r", stdin);
  freopen(file_out, "w", stdout);

  scanf("%d %d", &nodes, &edges);

  while(edges--) {

        scanf("%d %d %d", &x, &y, &c);

        Capacity[ x ][ y ] = c;
  }

  printf("%d" , furkeson( ) );

  return 0;
}
