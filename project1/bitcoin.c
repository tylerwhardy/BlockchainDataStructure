// Bitcoin Project 1
// Author: Tyler W Hardy

#include <stdio.h>
#include <stdlib.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <openssl/obj_mac.h>
#include <openssl/ec.h>

struct user{
  int user_id;
  char address[100];
  int satoshis;
};

struct user NewUser();

struct user display();

int main(){
  printf("Initializing project...\n");
  printf("Creating users...\n");
  int intUserTotal = 0;
  int intInitialCoin = 0;
  struct users[6]; 
  do{
    printf("Creating User: %d\n",intUserTotal);
    intUserTotal++;
    users[intUserTotal] = NewUser(intUserTotal);//NewUser
    display(users[intUserTotal]);
   } while(intUserTotal < 7);
  printf("Users created\n");
  printf("Enter initial coin count: ");
  scanf("%d", &intInitialCoin);
  printf("Distributing %d coins to User 0\n", intInitialCoin);
  return 0;
}

user NewUser(int uid){
// Function NewUser
// Defines a new user
  user_id = uid;
  address = "abcd";
  satoshis = 0;
  return user);
}

void display(struct user s){
  printf("\nDisplaying information on user\n");
  printf("UserID: %s\n", user.name);
  printf("Address:\n"); // Insert address here
  printf("Balance:\n"); // Insert balance here
}

// Function CreateTransaction
// Creates a new transaction

// Function CreateTree
// Creates a Merkle tree for a transaction

// Function CreateGenesis
// Creates a Genesis block

// Function AddBlock
// Adds a block to the Genesis block
