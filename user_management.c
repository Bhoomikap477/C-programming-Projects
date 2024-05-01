#include<stdio.h>
#include<string.h>

#define MAX_USERS 10
#define credential_length 30

typedef struct{
  char username[30];
  char password[10];
}User;


User users[MAX_USERS];
int user_count = 0; 

void register_user();
int login_user(); // returns user index
void fix_fgets_input(char*);//used to convert \n with \0
void input_password(char*);// used in multiple functions

int main(){
  int option;
  int user_index ;

  while(1){
  printf("User Management system\n");
  printf(" 1 : Register \n 2 : Login \n 3 : Exit\n");
  printf(" Select an option : ");
  scanf("%d",&option);
  printf("\n");
  getchar();

  switch(option){
    case 1: register_user();
           break;

    case 2: 
     user_index = login_user();
    if (user_index >=0){
      printf(" Login Successful!.. Welcome %s !..\n ",users[user_index].username);
    }else{
      printf("Login Failed!Incorrect username or password..\n"); 
    }
    break;

    case 3: printf("\n Exiting the Program!..");
            return 0;
           break;

    default:
            printf("Invalid option !.Please try again\n");
            break;
  }
  }
}


void register_user(){
           if(user_count == MAX_USERS){
              printf("\n Maximum %d is allowed!..\n",MAX_USERS);
              return;
            }

            int new_index = user_count;
            printf("\n Register new user!..");
            printf("\n Enter user name : ");
            fgets(users[new_index].username,credential_length,stdin);
            fix_fgets_input(users[new_index].username);
            input_password(users[new_index].password);
            user_count++;
            printf("\n Registration Successful!..\n");
           
}

int login_user(){
  char user_name[credential_length];
  char password[credential_length];
  printf("Login User\n");
  printf("\n Enter user name : ");
  fgets(user_name,credential_length,stdin);
  fix_fgets_input(user_name);
  input_password(password);

  for(int i=0;i<user_count;i++){
    if(strcmp(user_name,users[i].username) == 0 && strcmp(password,users[i].password) == 0){
      return i;
    }
  }
  return -1;
}

void fix_fgets_input(char* string){
  int index=strcspn(string,"\n");
  string[index]='\0';
}

void input_password(char* password){
  printf("\n Enter the password : ");
  fgets(password,credential_length,stdin);
  fix_fgets_input(password);
}