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
  int output; // sending to receiver
  int output2; // remaining with sender
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
struct block AddBlock(struct block lastBlock, struct transaction structTransaction);

int main(){
  printf("Initializing project...\n");
  char charDecision;
  int intSender;
  int intReceiver;
  int intAmount;
  int intTransactionCounter = 0;
  struct transaction structTransaction[100]; // Limited to 99 transactions
  printf("Clearing old blockchain files...\n");
  system("rm chain");
  printf("Aged blockchains cleared!\n");
  // Defining the Genesis Block
  struct block NullBlock;
  struct block LastBlock; // Return from adding a block
  struct block NewBlock; // PlaceHolder until we recycle transactions
  NullBlock.version = 1;
  NullBlock.previousblockhash[0] = 0;
  NullBlock.merkleroothash[0] = 0;
  printf("Generating initial block at UNIX time:\n");
  NullBlock.time = system("date '+%s'");
  NullBlock.nBits = 0;
  NullBlock.nonce = 0;
  NullBlock.magic_number = 0;
  NullBlock.blocksize = 0;
  NullBlock.transactionCounter = intTransactionCounter;
  // End Genesis Block
  
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
  user[0].satoshis = intInitialCoin; // make into genesis block
  
  structTransaction[0].input = intInitialCoin;
  structTransaction[0].output = 0;
  structTransaction[0].output2 = intInitialCoin;
  printf("Initial transaction completed at UNIX time:\n");
  structTransaction[0].time = system("date '+%s'");
  LastBlock = AddBlock(NullBlock, structTransaction[0]); // This is creating the Genesis block
	   
  do{
    intTransactionCounter++;
    printf("Transaction %d\n", intTransactionCounter);
    printf("Which user wants to send coins?\n");
    scanf("%d", &intSender);
    printf("Which user is receiving coins?\n");
    scanf("%d", &intReceiver);
    printf("How many coins are we sending (in Satoshis)?");
    scanf("%d", &intAmount);


    structTransaction[intTransactionCounter].input = 0;
    structTransaction[intTransactionCounter].input = user[intSender].satoshis;

    user[intSender].satoshis = user[intSender].satoshis - intAmount;
    user[intReceiver].satoshis = user[intReceiver].satoshis + intAmount;

    structTransaction[intTransactionCounter].output = intAmount;
    structTransaction[intTransactionCounter].output2 = user[intSender].satoshis;
    printf("Moving next transaction at UNIX time:\n");
    structTransaction[intTransactionCounter].time = system("date '+%s'");

    printf("\nSender:\n");
    display(user[intSender]);
    printf("\nReceiver:\n");
    display(user[intReceiver]);
    printf("\n");


    NewBlock = AddBlock(LastBlock, structTransaction[intTransactionCounter]);
    // Sign a file
    // system("openssl dgst -sign user1private.pem test.pdf > signature.bin")

    // Verify a file
    // system("openssl dgst -verify user1public.pem -signature signature.bin test.pdf")

    
    printf("Do you want to make another transaction? (y/n)\n");
    scanf(" %c",&charDecision);

    LastBlock = NewBlock;
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

struct block AddBlock(struct block lastBlock, struct transaction structTransaction){
  // Adds a block to the Genesis block
  struct block thisBlock = lastBlock;
  
  FILE *fileChain = fopen("chain","a");
  fprintf(fileChain, "\nNew Block ***************************\n");
  fprintf(fileChain, "Version %d\n", lastBlock.version);
  fprintf(fileChain, "Last Block Hash: %s\n", lastBlock.previousblockhash);
  fprintf(fileChain, "Merkle Root Hash: %s\n", lastBlock.merkleroothash);
  fprintf(fileChain, "Block Time: %d\n", lastBlock.time);
  fprintf(fileChain, "nBits: %d\n", lastBlock.nBits);
  fprintf(fileChain, "Nonce: %d\n",lastBlock.nonce);
  fprintf(fileChain, "Magic Number: %d\n", lastBlock.magic_number);
  fprintf(fileChain, "Blocksize: %d\n", lastBlock.blocksize);
  fprintf(fileChain, "Block Transaction Counter: %d\n", lastBlock.transactionCounter);
  fprintf(fileChain, "Transaction Input: %d\n",structTransaction.input);
  fprintf(fileChain, "Transaction Sending: %d\n", structTransaction.output);
  fprintf(fileChain, "Transaction Remaining With Sender: %d\n",structTransaction.output2);
  fprintf(fileChain, "Transaction Time: %d\n", structTransaction.time);
  fprintf(fileChain, "*************************************\n");
  
  return thisBlock;
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
