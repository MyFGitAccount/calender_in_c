#include "stdio.h"
#include "time.h"
#include "string.h"
#include "stdlib.h"

#define SizeOfArray(arr) sizeof(arr)/sizeof(arr[0])
int month_day[]={31,28,31,30,31,30,31,31,30,31,30,31};
char month[20];
char month_name[20];
char week_day[20];
char week_days[20];
char day[10];
char* month_str[]={"01","02","03","04","05","06","07","08","09","10","11","12"};
char week_str[]={"1234567"};
char* week[]={"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
char* short_week[]={"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};

char* get_day(int date,int maxDate,char* day,int wantDate){
   int index=0;
   char* return_day;
   char** short_week_ptr=short_week;
   for(int i=0;i<7;i++){
      if(strcmp(day,*(week+i))==0){
         index=i;
         break;
      }
   }
   short_week_ptr+=index;
   if(date==wantDate) return day;
   for(int i=0;i<abs(wantDate-date);i++){
      //if(date==wantDate) return day;
      if(wantDate<date){
         if(index==0){ 
           index=6;
           short_week_ptr+=index;
         }
         index--;
         short_week_ptr--;
         return_day=*(short_week_ptr);
         //index--;
      }
      else if(wantDate>date){
         if(index==6)
         {
          short_week_ptr-=index;
          index=0;
         }
         index++;
         short_week_ptr++;
         return_day=*short_week_ptr;
         //index++;
      }
   }
   return return_day;
}

void print_cal(char* month,char* day,char* month_name){
   time_t now;
   struct tm *time_info;
   time(&now);
   time_info=localtime(&now);

   int year = time_info->tm_year + 1900;
   if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
   * (month_day+1) = 29;
   }

   int m=atoi(month);
   int* month_day_ptr=month_day;
   int weekDay=*(month_day_ptr+m-1-1);
   int date=atoi(day);
   char* weekday;
   printf("	%8s\n",month_name);
   for(int i=1;i<weekDay+1;i++){
      weekday=get_day(date,weekDay,week_days,i);
      if (i==date && i%7!=0) printf("|\x1b[31m%2d(%s)\x1b[0m| ",i, weekday);
      else if(i==date && i%7==0) printf("|\x1b[31m%2d(%s)\x1b[0m| ",i,weekday);
      else if(i%7!=0) printf("|%2d(%s)| ",i,weekday);
      else printf("\n|%2d(%s)| ",i,weekday);
   }
   printf("\n");
}


int main(void){
  /*printf("month_name:%s\n",month_name);//09
  printf("week_day:%s\n",week_day);//1
  printf("maonth_str[1]:%s\n",month_str[1]);//02
  printf("day:%d\n",atoi(day));//1*/
  //printf("\n\n------------------------\n");
  time_t now;
  struct tm *time_info;
  time(&now);
  time_info=localtime(&now);
  strftime(month,sizeof(month),"%m",time_info);
  strftime(week_day,sizeof(week_day),"%u",time_info);
  strftime(day,sizeof(day),"%d",time_info);
  strftime(month_name,sizeof(month_name),"%B",time_info);
  strftime(week_days,sizeof(week_days),"%A",time_info);
  //printf("%s\n",week_days);
  print_cal(month,day,month_name);
}
