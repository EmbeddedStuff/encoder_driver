#include "stdlib.h"
#include "encoder.h"

typedef enum{
	DIR_NONE,
	DIR_POSITIVE,
	DIR_NEGATIVE
} direction_t;

typedef struct{
	int last_a;
	int last_b;
	direction_t direction;
	int position;
} encoder_t;


encoder_handle encoder_new(void){
	encoder_t* pEncoder = malloc(sizeof(encoder_t));
	pEncoder->position=0;
	pEncoder->direction=DIR_NONE;
	pEncoder->last_a=1;
	pEncoder->last_b=1;
	return pEncoder;
}

int encoder_getPosition(encoder_handle eHandle){
	encoder_t* pEncoder = eHandle;
	return  pEncoder->position;
}

typedef enum{
	NO_EDGE,
	POSEDGE_A,
	POSEDGE_B,
	NEGEDGE_A,
	NEGEDGE_B
}edge_event;

edge_event get_event(encoder_t* pEncoder, int stateA, int stateB){
	if((pEncoder->last_a == 0) && (stateA == 1))
		return POSEDGE_A;
	else if((pEncoder->last_a == 1) && (stateA == 0))
		return NEGEDGE_A;
	else if((pEncoder->last_b == 0) && (stateB == 1))
		return POSEDGE_B;
	else if((pEncoder->last_b == 1) && (stateB == 0))
		return NEGEDGE_B;
	else
		return NO_EDGE;
}

void encoder_postEvent(encoder_handle eHandle, int stateA, int stateB){
	encoder_t* pEncoder = eHandle;
	edge_event event = get_event(pEncoder, stateA, stateB);
	direction_t dir = pEncoder->direction;
	
	if( dir == DIR_NONE){
		if((stateA == 0) && (stateB == 0)){
			if(event == NEGEDGE_A)
				dir = DIR_POSITIVE;
			else if(event == NEGEDGE_B)
				dir = DIR_NEGATIVE;
		}
	}else if((stateA == 1) && (stateB == 1)){
		if((event == POSEDGE_A) && (dir == DIR_POSITIVE)){
			pEncoder->position++;
			dir = DIR_NONE;	
		}else if((event == POSEDGE_B) && (dir == DIR_NEGATIVE)){
			pEncoder->position--;
			dir = DIR_NONE;
		}else if(event != NO_EDGE){
			dir = DIR_NONE;
		}
	}
	
	pEncoder->direction=dir;
	pEncoder->last_a=stateA;
	pEncoder->last_b=stateB;
}
