#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>

void fill_time(char*,int);

void clear_screen();

void fill_date(char*);
int main(){
  char time[50],date[50];

  int choice;

  printf("\n Choose he time format\n");
  printf("24 hour format \n");
  printf("12 hour format (default) \n");
  scanf("%d",&choice);
    while(1){
    fill_time(time,choice);
     fill_date(date);
     clear_screen();
  printf("Current time is :%s\n",time);
  printf("Current date is :%s",date);
  sleep(1);
    }
  return 0;
}


void fill_time(char* buffer , int format){
   time_t raw_time; // to calculate time from system
  struct tm *current_time;

  time(&raw_time);
  current_time = localtime(&raw_time);

  if(format == 1){
  strftime(buffer,50,"%H : %M : %S %p",current_time);
  }else{
    strftime(buffer,50,"%I : %M : %S %p",current_time);
  }


}


void fill_date(char* buffer ){
  time_t raw_time; // to calculate time from system
  struct tm *current_time;

  time(&raw_time);
  current_time = localtime(&raw_time);

   strftime(buffer,100,"%A %B %d %Y",current_time);

}

void clear_screen(){
  #ifdef _WIN32
   system("cls");
  #else
   system("clear");
  #endif
}