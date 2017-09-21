//Grace Seiche - geseiche

#include "cachelab.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <math.h>

//If I were do to this project again, i would encapsulate some of these global variables in a
//struct for a cache containing an array sets and details about the cache. I would also change
//my check_something functions to return 1 if successful and 0 if not, rather than use did_hit.

//global variables regarding cache
unsigned long tick;//program clock
char mode; //instruction, load, store, or modify
unsigned long long address; //initially read in
unsigned size;//size of piece read
unsigned long long tag;//tag for currently read piece line of memory
unsigned long set_index;//set_index for currently read line of memory
int s = -1; //number of set bits
int S;//number of sets
int b = -1;//number of block bits
int E = -1;//number of lines
int t;//number of tag bits
int v =0;//verbose method or no
FILE* file = 0;//trace file
struct set* cache;//array of sets for caches
int hits = 0;//number of hits
int misses = 0;//number of misses
int evictions = 0;//number of evictions
int did_hit = 0;//has it hit/done most recent tack properly

//Line struct contains
// - int valid: either 1 or 0 representing a valid (filled) line or an invalid (empty) line respectively
// - unsigned long long tag: holds the tag value of the parsed line
// - unsigned long last_used: the most recent clock time when the line was hit in the cache
struct line {
	int valid;
	unsigned long long tag;
	unsigned long last_used;
};// struct line


//Set struct contains
// - struct line* lines: a pointer to an array of all the lines in the set
// - unsigned line_count: the number of lines in the set
struct set {
	struct line* lines;
	unsigned line_count;
};// struct set

// print_usage
// takes no arguements
// returns no parameters
// prints to console information regarding how to use the program correctly
// often implemented when there are invalid arguments
void print_usage(){
	//WRITE THIS FUNCTION
}// void print_usage()

// read_commands
// takes the main function arguments as paramenters
//  - int argc: the integer number of command line arguments
//  - char* argv[]: an array of strings containing the command line arguments
// returns no aguments
// sets the values of the global variables v, file, s, E, b, S, t
void read_commands (int argc, char* argv[]){
	int opt;
	int invalid = 0;
	// sort through the command line arguments and get the values for v, s, E, b, and t
	while((opt = getopt(argc, argv, "vhs:E:b:t:")) != -1) {
		switch (opt) {
		//if the user users -h, print the usage information and exit the program
		case 'h':
			print_usage();
			exit(-1);
		//optional argument; if v==1, will writer the verbose version of the program
		case 'v':
			v = 1;
			break;
		//open the file indicated by t flag in command line
		case 't':
			file = fopen(optarg, "r");
			break;
		//initializes the number of set bits
		case 's':
			s = atoi(optarg);
			break;
		//initializes the number of lines in a set
		case 'E':
			E = atoi(optarg);
			break;
		//initializes the number of block bits
		case 'b':
			b = atoi(optarg);
			break;
		//if all else fails, it is an invalid argument
		default:
			invalid = 1;
		}
	}

	//Validate args
	if(invalid || s == -1 || b == -1 || E == -1 || file == 0) {
		printf("Please give valid arguments\n");
		print_usage();
		exit(-1);
	}

	//Compute S
	S = pow(2,s);

	//Compute t
	t = 64 - s - b;
}//void read_commands(int argc, char* argv[])

//parse_line
//takes no parameters
//returns void
//reads one line and store the mode, address, and size
//then computes the tag set_index from the address
void parse_line (){
	fscanf(file, " %c %llx,%x\n", &mode, &address, &size);
	tag = address >> (s + b);
	set_index = (address << t) >> (t + b);
}//void parse_line()

//make_cache
//takes no parameters
//returns no arguments
//dynamically allocates memory space for the cache
void make_cache (){
	//allocate space for sets
	cache = (struct set*)malloc(S*sizeof(struct set));
	for(int i=0; i<S; i++){
		//allocate space for lines
		cache[i].lines = malloc(E*sizeof(struct line));
	}
}//void make_cache ()

