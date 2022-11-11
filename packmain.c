//#include "stddefs.h"
#include <stdint.h>

#include "murax.h"
#include "data.h"
//#include "riscv_asm.h"
//#include "sim_asm.h"
//#include "custom_asm.h"
////////////printers



//#define r_type_insn(_f7, _rs2, _rs1, _f3, _rd, _opc) \
asm volatile( \
".word (((" #_f7 ") << 25) | ((regnum_%0) << 20) | ((regnum_%1) << 15) | ((" #_f3 ") << 12) | ((regnum_%2) << 7) | ((" #_opc ") << 0));"  \
: "=r"(_rd) \
: "r" (_rs1), "r" (_rs2) \
);


//#define SIMD_ADD(_rd, _rs1, _rs2 ) \
r_type_insn(0b0000011, _rs2, _rs1, 0b000, _rd, 0b0110011)


//Calls output_char in a loop.
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
void putchar(char c){
	uart_write(UART, c);
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
	h_graph_mask[source]=true; //true or false supported? lets see if bool is supported. it should be.
	h_graph_visited[source]=true;

	
	int id,cost;
	

	// allocate mem for the result on host side
	//int* h_cost = (int*) malloc( sizeof(int)*no_of_nodes);
	
	h_cost[source]=0;
	int rd=0;
        int cycles;
	int k=0;
        int boom=0;
	bool stop; //flag
	do
        {
            //if no thread changes this value then the loop stops
            stop=false;

           for(int tid1 = 0; tid1 <  32; tid1++ ) //all nodes. row wise
            {
                 for(int tid2 = 0; tid2 < 32; tid2++ ) //all nodes. row wise
          	   {

//                    if(((h_graph_mask[tid1]>>tid2)&0x01))
//asm volatile("opcode_R(CUSTOM0,0x0,0x00,x3,x1,x2)");
SIMD_ADD(h_graph_mask[tid1],tid2,rd);
//if(((h_graph_mask[tid1]>>tid2)&0x01)){
if(rd){
                                                   h_graph_mask[tid1]=(~(1<<tid2))&h_graph_mask[tid1];
//ADI_ADD(tid1,tid2,boom);
boom=(tid1*32)+tid2;
                             for(int i=h_graph_nodes[boom].starting; i<(h_graph_nodes[boom].no_of_edges + h_graph_nodes[boom].starting); i++)
                    			{ //starting till no of edges
                        			int id = h_graph_edges[i];
                                                SIMD_ADD(h_graph_visited[id/32],(id%32),rd);
                                                if(!rd){
                                                //if(!((h_graph_visited[id/32]>>(id%32))&0x01))
                                               //	{
                            					h_cost[id]=h_cost[boom]+1; //add the cost.
                                                		stop=true;
                                                                h_updating_graph_mask[id/32]=((1<<(id%32)))|h_updating_graph_mask[id/32];

//								custom_set(h_updating_graph_mask[id],h_updating_graph_mask[id],id); 
							}
					}
				}
			}
		}
                 
            for(int tid=0; tid< 32 ; tid++ ) 
            {
              h_graph_mask[tid]=h_graph_mask[tid]|h_updating_graph_mask[tid];		
              h_graph_visited[tid]=h_graph_visited[tid]|h_updating_graph_mask[tid];
		h_updating_graph_mask[tid]=0;
            }
        k++;
            
        }
	while(stop);
	// cleanup memory
if(h_cost[100]==4){
println("Ash");
printf_d(45);
}
}


//////

int main() {
    
 // println("hello world Ashuthosh1");
 int a,b;
a=read_cycles();
    BFSGraph();
b=read_cycles();
printf_d(b-a);
 // println("hello world Ashuthosh");
  
}


void irqCallback(){
}




