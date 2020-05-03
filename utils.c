#include"utils.h"


uint8_t* __stou8(int8_t *input, uint32_t len){
    //lenght of byte array will always be half of string
    uint8_t* output = (uint8_t*)malloc(((len+1)/2));
    uint32_t o,i;
    o = i = 0;
    while(i<len){
        if(input[i]>='a'){
            input[i]-='a'-10;
        }else if(input[i]>='A'){
            input[i]-='A'-10;
        }else{
            input[i]-='0';
        }
        output[o] = output[o] | input[i];
        if(i%2==0){
            output[o] = output[o]<<4;
        }else{
            o++;
        }
        i++;
    }
    return output;
}

