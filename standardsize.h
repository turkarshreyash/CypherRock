/*
This file contains all the standard feild sizes
*/

#pragma once


//length in bytes

#define VERSION_LEN 4
#define NUMBER_OF_INPUTS_LEN 1
#define PREV_TXN_HASH_LEN 32
#define PREV_OUTPUT_INDEX_LEN 4
#define SCRIPT_LENGTH_LEN 1
#define SEQ_LEN 4
#define NUMBER_OF_OUTPUTS_LEN 1
#define VALUE_LEN 8
#define LOCKTIME_LEN 4
#define SIG_HASH_CODE_LEN 4
#define SEED_SIZE 64 //Bytes
#define MAX_SALT_SIZE 256
#define PRIVATE_KEY_LEN 32
#define PUBLIC_KEY_LEN 32
#define CHAIN_CODE_LEN 32
#define INDEX_SIZE 4
#define DEFAULT_UNSIGNED_TXN_SCRIPT_LEN 0x19

#define SIZE_OF_TXN_INPUTS_STRUCT (PREV_TXN_HASH_LEN+PREV_OUTPUT_INDEX_LEN+1+SEQ_LEN)
#define SIZE_OF_TXN_OUTPUTS_STRUCT (VALUE_LEN+1+DEFAULT_UNSIGNED_TXN_SCRIPT_LEN)

#define SIZE_OF_UNSIGNED_TXN_STRUCT(OUTS) (VERSION_LEN+1+(SIZE_OF_TXN_INPUTS_STRUCT+DEFAULT_UNSIGNED_TXN_SCRIPT_LEN)+1+((SIZE_OF_TXN_OUTPUTS_STRUCT)*(OUTS))+LOCKTIME_LEN)

#define SIZE_OF_MULTI_INPUT_UNSIGNED_TXN_STRUCT(INS,OUTS) (SIZE_OF_UNSIGNED_TXN_STRUCT(OUTS)+SIG_HASH_CODE_LEN+(SIZE_OF_TXN_INPUTS_STRUCT+1)*(INS-1))