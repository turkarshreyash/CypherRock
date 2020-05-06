/*
This file contains general utilities
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"structures.h"
#include "lib/crypto/bip39.h"
#include "lib/crypto/bip32.h"
#include "lib/crypto/curves.h"
#include "lib/crypto/secp256k1.h"
#include "lib/crypto/sha2.h"
#include "lib/crypto/ecdsa.h"
#include "lib/crypto/ripemd160.h"
#include "lib/crypto/base58.h"


/*
*/
uint32_t uint8_t_array_to_uint32_t(uint8_t *);


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
@para para1: tx meta struct*
@return void
*/
void print_txn_metadata(struct txn_metadata);

/*
*/
void print_unsigned_txn(struct unsigned_txn);

/*
*/
void print_signed_txn(struct signed_txn);

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
struct unsigned_txn* byte_array_to_unsigned_txn(uint8_t *, uint32_t);


/*
transaction meta data to byte array
@para para1: txn structure, reference to len variable
@return byte array
*/
struct txn_metadata* byte_array_to_txn_meta(uint8_t*, uint16_t);

/*
Unsigned to signed
@para para1: unsigned txn struct, txn_meta struct, signed txn struct
@return void
*/
int8_t* unsigned_to_signed(int8_t*, uint32_t, int8_t*, uint32_t, int8_t*, uint32_t, int8_t*, uint32_t,uint32_t*);


/*
serialise unsigned struct to byte array
@para para1: unsigned struct, para2: index -> input to skip, para3: (ref)len of byte array 
@return byte array
*/
uint8_t* serialise_unsigned_txn(struct unsigned_txn*, int32_t, uint16_t*);

/*
Serialise signed to byte array
*/
uint8_t* serialise_signed_txn(struct signed_txn*, uint32_t);



/*
Electr
*/