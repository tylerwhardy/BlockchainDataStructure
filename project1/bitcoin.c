// Bitcoin Project 1
// Author: Tyler W Hardy

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <openssl/obj_mac.h>
#include <openssl/ec.h>

struct users{
  int user_id;
  char private[100];
  char public[100];
  int satoshis;
};

struct block{
  uint32_t version;
  char previousblockhash[32];
  char markleroothash[32];
  uint32_t time;
  uint32_t nBits;
  uint32_t nonce; 
  unsigned char magic_number;
  uint32_t blocksize;
  int transactionCounter; 
};

struct users NewUser(int uid);
void CreateGenesis();
void display(struct users s);
void AddBlock(struct block lastBlock);


int main(){
  printf("Initializing project...\n");
  printf("Creating users...\n");
  int intInitialCoin = 0;
  struct users user[6]; 
  for ( int intUserTotal = 0; intUserTotal < 7; intUserTotal++){
    printf("Creating User: %d\n",intUserTotal);
    user[intUserTotal] = NewUser(intUserTotal);
    display(user[intUserTotal]);
  }
  printf("\nAll users created\n\n");
  printf("Enter initial Satoshi count: ");
  scanf("%d", &intInitialCoin);
  printf("Distributing %d coins to User 0\n", intInitialCoin);
  return 0;
}

struct users NewUser(int uid){
// Defines a new user
  struct users user;
  user.user_id = uid;
  strcpy(user.public, "abcd");
  strcpy(user.private,"efgh");
  user.satoshis = 0;
  return user;
}

void display(struct users s){
  // Displays information about a user
  printf("\nDisplaying information on user\n");
  printf("UserID:%d\n", s.user_id);
  printf("Public Key:%s\n", s.public);
  printf("Private Key:%s\n", s.private);
  printf("Balance:%d\n\n", s.satoshis);
}

// Function CreateTransaction
// Creates a new transaction

// Function CreateTree
// Creates a Merkle tree for a transaction

void CreateGenesis(){
  // Creates a Genesis block
  int PreviousTransaction = 0;
  //void AddBlock(PreviousTransaction)
}

void AddBlock(struct block lastBlock){
  // Adds a block to the Genesis block
}
