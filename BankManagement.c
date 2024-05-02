#include <stdio.h>
#include <string.h>

void create_account();
void diposit_money();
void withdraw_money();
void check_Balance();

const char *ACCOUNT_FILE = "account.dat";

typedef struct
{
  char name[50];
  int acc_no;
  float balance;
} Account;

int main()
{
  int choice;

  while (1)
  {
    printf("\n**** BANK MANAGEMENT SYSTEM ****");
    printf("\n1. Create Account\n2. Deposit Money\n3. Withdraw Money\n4. Check Balance\n5. Exit");
    printf("\nEnter your choice : ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
      create_account();
      break;
    case 2:
      diposit_money();
      break;
    case 3:
      withdraw_money();
      break;
    case 4:
      check_Balance();
      break;
    case 5:
      printf("Closing the Bank .. Thanks for visiting!>.\n");
      return 0;
    default:
      printf("Invalid Choice\n");
      break;
    }
  }

  return 0;
}

void create_account()
{
  Account acc;

  FILE *file = fopen(ACCOUNT_FILE, "ab+");
  if (file == NULL)
  {
    printf("\nUnable to open the file");
    return;
  }

  printf("\nEnter your Name : ");
  getchar();
  fgets(acc.name, sizeof(acc.name), stdin); // to take space also
  int index = strcspn(acc.name, "\n");      // to remove \n
  acc.name[index] = '\0';
  printf("\nEnter your Account Number");
  scanf("%d", &acc.acc_no);
  getchar();
  acc.balance = 0;
  fwrite(&acc, sizeof(acc), 1, file);
  fclose(file);
  printf("\nAccount created Successfully!..");
}

void diposit_money()
{
  FILE *file = fopen(ACCOUNT_FILE, "rb+");
  if (file == NULL)
  {
    printf("\nUnable to open the file!..\n");
    return;
  }

  int acc_no;
  float money;
  Account acc_r;
  printf("\nEnter your account number : ");
  scanf("%d", &acc_no);
  printf("\nEnter the amount to deposit :  ");
  scanf("%f", &money);

  while (fread(&acc_r, sizeof(acc_r), 1, file))
  {
    if (acc_r.acc_no == acc_no)
    {
      acc_r.balance += money;
      fseek(file, -sizeof(acc_r), SEEK_CUR);
      fwrite(&acc_r, sizeof(acc_r), 1, file);
      fclose(file);
      printf("Successfully deposited Rs. %.2f. New Balance is %.2f \n", money, acc_r.balance);
      return;
    }
  }

  fclose(file);
  printf("Account Number %d not found in the records!>>>>.. the money could not be deposited!..", acc_no);
}

void withdraw_money()
{
  FILE *file = fopen(ACCOUNT_FILE, "rb+");
  if (file == NULL)
  {
    printf("Unable to open the account file!..\n");
    return;
  }

  Account acc_r;
  int acc_no;
  float money;
  printf("Enter your account number : ");
  scanf("%d", &acc_no);
  printf("Enter the amount to be withdraw : ");
  scanf("%f", &money);

  while (fread(&acc_r, sizeof(acc_r), 1, file))
  {
    if (acc_r.acc_no == acc_no)
    {
      if (acc_r.balance >= money)
      {
        acc_r.balance -= money;
        fseek(file, -sizeof(acc_r), SEEK_CUR);
        fwrite(&acc_r, sizeof(acc_r), 1, file);
        printf("Successfully Withdrawn Rs %.2f.. remaining Balance is Rs %.2f\n", money, acc_r.balance);
      }
      else
      {
        printf("Insufficient Balance\n");
      }

      fclose(file);
      return;
    }
  }

  printf("Account Number %d not found in the records!>>>>.. the money could not be deposited!..", acc_no);
}

void check_Balance()
{
  FILE *file = fopen(ACCOUNT_FILE, "rb");

  if (file == NULL)
  {
    printf("Unable to open the file!..\n");
    return;
  }

  int acc_no;
  Account acc_read;
  printf("\nEnter your Account Number : ");
  scanf("%d", &acc_no);
  getchar();

  while (fread(&acc_read, sizeof(acc_read), 1, file))
  {
    if (acc_read.acc_no == acc_no)
    {
      printf("Your current balance is Rs.%.2f", acc_read.balance);
      fclose(file);
      return;
    }
  }

  fclose(file);
}