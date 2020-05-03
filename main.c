#include<stdio.h>
#include<string.h>

#include"structures.h"
#include"utils.h"

void print_byte_array(uint8_t *arr ,uint32_t len){
    for(uint32_t i = 0 ; i < len ; i++){
        printf("%x ",arr[i]);
    }
    printf("\n");
}



int main(int argc, char* args[]){
    if(argc<2){
        printf("Byte Array Invalid\n");
        exit(0);
    }
    
    int8_t *unsigned_txn_string = args[1];
    uint32_t unsigned_txn_string_len = strlen(unsigned_txn_string);

    uint8_t *byte_array = string_to_byte_array(unsigned_txn_string, unsigned_txn_string_len);

    print_byte_array(byte_array,(unsigned_txn_string_len+1)/2);


    struct unsigned_txn* new_transaction = byte_array_to_struct(byte_array,(unsigned_txn_string_len+1)/2);

    printf("version: ");
    print_byte_array(new_transaction->version,VERSION_LEN);
    printf("Number of inputs: %d\n", new_transaction->no_of_inputs);
    for(uint16_t i = 0 ; i < new_transaction->no_of_inputs ; i++){
        printf("(Input %d) Prev TXN Hash: ",i);
        print_byte_array(new_transaction->inputs[i].prev_txn_hash ,PREV_TXN_HASH_LEN);
        printf("(Input %d) Prev Output Index: ",i);
        print_byte_array(new_transaction->inputs[i].prev_output_index,PREV_OUTPUT_INDEX_LEN);
        printf("(Input %d) Script Len: %d\n",i,new_transaction->inputs[i].script_len,SCRIPT_LENGTH_LEN);
        printf("(Input %d) Script: ",i);
        print_byte_array(new_transaction->inputs[i].script,new_transaction->inputs[i].script_len);
        printf("(Input %d) Sequence: ",i);
        print_byte_array(new_transaction->inputs[i].squence,SEQ_LEN);
    }
    



    printf("Number of outputs: %d\n",new_transaction->no_of_outputs);

    for(uint16_t i = 0 ; i < new_transaction->no_of_outputs ; i++){
        printf("(Output %d) Value: ",i);
        print_byte_array(new_transaction->outputs[i].value,VALUE_LEN);
        printf("(Output %d) Script Len : %d\n",i,new_transaction->outputs[i].script_len);
        printf("(Output %d) Script: ",i);
        print_byte_array((uint8_t*)new_transaction->outputs[i].script_public_key,new_transaction->outputs[i].script_len);
    }

    printf("Locktime: ");
    print_byte_array(new_transaction->lock_time,LOCKTIME_LEN);
    printf("Sighash: ");
    print_byte_array(new_transaction->sig_hash_code,SIG_HASH_CODE_LEN);




}