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
    int8_t salt[MAX_SALT_SIZE];
    uint8_t seed[SEED_SIZE];
    HDNode *node = (HDNode*)malloc(sizeof(HDNode));
    HDNode *address = (HDNode*)malloc(sizeof(HDNode));

    //populating mnemonics and salt
    strcpy(mnemonic,"expire tank desert squeeze rule panic resist ocean dismiss bind shrimp mail gospel chief interest nominee already layer dutch drama genre spider love transfer");
    strcpy(salt,"");

    //calling function to get seed 512bit
    mnemonic_to_seed(mnemonic,salt,seed,NULL);
    printf("bip39 seed: ");
    print_byte_array(seed,SEED_SIZE);
    printf("------------\n");

    hdnode_from_seed(seed,SEED_SIZE,SECP256K1_NAME,node);
    hdnode_fill_public_key(node);

    printf("Master:\n");
    print_hdnode(node);
    printf("------------\n");



    hdnode_private_ckd_prime(node,44);
    hdnode_fill_public_key(node);
    printf("Purpose:\n");
    print_hdnode(node);
    printf("------------\n");

    hdnode_private_ckd_prime(node,1);
    hdnode_fill_public_key(node);
    printf("Coin:\n");
    print_hdnode(node);
    printf("------------\n");

    hdnode_private_ckd_prime(node,0);
    hdnode_fill_public_key(node);
    printf("----------\nAccount\n");
    print_hdnode(node);
    printf("----------\n");

    //0 hence internal node
    hdnode_private_ckd(node,0);
    hdnode_fill_public_key(node);
    printf("----------\nChange Node: \n");
    print_hdnode(node);
    printf("----------\n");
    

    for(uint16_t i= 0 ; i < 20 ; i++){
        memcpy(address,node,sizeof(HDNode));
        hdnode_private_ckd(address,i);
        hdnode_fill_public_key(address);
        printf("----------\nAddress Node (%d): \n",i);
        print_hdnode(node);
        printf("----------\n");
    }

}