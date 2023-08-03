
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{
    int stno;
    char name[20];
    struct subject{
     int scode;
     char sname[20];
     int mark;
     }sub[3];
    int total;
    float ave;
}student;


// Function to add new student details to the file 'mystudents.txt'
void addNewStu(){
    student *s;
    FILE *fp;
    int n,i,j;
    printf("\nEnter how many students you want to add: ");
    scanf("%d",&n);

    s = (student*)calloc(n, sizeof(student));
    fp = fopen("mystudents.txt","a");

    for(i=0;i<n;i++){
        s[i].total=0;
        s[i].ave=0;
        printf("\nEnter the Student Number : ");
        scanf("%d",&s[i].stno);
        fflush(stdin);
        printf("\nEnter the Student Name : ");
        scanf("%[^\n]s",s[i].name);
        for(j=0;j<3;j++){
            printf("Enter Marks of Subject %d :",j+1);
            scanf("%d",&s[i].sub[j].mark);
            s[i].total+=s[i].sub[j].mark;
        }
        s[i].ave=s[i].total/3.0;
        fwrite(&s[i],sizeof(student),1,fp);
    }
    fclose(fp);
  }

// Function to update existing student details in the file 'mystudents.txt'
void updateDet(){
      int j,stno,found=0;
      student s1;
      FILE *fp , *fp1;
      fp = fopen("mystudents.txt","r");
      fp1 = fopen("temp.txt", "w");
      printf("Enter the Student Number to Update : ");
      scanf("%d",&stno);
      //printf("No            NAME                      MATHS | SCIENCE |  ENGLISH|  TOTAL| AVERAGE");

      while(fread(&s1,sizeof(student),1,fp))
      {
         if(s1.stno == stno){
             s1.total = 0;
             s1.ave = 0;
             found=1;
             fflush(stdin);
             printf("\nEnter the New Name : ");
             scanf("%[^\n]s",s1.name);
             for(j=0;j<3;j++){
               printf("Enter New Marks of Subject %d :",j+1);
               scanf("%d",&s1.sub[j].mark);
               s1.total+=s1.sub[j].mark;
            }
        s1.ave=s1.total/3.0;
       }
       fwrite(&s1,sizeof(student),1,fp1);
     }
     fclose(fp);
     fclose(fp1);

     if(found){
        fp1 = fopen("temp.txt","r");
        fp = fopen("mystudents.txt","w");

        while(fread(&s1,sizeof(student),1,fp1)){
          fwrite(&s1,sizeof(student),1,fp);
        }

        fclose(fp);
        fclose(fp1);

     }
     else {
        printf("\n\n     **************************Record Not Found**************************      \n");
     }

}

// Function to display all student details from the file 'mystudents.txt'
void display(){
      int j;
      student s1;
      FILE *fp;
      fp = fopen("mystudents.txt","r");
      printf("No            NAME                      MATHS | SCIENCE |  ENGLISH|  TOTAL| AVERAGE");
      while(fread(&s1,sizeof(student),1,fp))
      {
         printf("\n%-7d%-30s",s1.stno,s1.name);
         for(j=0;j<3;j++){
            printf("%8d |",s1.sub[j].mark);

         }
         printf("%6d | %7.2f",s1.total,s1.ave);
      }

     fclose(fp);
}


// Function to delete a specific student record from the file 'mystudents.txt'
void deleteStu(){
     int j,stno,found=0;
      student s1;
      FILE *fp , *fp1;
      fp = fopen("mystudents.txt","r");
      fp1 = fopen("temp.txt", "w");
      printf("Enter the Student Number to Delete : ");
      scanf("%d",&stno);
      //printf("No            NAME                      MATHS | SCIENCE |  ENGLISH|  TOTAL| AVERAGE");

      while(fread(&s1,sizeof(student),1,fp))
      {
         if(s1.stno == stno){
            found=1;
         }
         else
           fwrite(&s1,sizeof(student),1,fp1);
     }
     fclose(fp);
     fclose(fp1);

     if(found){
        fp1 = fopen("temp.txt","r");
        fp = fopen("mystudents.txt","w");

        while(fread(&s1,sizeof(student),1,fp1)){
          fwrite(&s1,sizeof(student),1,fp);
        }

        fclose(fp);
        fclose(fp1);

     }
     else {
        printf("\n\n     **************************Record Not Found**************************      \n");
     }
}

// Function to count the total number of student records in the file 'mystudents.txt'
void noRecords(){
    student s1;
    FILE *fp;
    fp=fopen("mystudents.txt","r");
    fseek(fp,0,SEEK_END);
    int n = ftell(fp)/sizeof(student);
    printf("\n\nNO OF RECORDS = %d",n);
    fclose(fp);
}

