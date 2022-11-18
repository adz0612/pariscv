//#include "stddefs.h"
#include <stdint.h>

#include "murax.h"
#include "data.h"

////////////printers



//Calls output_char in a loop.


///////////


void putchar(char c){
	uart_write(UART, c);
}


static void printf_c(int c)
{
	putchar(c);
}


static void printf_d(int val)
{
	char buffer[32];
	char *p = buffer;
	if (val < 0) {
		printf_c('-');
		val = -val;
	}
	while (val || p == buffer) {
		*(p++) = '0' + val % 10;
		val = val / 10;
	}
	while (p != buffer)
		printf_c(*(--p));
}

int read_cycles(void)
{
int cycles;
asm volatile ("rdcycle %0" : "=r" (cycles));
return cycles;
}
void print(const char*str){
	while(*str){
		uart_write(UART,*str);
		str++;
	}
}
void println(const char*str){
	print(str);
	uart_write(UART,'\n');
}



/////bfs function
/*
void bfs (){

  int thislevel;
  int back, front;
  int i, v, w, e;
  back = 0;   
  front = 0;  
  thislevel = 0;
  level[0] = 0;
  levelsize[0] = 1;
  queue[back++] = 0;

  
  while (levelsize[thislevel] > 0) {
    levelsize[thislevel+1] = 0;
    for (i = 0; i < levelsize[thislevel]; i++) {
      v = queue[front++];       // v is the current vertex to explore from
      for (e = firstnbr[v]; e < firstnbr[v+1]; e++) {
        w = nbr[e];          // w is the current neighbor of v
        if (level[w] == -1) {   // w has not already been reached
          parent[w] = v;
          level[w] = thislevel+1;
          levelsize[thislevel+1]++;
          queue[back++] = w;    // put w on queue to explore
        }
      }
    }
    thislevel = thislevel+1;
  }
//if(level[100]==3)
//println("pass");
}*/
void BFSGraph() 
{
        int no_of_nodes = ver;          //number of vertices
        int edge_list_size = edg;       //edges
        int source = 0;

	
	int start, edgeno;   
	// initalize the memory


	
	//set the source node as true in the mask
	h_graph_active[0]=source; //true or false supported? lets see if bool is supported. it should be.
	h_graph_visited[source]=true;

	
	int id,cost;
	int tid,count1,count;

	// allocate mem for the result on host side
	//int* h_cost = (int*) malloc( sizeof(int)*no_of_nodes);
	
	h_cost[source]=0;
	count1=1;
        int cycles;
	int k=0;

	bool stop; //flag
	do
        {
            //if no thread changes this value then the loop stops
            stop=false;

           

count=0;
for(int j=0;j<count1;j++){
tid=h_graph_active[j];


                    for(int i=h_graph_nodes[tid].starting; i<(h_graph_nodes[tid].no_of_edges + h_graph_nodes[tid].starting); i++)
                    { //starting till no of edges
                        int id = h_graph_edges[i]; //where is it connected to.
                        if(!h_graph_visited[id]) //is it visited?
                        {
                            h_cost[id]=h_cost[tid]+1; //add teh cost.
                            h_updating_graph_active[count]=id; //add the neighbour to active list
                            count++;
                            stop=true;
                            h_graph_visited[id]=true;
                        }
                    }
                }
count1=count;
            

for(int c=0;c<count;c++){
h_graph_active[c]=h_updating_graph_active[c]+5;
}

for(int c=0;c<count;c++){
h_graph_active[c]=h_graph_active[c]-5;
}

        k++;

        }
	while(stop);
	// cleanup memory
//if(h_cost[100]==4)
//println("hi");
//if(h_cost[1020]==3)
//println("double");

}


//////

int main() {
    
 // println("hello world Ashuthosh1");
int a=read_cycles();
    BFSGraph();
int b=read_cycles();
printf_d(b-a);
println("\n");
  //println("hello world Ashuthosh");
  
}


void irqCallback(){
}





