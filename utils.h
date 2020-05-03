/*
This file contains general utilities
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"structures.h"
#include"./lib/crypto/bip32.h"

/*
@para para1: byte array, para2: len of array
@return void
*/
void print_byte_array(uint8_t*, uint32_t);

/*
@para para1: hdnode
return void
*/
void print_hdnode(HDNode*);


/*
string to byte array
@para para1: string, para2: len of string, para3: byte array
@return len of byte array
*/
uint8_t* string_to_byte_array(int8_t *, uint32_t);


/*
byte array to struct
@para para1: byte array, para2: len of byte array
@return struct
*/
struct unsigned_txn* byte_array_to_struct(uint8_t *, uint32_t);