//free_cache
//takes no parameters
//returns no arguments
//frees the memory allocated for the cache
void free_cache (){
	for(int i=0; i<S; i++){
		free(cache[i].lines);
	}
	free(cache);
}//void free_cache ()

//check_if_hit
//takes no parameters
//returns void
//iterates through the lines in the set (decided by set_index) and determines if a cache hit occurs
//(i.e. the tags match and it is valid), if so, increments hits by 1 and sets did_hit to one)
void check_if_hit (){
	for(int i=0; i<E; i++){
		//checks for hit in indexed line (chosen by i)
		if(cache[set_index].lines[i].tag==tag && cache[set_index].lines[i].valid==1){
			cache[set_index].lines[i].last_used = tick;//update last_used to reflect the hit
			hits++;//increase hits counter
			did_hit = 1;
			return;
		}
	}
}//void check_if_hit

//check_if_open_line
//takes no parameters
//returns void
//checks all lines in set (indicated by set_index) and determines if there is an empty line, if so,
//it makes that line valid and places the recently parsed data into that line
//chooses the first empty line and returns; if no lines are empty, return without modifying anything
void check_if_open_line(){
	for(int i = 0; i<E; i++){
		//check whether this line in empty
		if(cache[set_index].lines[i].valid==0){
			//insert recent data into empty line
			cache[set_index].lines[i].valid = 1;
			cache[set_index].lines[i].tag = tag;
			cache[set_index].lines[i].last_used = tick;
			did_hit = 1;
			return;
		}
	}
}//void check_if_open_line

//evict_LRU
//take no parameters
//return void
//run through all lines in given set and find the least recently used line
//replace the data in the least recently used line with the data from the recent parse
void evict_LRU (){
	//set the lru data to that of the data in line[0]
	int lru_time = cache[set_index].lines[0].last_used;
	int lru = 0;
	//iterate through the following lines comparing it to the lru data
	for(int i=1; i<E;i++){
		if(cache[set_index].lines[i].last_used <= lru_time){
			//if the data in the current index is older than the lru data, replace the lru with the current index data
			lru_time = cache[set_index].lines[i].last_used;
			lru = i;
		}
	}
	//printf("%llx ", cache[set_index].lines[lru].tag);
	//replace the least recently used line data with the recently parsed data
	cache[set_index].lines[lru].tag = tag;
	cache[set_index].lines[lru].last_used = tick;
	//increment the eviction count
	evictions++;
}//void evict_LRU()

//main
//takes in the command line arguments in argc and argv
//returns 0 if correctly executed
//simulate the cache hits misses and evictions
int main(int argc, char* argv[]) {
	tick = 0;//set program clock
	read_commands(argc, argv);
	make_cache();

	//main loop that repeats for each line of valgrind output that it reads
	while (!feof(file)){//while there are more lines of code to access
		did_hit = 0;
		do{
			parse_line();
		} while (mode == 'I');//parse a line, as long as it is not an instruction I, keep going
		if(v){
			printf("%c %llx, %d ", mode, address, size);
		}
		//check if in cache
		check_if_hit();
		//if cache hit
		if(did_hit && v){
			printf("hit ");
		}
		//if not cache hit
		if(!did_hit){
			//printf("%llx ", tag);
			//increment misses
			misses++;
			if(v){
				printf("miss ");
			}
			//check if open spot in cache
			check_if_open_line();
			//if no open spot in the cache
			if(!did_hit){
				//evict
				evict_LRU();
				if(v){
					printf("eviction ");
				}
			}
		}
		//if a modify, then add a hit because modify is load and store, but store is always a hit in modify
		if (mode == 'M'){
			if(v){
				printf("hit ");
			}
			hits++;
		}
		if(v){
			printf("\n");//terminate printed line
		}
		tick++;//increase clock time
	}

	//finishing details
	fclose(file);
	free_cache();
    printSummary(hits, misses, evictions);
    return 0;
}//int main (int argc, char* argv[])


