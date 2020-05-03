#include"utils.h"

void print_byte_array(uint8_t *arr ,uint32_t len){
    for(uint32_t i = 0 ; i < len ; i++){
        printf("%x ",arr[i]);
    }
    printf("\n");
}

uint8_t* string_to_byte_array(int8_t *input, uint32_t len){
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


struct unsigned_txn* byte_array_to_struct(uint8_t *input, uint32_t len){
    uint32_t offset = 0;
    struct unsigned_txn *output = (struct unsigned_txn*)malloc(sizeof(struct unsigned_txn));
    memcpy(output,input+offset,VERSION_LEN+NUMBER_OF_INPUTS_LEN);
    offset += VERSION_LEN+NUMBER_OF_INPUTS_LEN;
    output->inputs = (struct unsigned_txn_inputs*)malloc(sizeof(struct unsigned_txn_inputs)*output->no_of_inputs);
    
    uint8_t i = 0;
    while(i < output->no_of_inputs){
        memcpy((void*)&output->inputs[i],input+offset,PREV_TXN_HASH_LEN+PREV_OUTPUT_INDEX_LEN+SCRIPT_LENGTH_LEN);
        offset += PREV_TXN_HASH_LEN+PREV_OUTPUT_INDEX_LEN+SCRIPT_LENGTH_LEN;
        output->inputs[i].script = (uint8_t*)malloc(output->inputs[i].script_len);
        memcpy(output->inputs[i].script,input+offset,output->inputs[i].script_len);
        offset+=output->inputs[i].script_len;
        memcpy((void*)&output->inputs[i].squence,input+offset,SEQ_LEN);
        offset+=SEQ_LEN;
        i++;
    } 
    memcpy((void*)&output->no_of_outputs,input+offset,NUMBER_OF_OUTPUTS_LEN);
    offset+=NUMBER_OF_OUTPUTS_LEN;

    output->outputs = (struct unsigned_txn_outputs*)malloc(sizeof(struct unsigned_txn_outputs)*output->no_of_outputs);

    i = 0;

    while(i < output->no_of_outputs){
        memcpy((void*)&output->outputs[i],input+offset,VALUE_LEN+SCRIPT_LENGTH_LEN);
        offset+=VALUE_LEN+SCRIPT_LENGTH_LEN;
        output->outputs[i].script_public_key = (uint8_t*)malloc(output->outputs[i].script_len);
        memcpy(output->outputs[i].script_public_key,input+offset,output->outputs[i].script_len);
        offset+=output->outputs[i].script_len;
        i++;
    }

    memcpy(output->lock_time,input+offset,LOCKTIME_LEN+SIG_HASH_CODE_LEN);
    return output;
}