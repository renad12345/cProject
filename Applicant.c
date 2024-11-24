#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addApplicant();
void calculatePoints();
void setApplicantState (char* MajorList );
void printList();
void writeAssinedApplicants();

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
   calculatePoints();
   
   char* majorList="CSC,InS,SWE,CEN";
   setApplicantState(majorList);
   
   writeAssinedApplicants(); 
   printList();
   
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


    


void calculatePoints(){
   int experience=0;
   int i;
   for(i = 0; i<7; i++){
      experience = arrayApplicant[i].Experience;
      if(strcmp(arrayApplicant[i].education, "MSc") == 0)
         experience+= 10;
      arrayApplicant[i].Points = arrayApplicant[i].GPA + experience;}
}
    
    

void setApplicantState (char* MajorList){

   for(int i = 0; i<count; i++){
   
      if(strstr(MajorList, arrayApplicant[i].major) !=NULL )
         strcpy(arrayApplicant[i].State, "Candidate");
   
   }

   int highest = 0;
   int index =0;
   for(int i = 0; i<7; i++){
      if(strcmp(arrayApplicant[i].State, "Candidate") == 0)
         if(arrayApplicant[i].Points>highest){
            highest = arrayApplicant[i].Points;
            index = i;
         }
   }
   strcpy(arrayApplicant[index].State, "Assigned");

   
}

void writeAssinedApplicants(){
   FILE *fpo= fopen("Output_Applicants.txt","w");
   if (fpo == NULL) {
      printf("Error opening file.\n");
      return;}
   fprintf(fpo, "The input applicants List is:\n");
   fprintf(fpo, "id\t\tName\t\tEducation\t\tExperience\t\tMajor\t\tGPA\t\tState\n");       
   int i;
   for (i=0; i<count ; i++){
      fprintf(fpo, "%d\t\t%s\t\t%s\t\t\t%d\t\t\t%s\t\t%.1f\t\t%s\n",
                arrayApplicant[i].id, arrayApplicant[i].applicant, arrayApplicant[i].education,
                arrayApplicant[i].Experience, arrayApplicant[i].major,
                arrayApplicant[i].GPA, "OWL");
   }
                
   fprintf(fpo, "----------------------------------------------------------------------------------------\n");            
   fprintf(fpo, "\nThe Candidates list is:\n");
   fprintf(fpo, "id\t\tName\t\tEducation\t\tExperience\t\tMajor\t\tPoints\t\tState\n");
   for (int i = 0; i <count ; i++) {
      if (strcmp(arrayApplicant[i].State, "Candidate") == 0 || strcmp(arrayApplicant[i].State, "Assigned") == 0) {   
         fprintf(fpo, "%d\t\t%s\t\t%s\t\t\t%d\t\t\t%s\t\t%.1f\t\t%s\n",
                arrayApplicant[i].id, arrayApplicant[i].applicant, arrayApplicant[i].education,
                arrayApplicant[i].Experience, arrayApplicant[i].major,
                arrayApplicant[i].Points, "Candidate");}
   }
                 
   fprintf(fpo, "----------------------------------------------------------------------------------------\n");            
   fprintf(fpo, "\nAssigned Applicant is:\n");
   fprintf(fpo, "id\t\tName\t\tEducation\t\tExperience\t\tMajor\t\tPoints\t\tState\n");
   for (int i = 0; i <count ; i++) {
      if (strcmp(arrayApplicant[i].State, "Assigned") == 0) {   
         fprintf(fpo, "%d\t\t%s\t\t%s\t\t\t%d\t\t\t%s\t\t%.1f\t\t%s\n",
                arrayApplicant[i].id, arrayApplicant[i].applicant, arrayApplicant[i].education,
                arrayApplicant[i].Experience, arrayApplicant[i].major,
                arrayApplicant[i].Points, arrayApplicant[i].State);}
   }   
   fclose(fpo); 
}   



void printList(){

   printf("\nThe input applicants list is:\n");
   printf("ID\t\tApplicant\tEducation\tExperience\t\tMajor\t\tGPA\t\tState\n");
   for (int i = 0; i < count; i++)
      printf("%d\t\t%s\t\t\t%s\t\t\t%d\t\t\t\t\t%s\t\t%.2f\t\t%s\n",arrayApplicant[i].id,arrayApplicant[i].applicant,arrayApplicant[i].education,arrayApplicant[i].Experience,arrayApplicant[i].major,arrayApplicant[i].GPA,"OWL");
   printf("----------------------------------------------\n");


   printf("\nThe Candidates list is:\n");
   printf("ID\t\tApplicant\tEducation\tMajor\t\tpoints\t\tState\n");
   for (int i = 0; i < count; i++) {
      if(strcmp(arrayApplicant[i].State,"Candidate")==0|| strcmp(arrayApplicant[i].State,"Assigned")==0)
         printf("%d\t\t%s\t\t\t%s\t\t\t%s\t\t%.2f\t\t\t%s\n",arrayApplicant[i].id,arrayApplicant[i].applicant,arrayApplicant[i].education,arrayApplicant[i].major,arrayApplicant[i].Points,"Candidate");
   }//for

   printf("----------------------------------------------\n");
   printf("The Assigned Applicant is :\n");
   for (int i= 0; i < count; i++) {
      if(strcmp(arrayApplicant[i].State,"Assigned")==0){
         printf("%d\t\t%s\t\t\t%s\t\t\t%s\t\t%.2f\t\t\t%s\n",arrayApplicant[i].id,arrayApplicant[i].applicant,arrayApplicant[i].education,arrayApplicant[i].major,arrayApplicant[i].Points,arrayApplicant[i].State);
         break;
      }
   }//for



}//printMethod
