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
#include "itoa.h"


struct users{
  int user_id;
  char private[100];
  char public[100];
  int satoshis;
};

struct transaction{
  // This is to represent a transaction. Some features are abstracted away. 
  int input; // sender balance
  int output; // receiver balance
  int output2; // sender balance
  uint32_t time; // timestamp 
};

struct block{
  // Header
  uint32_t version;
  char previousblockhash[32];
  char merkleroothash[32];
  uint32_t time;
  uint32_t nBits; // This is something for mining, we will leave it at 0
  uint32_t nonce; // This is something for mining, we will leave it at 0
  // /Header
  unsigned char magic_number;
  uint32_t blocksize;
  int transactionCounter;
  struct transaction transactionList;
};



struct users NewUser(int uid);
void CreateGenesis();
void display(struct users s);
void AddBlock(struct block lastBlock);

int main(){
  printf("Initializing project...\n");
  char charDecision;
  int intSender;
  int intReceiver;
  int intAmount;
  int intTransactionCounter;
  struct transaction structTransaction[100]; // Limited to 99 transactions
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
  user[0].satoshis = intInitialCoin;

  
  
  // CreateGenesis();
  do{
    intTransactionCounter++;
    printf("Which user wants to send coins?\n");
    scanf("%d", &intSender);
    printf("Which user is receiving coins?\n");
    scanf("%d", &intReceiver);
    printf("How many coins are we sending (in Satoshis)?");
    scanf("%d", &intAmount);

    structTransaction[intTransactionCounter].input = user[intSender].satoshis;

    user[intSender].satoshis = user[intSender].satoshis - intAmount;
    user[intReceiver].satoshis = user[intReceiver].satoshis + intAmount;

    structTransaction[intTransactionCounter].output = user[intReceiver].satoshis;
    structTransaction[intTransactionCounter].input = user[intSender].satoshis;
    structTransaction[intTransactionCounter].time = system("date '+%s'");

    printf("\nSender:\n");
    display(user[intSender]);
    printf("\nReceiver:\n");
    display(user[intReceiver]);
    printf("\n");

    
    printf("Do you want to make another transaction? (y/n)\n");
    scanf(" %c",&charDecision);


  } while (charDecision ==  'y' && intTransactionCounter < 100);
  
  return 0;
}

struct users NewUser(int uid){
// Defines a new user
  char suid[2];
  char src[20];
  char username[20];
  struct users user;
  char publicpath[20];
  char privatepath[20];
  char private[20] = "private.pem";
  char public[20] = "public.pem";
  
  user.user_id = uid;
  itoa(uid, suid,10);

  strcpy(username,"user");
  strncat(username,suid,10);

  strcpy(user.public, username);
  strcpy(user.private, username);
  strncat(user.public, public,10);
  strncat(user.private, private,11);
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
  CreateGenesis();
}

// Function CreateTransaction
// Creates a new transaction

// Function CreateTree
// Creates a Merkle tree for a transaction

void CreateGenesis(){
  // Creates a Genesis block
  int PreviousTransaction = 0;
  int time;
  time = system("date '+%s'");
  printf("%d", time);
  //void AddBlock(PreviousTransaction)
}

void AddBlock(struct block lastBlock){
  // Adds a block to the Genesis block
  FILE *fileChain = fopen("chain","w");
  fprintf(fileChain, "Block");
}


// For Reference Only ********
// These are CLI commands to generate the associated keys
// This application assumes a prefix of usern where n is the user number
// For example, user1public.pem

// Create Eliptic Curve parameter file:
// openssl ecparam -name secp256k1 -out secp256k1.pem

// Create Private key
// openssl ecparam -in secp256k1.pem -genkey -noout -out private.pem

// Create Public key from Private
// openssl ec -in private.pem -pubout -out public.pem

// Sign a file
// system("openssl dgst -sign user1private.pem test.pdf > signature.bin")

// Verify a file
// system("openssl dgst -verify user1public.pem -signature signature.bin test.pdf")

// ******************************
