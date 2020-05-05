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
    int8_t mnemonic[160];
    int8_t txn_metadata_string[96];
    int8_t unsigned_txn_string[298];
    int8_t salt[MAX_SALT_SIZE];

    uint32_t length;

    //populating mnemonics and salt
    strcpy(mnemonic,"expire tank desert squeeze rule panic resist ocean dismiss bind shrimp mail gospel chief interest nominee already layer dutch drama genre spider love transfer");
    strcpy(txn_metadata_string,"8000002c80000001800000000100000000000000000200000000000000010000000100000000010000000100000000");
    strcpy(salt,"");
    
    //UNSINGNED TRANSACTION
    // strcpy(unsigned_txn_string,"02000000021245fe7c5455b43e73743d83ccb5587303586a4e9a5b8f56a3eb08593624bb02000000001976a914d46d05e6ac27683aa5d63a6efc44969798acf13688acfdffffff1245fe7c5455b43e73743d83ccb5587303586a4e9a5b8f56a3eb08593624bb02010000001976a914dacc24d8b195ce046a40caedd5e2e649beee4e3388acfdffffff01f4ff0000000000001976a9142d77ece155f6b80dcab97a373834543e4b70b3e988ac84431a0001000000");
    strcpy(unsigned_txn_string,"020000000155f34eb0096d6d2972abbe086d7f4b93c22ec322ef29219a6c1c90a495dcc85a000000001976a914d323988772f6f24d7108d50524f576b3b639dfb988acfdffffff022ea30000000000001976a9148e58712486df06aa62033064a147f505801178c388ac50c30000000000001976a91447e542e7ebf9e5e590aac8fd44725ea26cb0a5cb88ac0000000001000000");


    uint8_t* singed_transaction = unsigned_to_signed(unsigned_txn_string,297,txn_metadata_string,95,mnemonic,159,salt,0,&length);
    print_byte_array(singed_transaction,length);

}