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
    uint8_t *txn_byte_array;
    int8_t salt[MAX_SALT_SIZE];
    uint8_t seed[SEED_SIZE];
    HDNode *node = (HDNode*)malloc(sizeof(HDNode));
    HDNode *addr_node = (HDNode*)malloc(sizeof(HDNode));
    char *address = (char*)malloc(256);

    //populating mnemonics and salt
    strcpy(mnemonic,"expire tank desert squeeze rule panic resist ocean dismiss bind shrimp mail gospel chief interest nominee already layer dutch drama genre spider love transfer");
    strcpy(txn_metadata_string,"8000002c80000001800000000100000000000000000200000000000000010000000100000000010000000100000000");
    strcpy(salt,"");
    /*
    struct txn_metadata{
    
    uint8_t purpose_index[INDEX_SIZE];
    uint8_t coin_index[INDEX_SIZE];
    uint8_t account_index[INDEX_SIZE];

    uint8_t input_count;
    struct node *inputs;

    uint8_t output_count;
    struct node *outputs;

    uint8_t change_count;
    struct node *changes;

};
    */
    txn_byte_array = string_to_byte_array(txn_metadata_string,95);
    print_byte_array(txn_byte_array,96/2);
    struct txn_metadata* txn_meta = txn_to_byte_array(txn_byte_array,96/2);
    print_txn_metadata(*txn_meta);

    mnemonic_to_seed(mnemonic,salt,seed,NULL);
    //m
    hdnode_from_seed(seed,SEED_SIZE,SECP256K1_NAME,node);
    hdnode_fill_public_key(node);

    //m/44'
    hdnode_private_ckd(node,uint8_t_array_to_uint32_t(txn_meta->purpose_index));
    hdnode_fill_public_key(node);

    //m/44'/1'
    hdnode_private_ckd(node,uint8_t_array_to_uint32_t(txn_meta->coin_index));
    hdnode_fill_public_key(node);
    //m/44'/1'/0'
    hdnode_private_ckd(node,uint8_t_array_to_uint32_t(txn_meta->account_index));
    hdnode_fill_public_key(node);


    //m/44'/1'/0'/from_meta_data
    struct node last_output_node = txn_meta->outputs[txn_meta->output_count-1];
    hdnode_private_ckd(node,uint8_t_array_to_uint32_t(last_output_node.chain_index));
    hdnode_fill_public_key(node);

    hdnode_private_ckd(node,uint8_t_array_to_uint32_t(last_output_node.address_index));
    hdnode_fill_public_key(node);
    hdnode_get_address(node,0x6f,address,256);
    print_hdnode(node);
    printf("Address: %s\n",address);





}