// Function to search for a specific student by their student number in the file 'mystudents.txt'
void search(){
      int j,stno,found=0;
      student s1;
      FILE *fp;
      fp = fopen("mystudents.txt","r");
      printf("Enter the Student Number to Search : ");
      scanf("%d",&stno);
      printf("No            NAME                      MATHS | SCIENCE |  ENGLISH|  TOTAL| AVERAGE");

      while(fread(&s1,sizeof(student),1,fp))
      {
         if(s1.stno == stno){
             found=1;
             printf("\n%-7d%-30s",s1.stno,s1.name);
             for(j=0;j<3;j++){
                printf("%8d |",s1.sub[j].mark);

             }
             printf("%6d | %7.2f",s1.total,s1.ave);
          }
      }

     if(!found)
     {
        printf("\n\n     **************************Record Not Found**************************      \n");
     }
     fclose(fp);
}

// Function to calculate and print student ranks based on total marks
void printRank(){
    student *s,s1;
    int i,j,rank=1;
    FILE *fp;
    fp = fopen("mystudents.txt","r");
    fseek(fp,0,SEEK_END);
    int n = ftell(fp)/sizeof(student);
    s = (student*)calloc(n,sizeof(student));

    rewind(fp);
    for(i=0;i<n;i++)
        fread(&s[i],sizeof(student),1,fp);

    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            if(s[i].total < s[j].total){
                s1 = s[i];
                s[i] = s[j];
                s[j] = s1;
            }
        }
     }
    printf("No            NAME                      MATHS | SCIENCE |  ENGLISH|  TOTAL| AVERAGE | RANK |");
    for(i=0;i<n;i++){
        // Check if total marks are the same as the previous student
        // If yes, do not update the rank
        if (i > 0 && s[i].total < s[i - 1].total) {
            rank = i + 1;
        }
             printf("\n%-7d%-30s",s[i].stno,s[i].name);
             for(j=0;j<3;j++){
                printf("%8d |",s[i].sub[j].mark);
             }
             printf("%6d | %7.2f | %3d  |",s[i].total,s[i].ave,rank);

    }
    fclose(fp);
}

// Displaying the main menu options
int homepage(){
    int ch;
    do{
        printf("\n\n");
        printf("\n------------------------------------------------------------------------------------");
        printf("\n[1]  Add New Student                                  [2]  Update Student Details");
        printf("\n[3]  Display Student Details                          [4]  Delete Student");
        printf("\n[5]  No of Records                                    [6]  Search Details");
        printf("\n[7]  Print Students Rank                              [0]  Exit");
        printf("\n------------------------------------------------------------------------------------");

        printf("\nEnter your Choice : ");
        scanf("%d",&ch);

        switch(ch){
            case 1 :
                addNewStu();
                break;
            case 2 :
                updateDet();
                break;
            case 3 :
                display();
                break;
            case 4 :
                deleteStu();
                break;
            case 5 :
                noRecords();
                break;
            case 6 :
                search();
                break;
            case 7 :
                printRank();
                break;
            case 0 :
                exit(0);
                break;
            default:
                printf("\n************************  Invalid Input! Try Again  ***********************\n");
                homepage();// If an invalid choice is entered, display the main menu again
                break;
            }


    }while(ch!=0);

   return 0;
}

int main(){
         char un[20];
         char pw[20];
         char ch;
         int i=0;

        // Displaying the welcome message and login screen
        printf("\n-------------------------------------------------------------------------------------");
        printf("\n|                   WELCOME TO ABC SCHOOL MARKS MANAGEMENT SYSTEM                   |");
        printf("\n-------------------------------------------------------------------------------------");

        printf("\n                             ------------------------                                 ");
        printf("\n                             |        LOGIN         |                                 ");
        printf("\n                             ------------------------                                 ");

        printf("\nEnter your Username: ");
        scanf(" %s",un);
        printf("\nEnter your Password: ");

        // Masking the password input with '*' characters
        while ((ch = _getch())!= 13){
        if (ch == 8) {
            if (i > 0) {
                // If backspace is pressed and we have characters in the password
                // Remove the last character and go back one position
                printf("\b \b");
                i--;
            }
        }
           else {
             pw[i] = ch;
             i++;
             printf("*");
        }
    }

        pw[i]='\0';

        // Checking if the login credentials are correct
        if( !strcmp(un,"admin") && !strcmp(pw,"2001")){
                   homepage();// If login is successful, go to the main menu
        }
        else{
            printf("\n\n      **************Invalid Username or Password**************      \n\n");
        }
}
