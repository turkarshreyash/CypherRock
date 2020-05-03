CC := gcc

BASE_DIR := .

LIB_DIR := $(BASE_DIR)/lib
SRC_DIR := $(BASE_DIR)

CRYPTO_LIB := $(LIB_DIR)/crypto

CSRC := $(wildcard $(SRC_DIR)/*.c) 
CSRC +=	$(wildcard $(CRYPTO_LIB)/*.c) 
CSRC += $(wildcard $(CRYPTO_LIB)/aes/*.c)
CSRC += $(wildcard $(CRYPTO_LIB)/chacha20poly1305/*.c)
CSRC += $(wildcard $(CRYPTO_LIB)/ed25519-donna/*.c)
# CSRC += $(wildcard $(CRYPTO_LIB)/monero/*.c)


OBJ := $(CSRC:.c=.o)


CFLAGS := -L$(CRYPTO_LIB) -I$(CRYPTO_LIB)

main:$(CSRC)
	$(CC) -o $@ $^ $(CFLAGS)