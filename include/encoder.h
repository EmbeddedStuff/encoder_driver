#ifndef ENCODER_H 
#define ENCODER_H 

typedef void* encoder_handle; 

encoder_handle encoder_new(void); 

int encoder_getPosition(encoder_handle eHandle);
void encoder_postEvent(encoder_handle eHandle, int stateA, int stateB);
void encoder_setOnChangeCallback(encoder_handle eHandle, void (*onChangeCallback)(encoder_handle));

#endif// ENCODER_H 

