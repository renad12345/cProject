#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addApplicant();
int count;

struct Applicant{
   int id;
   char applicant[20];
   char education[20];//in the main check if it “BSc” OR “MSc” only 
   char major[5];
   int Experience;
   float GPA;
   float Points;
   char State[10];

};

struct Applicant arrayApplicant[7];

int main(){


   addApplicant();
   int i;
   for(i=0; i<7;i++)//testing
      printf("ID: %d  Name: %s     Education: %s      Experience: %d      Major: %s     GPA: %f      Points: %f     State: %s \n", 
         arrayApplicant[i].id, 
         arrayApplicant[i].applicant, 
         arrayApplicant[i].education, 
         arrayApplicant[i].Experience, 
         arrayApplicant[i].major, 
         arrayApplicant[i].GPA,
         arrayApplicant[i].Points,
         arrayApplicant[i].State);

   return 0;
}



void addApplicant(){

   FILE *file = fopen("Applicants.txt", "r");
   if (file == NULL) {
      perror("Error opening file");
      return;
   }
    
   char OneLine[100];
   count=0;
   int i;
    
   for(i=0;i<3;i++) //to skip the first two lines
      fgets(OneLine, sizeof(OneLine),file);
    
    
   while (fgets(OneLine, sizeof(OneLine), file) != NULL) {
      if (sscanf(OneLine, "%d %19s %19s %d %4s %f %9s",
                   &arrayApplicant[count].id,
                   arrayApplicant[count].applicant,
                   arrayApplicant[count].education,
                   &arrayApplicant[count].Experience,
                   arrayApplicant[count].major,
                   &arrayApplicant[count].GPA,
                   arrayApplicant[count].State) == 7) {
            
            // Validate education
         if (strcmp(arrayApplicant[count].education, "BSc") != 0 &&
                strcmp(arrayApplicant[count].education, "MSc") != 0) {
            printf("Invalid education format for applicant ID %d: %s\n",
                       arrayApplicant[count].id, arrayApplicant[count].education);
            continue;  // Skip invalid entries
         }
      
            // Initialize Points and move to the next entry
         arrayApplicant[count].Points = 0;
         count++;
      }
   }
   fclose(file);
}
    
    


