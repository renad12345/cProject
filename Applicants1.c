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

struct Applicant arrayApplicant[50];
struct Applicant* list=arrayApplicant;

int main(){
   addApplicant();
   calculatePoints();
   
   char* majorList="CSC,InS,SWE,CEN";
   setApplicantState(majorList);
   
   writeAssinedApplicants(); 
   printList();
   
   //free(list);
   return 0;
}
void addApplicant(){
   FILE *file = fopen("Applicants.txt", "r");
   if (file == NULL) {
      perror("Error opening file");
      return;
   }
   
   
 
//list = calloc(count, sizeof(struct Applicant));
   
    
   char OneLine[100];
   count=0;
   int i;
    
   for(i=0;i<3;i++) //to skip the first Three lines
      fgets(OneLine, sizeof(OneLine),file);
    
    
   while (fgets(OneLine, sizeof(OneLine), file) != NULL) {
      if (sscanf(OneLine, "%d %19s %19s %d %4s %f %9s",
                   &list[count].id,
                   list[count].applicant,
                   list[count].education,
                   &list[count].Experience,
                   list[count].major,
                   &list[count].GPA,
                   list[count].State) ) {
            
            // Validate education
         if (strcmp(list[count].education, "BSc") != 0 &&
                strcmp(list[count].education, "MSc") != 0) {
            printf("Invalid education format for applicant ID %d: %s\n",
                       list[count].id, list[count].education);
                      
            continue;  // Skip invalid entries
         }
      
            // Initialize Points and move to the next entry
         list[count].Points = 0;
         count++;
      }
     
   }
   fclose(file);
}
    
void calculatePoints(){
   int experience=0;
   int i;
   for(i = 0; i<7; i++){
      experience = list[i].Experience;
      if(strcmp(list[i].education, "MSc") == 0)
         experience+= 10;
      list[i].Points = list[i].GPA + experience;}
}
    
    
void setApplicantState (char* MajorList){
   for(int i = 0; i<count; i++){
   
      if(strstr(MajorList, list[i].major) !=NULL )
         strcpy(list[i].State, "Candidate");
   
   }
   int highest = 0;
   int index =0;
   for(int i = 0; i<count; i++){
      if(strcmp(list[i].State, "Candidate") == 0)
         if(list[i].Points>highest){
            highest = list[i].Points;
            index = i;
         }
   }
   strcpy(list[index].State, "Assigned");
   
}
void writeAssinedApplicants(){
   FILE *fpo= fopen("Output_Applicants.txt","w");
   if (fpo == NULL) {
      printf("Error opening file.\n");
      return;}
   fprintf(fpo, "The input applicants List is:\n");
   fprintf(fpo, "id\tName\t\tEducation\tExperience\tMajor\t\tGPA\t\tState\n");       
   int i;
   for (i=0; i<count ; i++){
      fprintf(fpo, "%d\t%s\t\t%s\t\t%d\t\t%s\t\t%.1f\t\t%s\n",
                list[i].id, list[i].applicant, list[i].education,
                list[i].Experience, list[i].major,
                list[i].GPA, "OWL");
   }
                
   fprintf(fpo, "----------------------------------------------------------------------------------------\n");            
   fprintf(fpo, "\nThe Candidates list is:\n");
   fprintf(fpo, "id\tName\t\tEducation\tMajor\t\tPoints\t\tState\n");
   for (int i = 0; i <count ; i++) {
      if (strcmp(list[i].State, "Candidate") == 0 || strcmp(list[i].State, "Assigned") == 0) {   
         fprintf(fpo, "%d\t%s\t\t%s\t\t%s\t\t%.1f\t\t%s\n",
                list[i].id, list[i].applicant, list[i].education,
                 list[i].major,
                list[i].Points, "Candidate");}
   }
                 
   fprintf(fpo, "----------------------------------------------------------------------------------------\n");            
   fprintf(fpo, "\nAssigned Applicant is:\n");
   fprintf(fpo, "id\tName\t\tEducation\tMajor\t\tPoints\t\tState\n");
   for (int i = 0; i <count ; i++) {
      if (strcmp(list[i].State, "Assigned") == 0) {   
         fprintf(fpo, "%d\t%s\t\t%s\t\t%s\t\t%.1f\t\t%s\n",
                list[i].id, list[i].applicant, list[i].education,
                list[i].major,
                list[i].Points, list[i].State);}
   }   
   fclose(fpo); 
}   
void printList(){
   printf("\nThe input applicants list is:\n");
   printf("ID\t\tApplicant\tEducation\tExperience\t\tMajor\t\tGPA\t\tState\n");
   for (int i = 0; i < count; i++)
      printf("%d\t\t%s\t\t\t%s\t\t\t%d\t\t\t\t\t%s\t\t%.2f\t\t%s\n",list[i].id,list[i].applicant,list[i].education,list[i].Experience,list[i].major,list[i].GPA,"OWL");
   printf("----------------------------------------------\n");
   printf("\nThe Candidates list is:\n");
   printf("ID\t\tApplicant\tEducation\tMajor\t\tpoints\t\tState\n");
   for (int i = 0; i < count; i++) {
      if(strcmp(list[i].State,"Candidate")==0|| strcmp(list[i].State,"Assigned")==0)
         printf("%d\t\t%s\t\t\t%s\t\t\t%s\t\t%.2f\t\t\t%s\n",list[i].id,list[i].applicant,list[i].education,list[i].major,list[i].Points,"Candidate");
   }//for
   printf("----------------------------------------------\n");
   printf("The Assigned Applicant is :\n");
   for (int i= 0; i < count; i++) {
      if(strcmp(list[i].State,"Assigned")==0){
         printf("%d\t\t%s\t\t\t%s\t\t\t%s\t\t%.2f\t\t\t%s\n",list[i].id,list[i].applicant,list[i].education,list[i].major,list[i].Points,list[i].State);
         break;
      }
   }//for
}//printMethod