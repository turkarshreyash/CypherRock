/*
This file contains all the neccessary structs
*/

#pragma once

#include<inttypes.h>

#include"standardsize.h"



/*
Structure for input
*/
struct unsigned_txn_inputs{
    uint8_t prev_txn_hash[PREV_TXN_HASH_LEN];
    uint8_t prev_output_index[PREV_OUTPUT_INDEX_LEN];
    uint8_t script_len;
    uint8_t *script;
    uint8_t squence[SEQ_LEN];
};

/*
Structure for output
*/
struct unsigned_txn_outputs{
    uint8_t value[VALUE_LEN];
    uint8_t script_len;
    uint8_t *script_public_key;
};

/*
Structure for unsigned transactions
*/
struct unsigned_txn{
    uint8_t version[VERSION_LEN];
    uint8_t no_of_inputs;
    
    //Inputs sub struct 
    struct unsigned_txn_inputs* inputs;
    
    uint8_t no_of_outputs;

    //Output sub struct
    struct unsigned_txn_outputs* outputs;

    uint8_t lock_time[LOCKTIME_LEN];
    uint8_t sig_hash_code[SIG_HASH_CODE_LEN];

};