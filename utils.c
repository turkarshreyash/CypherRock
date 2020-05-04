#include"utils.h"

uint32_t uint8_t_array_to_uint32_t(uint8_t *arr){
    uint32_t temp = 0;
    for(int8_t i = 0; i < 4; i++){
        temp = temp<<8;
        temp = temp|arr[i];
    }
    return temp;
}

void print_byte_array(uint8_t *arr ,uint32_t len){
    for(uint32_t i = 0 ; i < len ; i++){
        printf("%02x ",arr[i]);
    }
    printf("\n");
}

/*
  uint32_t depth;
  uint32_t child_num;
  uint8_t chain_code[32];

  uint8_t private_key[32];
  uint8_t private_key_extension[32];

  uint8_t public_key[33];
  const curve_info *curve;
*/
void print_hdnode(HDNode* node){
    printf("Depth: %x\n",node->depth);
    printf("Child Num: %x\n",node->child_num);
    printf("Chain code: ");print_byte_array(node->chain_code,CHAIN_CODE_LEN);
    printf("Private Key: ");print_byte_array(node->private_key,PRIVATE_KEY_LEN);
    printf("Private Key Ext: ");print_byte_array(node->private_key_extension,PRIVATE_KEY_LEN);
    printf("Public Key: ");print_byte_array(node->public_key,PUBLIC_KEY_LEN);
}

void print_txn_metadata(struct txn_metadata input){
    printf("purpose index: ");print_byte_array(input.purpose_index,INDEX_SIZE);
    printf("coin index: ");print_byte_array(input.coin_index,INDEX_SIZE);
    printf("account index: ");print_byte_array(input.account_index,INDEX_SIZE);
    printf("no of inputs: %x\n",input.input_count);
    for(uint8_t i = 0 ; i < input.input_count ; i++){
        printf("input(%d) Address Index: ",i);print_byte_array(input.inputs[i].address_index,INDEX_SIZE);
        printf("input(%d) Chain Index: ",i);print_byte_array(input.inputs[i].chain_index,INDEX_SIZE);
    }
    printf("no of outputs: %x\n",input.output_count);
    for(uint8_t i = 0 ; i < input.output_count ; i++){
        printf("output(%d) Address Index: ",i);print_byte_array(input.outputs[i].address_index,INDEX_SIZE);
        printf("output(%d) Chain Index: ",i);print_byte_array(input.outputs[i].chain_index,INDEX_SIZE);
    }
    printf("no of change: %x\n",input.change_count);
    for(uint8_t i = 0 ; i < input.change_count ; i++){
        printf("change(%d) Address Index: ",i);print_byte_array(input.changes[i].address_index,INDEX_SIZE);
        printf("change(%d) Chain Index: ",i);print_byte_array(input.changes[i].chain_index,INDEX_SIZE);
    }
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

struct txn_metadata* txn_to_byte_array(uint8_t* input, uint16_t len){
    struct txn_metadata *output = (struct txn_metadata*)malloc(sizeof(struct txn_metadata));
    uint16_t offset = 0;

    memcpy((void*)output,input+offset,(INDEX_SIZE*3)+1);
    offset += INDEX_SIZE*3+1;
    
    output->inputs = (struct node*)malloc(sizeof(struct node)*output->input_count);
    
    memcpy((void*)output->inputs,input+offset,INDEX_SIZE*2*output->input_count);
    offset += INDEX_SIZE*2*output->input_count;
    
    memcpy((void*)&output->output_count,input+offset,1);
    // output->output_count=input[offset];
    offset += 1;
    
    output->outputs = (struct node*)malloc(sizeof(struct node)*output->output_count);
    
    memcpy((void*)output->outputs,input+offset,INDEX_SIZE*2*output->output_count);
    offset += INDEX_SIZE*2*output->output_count;
    
    memcpy((void*)&output->change_count,input+offset,1);
    // output->change_count=input[offset];
    offset += 1;
    
    output->changes = (struct node*)malloc(sizeof(struct node)*output->change_count);
    
    memcpy((void*)output->changes,input+offset,INDEX_SIZE*2*output->change_count);
    offset += INDEX_SIZE*2*output->change_count;
    
    return output;
}