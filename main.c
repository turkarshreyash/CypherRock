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

    for(uint16_t i = 0 ; i < 20 ; i++){
        
        hdnode_private_ckd_prime(node,i);
        hdnode_fill_public_key(node);
        printf("----------\nAccount %d\n",i);
        print_hdnode(node);
        printf("----------\n");

    }

}