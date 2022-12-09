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

asm(".set abiname_zero, 0");
asm(".set abiname_ra , 1");
asm(".set abiname_sp , 2");
asm(".set abiname_gp , 3");
asm(".set abiname_tp , 4");
asm(".set abiname_t0 , 5");
asm(".set abiname_t1 , 6");
asm(".set abiname_t2 , 7");
asm(".set abiname_s0 , 8");
asm(".set abiname_s1 , 9");
asm(".set abiname_a0 , 10");
asm(".set abiname_a1 , 11");
asm(".set abiname_a2 , 12");
asm(".set abiname_a3 , 13");
asm(".set abiname_a4 , 14");
asm(".set abiname_a5 , 15");
asm(".set abiname_a6 , 16");
asm(".set abiname_a7 , 17");
asm(".set abiname_s2 , 18");
asm(".set abiname_s3 , 19");
asm(".set abiname_s4 , 20");
asm(".set abiname_s5 , 21");
asm(".set abiname_s6 , 22");
asm(".set abiname_s7 , 23");
asm(".set abiname_s8 , 24");
asm(".set abiname_s9 , 25");
asm(".set abiname_s10 , 26");
asm(".set abiname_s11 , 27");
asm(".set abiname_t3 , 28");
asm(".set abiname_t4 , 29");
asm(".set abiname_t5 , 30");
asm(".set abiname_t6 , 31");

///////////
#define SIMD_ADD(src1, src2, result) \
asm volatile(  \
".word ((0b0000011 << 25) | (abiname_%2 << 20) | (abiname_%1 << 15) | (0b000 << 12) | (abiname_%0 << 7) | 0b0110011) \n\t" \
: "=r"(result)    \
: "r" (src1), "r" (src2) \
) 


#define ADI_ADD(src1, src2, result) \
asm volatile(  \
".word ((0b0000011 << 25) | (abiname_%2 << 20) | (abiname_%1 << 15) | (0b000 << 12) | (abiname_%0 << 7) | 0b0110010) \n\t" \
: "=r"(result)    \
: "r" (src1), "r" (src2) \
) 



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
	int proc1,proc2=0;
	
	int start, edgeno;   
	// initalize the memory


	int id,cost;
	int tid,count1,count,count2,count3,next1,next2;

	//set the source node as true in the mask
	if(h_own1[source]==-1){
	h_graph_active2[0]=source; 
		count3=1;//true or false supported? lets see if bool is supported. it should be.
//	h_graph_visited[source]=true;
	}
	else
	{
	h_graph_active1[0]=source;
		count1=1;
	}
	
	// allocate mem for the result on host side
	//int* h_cost = (int*) malloc( sizeof(int)*no_of_nodes);
	
	h_cost1[source]=0;
        h_cost2[source]=0;
	//count1=1;
        count2=0;
        count3=0;
        int cycles;
	int k=0;
        int local=0;

	bool stop; //flag
	do
        {
            //if no thread changes this value then the loop stops
       //     stop=false;

           stop=false;
k++;


count=0;
next1=1;
for(int j=0;j<count1;j++){
local=h_graph_active1[j];
tid=h_own1[local];
                    for(int i=h_graph_nodes1[tid]; i< h_graph_nodes1[tid+1]; i++)
                    { //starting till no of edges
                        int id = h_graph_edges1[i]; //where is it connected to.
			if(h_cost1[id]<0){
                           if(h_own1[id]>=0){
                                	h_cost1[id]=k;
					h_updating_graph_active1[count]=id;		
					count=count+1;
		                        }
				 else{
				h_cost1[id]=k;
				common2[next1]=id;
                                next1=next1+1;
 
                                      }
                          

                               }     
                        
                    }
}
common2[0]=next1;


count2=0;
next2=1;
//int a=read_cycles();

for(int j=0;j<count3;j++){
local=h_graph_active2[j];
tid=h_own2[local];
                    for(int i=h_graph_nodes2[tid]; i< h_graph_nodes2[tid+1]; i++)
                    { //starting till no of edges
                        int id = h_graph_edges2[i]; //where is it connected to.
			if(h_cost2[id]<0){
                           if(h_own2[id]>=0){
                                	h_cost2[id]=k;
					h_updating_graph_active2[count2]=id;		
					count2=count2+1;
		                        }
				  else{
				h_cost2[id]=k;
				common1[next2]=id;
				next2=next2+1;
                               }     


                                      }
                         
                        
                    }
}
common1[0]=next2;
//int b=read_cycles();

///////////////////////
//postprocessing in core 1

for(int c=1;c<common1[0];c++){
int id = common1[c]; //where is it connected to.
			if(h_cost1[id]<0){
                                	h_cost1[id]=k;
					h_updating_graph_active1[count]=id;		
					count=count+1;
		                        }
                           
}
count1=count;
for(int c=0;c<count;c++){
h_graph_active1[c]=h_updating_graph_active1[c];
}

//int c=read_cycles();

//////////////////////////
//post processing in core 2
for(int c=1;c<common2[0];c++){
int id = common2[c]; 
			if(h_cost2[id]<0){
                                	h_cost2[id]=k;
					h_updating_graph_active2[count2]=id;		
					count2=count2+1;
		                        }
                           
}
count3=count2;

for(int c=0;c<count2;c++){
h_graph_active2[c]=h_updating_graph_active2[c];
}
//int d=read_cycles();
//////
//print("proc 1 is");
//printf_d(count);
//print("proc 2 is");
//printf_d(count2);
//println("\n");
if(count!=0)
stop=true;
if(count2!=0)
stop=true;
//printf_d((b-a)+(d-c));
//println("\n");
        }
	while(stop);
//if(h_cost1[100]==4)
//println("hi");

//if(h_cost1[1020]==3)
//println("double");

}


//////

int main() {
    
 // println("hello world Ashuthosh1");
int a=read_cycles();
    BFSGraph();
int b=read_cycles();
//printf_d(b-a);
//println("\n");

/*
for(int i=0;i<512;i++)
{
printf_d(h_cost1[i]);
print(",");
if(i%100==0)
print("\n");
}
for(int i=512;i<1024;i++)
{
printf_d(h_cost2[i]);
print(",");
if(i%100==0)
print("\n");
}*/
/*
for(int i=512;i<1024;i++)
{
printf_d(1);
print(",");
if(i%100==0)
print("\n");
}
for(int i=512;i<1024;i++)
{
printf_d(0);
print(",");
if(i%100==0)
print("\n");
}*/

int p=0;
for(int i=0;i<1024;i++)
{
//printf_d(i);
//print("-1,");
if(h_own1[i]>=0)
{
printf_d(h_cost1[i]);
print(",");
//p++;
}
else{
//if(h_own1[i]==0)
//{
//printf_d(p);
//print(",");
//p++;
printf_d(h_cost2[i]);
print(",");

}

if(i%100==0)
print("\n");
}
//printf_d(p);

/*
for(int i=0;i<512;i++)
{
printf_d(i);
print(",");
if(i%100==0)
print("\n");
}
*/
//printf_d(h_graph_nodes[512]);
  //println("hello world Ashuthosh");
  
}


void irqCallback(){
}





