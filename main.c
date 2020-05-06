#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<inttypes.h>

#include"utils.h"
#include"standardsize.h"

#include"lib/crypto/bip32.h"
#include"lib/crypto/curves.h"


int main(){
    //declarations
    int8_t mnemonic[159];
    int8_t txn_metadata_string[111];
    int8_t unsigned_txn_string[493];
    int8_t salt[MAX_SALT_SIZE];

    uint32_t length;
    
    //populating mnemonics and salt
    strcpy(mnemonic,"expire tank desert squeeze rule panic resist ocean dismiss bind shrimp mail gospel chief interest nominee already layer dutch drama genre spider love transfer");
    strcpy(txn_metadata_string,"8000002c800000018000000003000000000000000100000001000000020000000000000001010000000100000001010000000100000001");
    strcpy(salt,"");
    
    //UNSINGNED TRANSACTION
    // strcpy(unsigned_txn_string,"02000000021245fe7c5455b43e73743d83ccb5587303586a4e9a5b8f56a3eb08593624bb02000000001976a914d46d05e6ac27683aa5d63a6efc44969798acf13688acfdffffff1245fe7c5455b43e73743d83ccb5587303586a4e9a5b8f56a3eb08593624bb02010000001976a914dacc24d8b195ce046a40caedd5e2e649beee4e3388acfdffffff01f4ff0000000000001976a9142d77ece155f6b80dcab97a373834543e4b70b3e988ac84431a0001000000");
    strcpy(unsigned_txn_string,"0200000003fcb66d27eb9f20243e63b5eb37d558cc9964d2e88d5d28e48b2878d00e232f06000000001976a91447e542e7ebf9e5e590aac8fd44725ea26cb0a5cb88acfdffffff2364bbbfa1a33e34e4cd090d8712e14e98e6de42d43faaf93248bf905b6a5db4010000001976a9140bbadb5b0e9befbc160518477f772fc49a2a91af88acfdffffff7fe63e1499e1403ac8f8f70d3e9337a4c83c505067acca2440fcf5ecbfbc94ea010000001976a91447e542e7ebf9e5e590aac8fd44725ea26cb0a5cb88acfdffffff0157620100000000001976a9142a7d71a1af7b6424c79277b70f2143623b122ef988ace44a1a0001000000");

    uint8_t* singed_transaction = unsigned_to_signed(unsigned_txn_string,493,txn_metadata_string,111,mnemonic,159,salt,0,&length);
    print_byte_array(singed_transaction,length);
}

/*
0200000003fcb66d27eb9f20243e63b5eb37d558cc9964d2e88d5d28e48b2878d00e232f06000000001976a91447e542e7ebf9e5e590aac8fd44725ea26cb0a5cb88acfdfffffffcb66d27eb9f20243e63b5eb37d558cc9964d2e88d5d28e48b2878d00e232f06010000001976a914f6a3527071e1e3d6cdceeae1ce14a7b506b5cf9088acfdffffff7fe63e1499e1403ac8f8f70d3e9337a4c83c505067acca2440fcf5ecbfbc94ea010000001976a91447e542e7ebf9e5e590aac8fd44725ea26cb0a5cb88acfdffffff0143630100000000001976a9142a7d71a1af7b6424c79277b70f2143623b122ef988ac924a1a0001000000
*/