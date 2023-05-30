#define MAX_QUADS 1000
#include <stdlib.h>
#include "ctype.h"
typedef struct quadruplet {
  char op[20];
  char arg1[20];
  char arg2[20];
  char res[20];
} quadruplet; 

quadruplet quadruplets[MAX_QUADS];
 
extern int qc;
void quadr(char *op, char *arg1, char *arg2, char *res) {

  if (qc >= MAX_QUADS) {
    printf("Erreur : capacité de quadruplets dépassée.\n");
    exit(EXIT_FAILURE);
  }
  
  strcpy(quadruplets[qc].op, op);
  strcpy(quadruplets[qc].arg1, arg1);
  strcpy(quadruplets[qc].arg2, arg2);
  strcpy(quadruplets[qc].res, res);
  qc++;
}

void ajour_quad(int ligne, int champ, char *val) {
  switch (champ) {
    case 1:
      strcpy(quadruplets[ligne].op, val);
      break;
    case 2:
      strcpy(quadruplets[ligne].arg1, val);
      break;
    case 3:
      strcpy(quadruplets[ligne].arg2, val);
      break;
    case 4:
      strcpy(quadruplets[ligne].res, val);
      break;
    default:
      printf("Erreur : champ de quadruplet invalide.\n");
      exit(EXIT_FAILURE);
  }
}
void affich_quad(){
    for (int i = 0; i < sizeof(quadruplets) / sizeof(quadruplets[0]); i++){
        if(strcmp(quadruplets[i].op, "") != 0 || 
        strcmp(quadruplets[i].arg1, "") != 0 || 
        strcmp(quadruplets[i].arg2, "") != 0 || 
        strcmp(quadruplets[i].res, "") != 0) {
        printf("\n %d - ( %s , %s , %s , %s )",i,quadruplets[i].op,quadruplets[i].arg1,quadruplets[i].arg2,quadruplets[i].res); 
        }
    }
}
 
 void  Simplify(quadruplet* q1,int indice){
  char res[20];
  char resb[20];
  char savet[20];
  strcpy(savet,q1->res);
   int first=indice;
  //printf("%d",indice);
        quadruplet save[MAX_QUADS];
          // copier les valeurs de quadruplets dans save
          for (int i = 0; i < qc; i++){
              save[i] = quadruplets[i];
          }
      
          
          sprintf(resb,"%s%d",q1->res,0);
        
  if(isalpha(q1->arg1[0])){
 
      int max=atoi(q1->arg2);
      strcpy(quadruplets[indice].op, "+");
      strcpy(quadruplets[indice].arg1,q1->arg1);
      strcpy(quadruplets[indice].arg2, q1->arg1);
    //  strcpy(quadruplets[indice].res, resb);
    /*
    for(int i=1;i<max-1;i++){
      sprintf(res, "%s%d%d", "T",first, i);
      indice++;
      strcpy(quadruplets[indice].op, "+");
      strcpy(quadruplets[indice].arg1, resb);
      strcpy(quadruplets[indice].arg2, q1->arg1);
      strcpy(quadruplets[indice].res, res);
    }



    // modifier les valeurs de quadruplets à partir de l'indice donné
        for(int i=first+1;i<qc;i++){
            //printf("%d%d",i,qc+max-2);
            strcpy(quadruplets[i+max-2].op, save[i].op);
            strcpy(quadruplets[i+max-2].arg1,save[i].arg1);
            strcpy(quadruplets[i+max-2].arg2, save[i].arg2);
            strcpy(quadruplets[i+max-2].res, save[i].res);
        }
      */

  }else if(isalpha(q1->arg2[0])){

            int max=atoi(q1->arg1);
            strcpy(quadruplets[indice].op, "+");
            strcpy(quadruplets[indice].arg1,q1->arg2);
            strcpy(quadruplets[indice].arg2, q1->arg2);
           //strcpy(quadruplets[indice].res, resb);
    
  }
}
int checkIfChange(quadruplet* quads,int num_quads,int indice_actuel){
  int changed = 0;
  quadruplet* q1 = &quads[indice_actuel];
  int i ;
    for (i= indice_actuel+1; i < num_quads; i++) {
       quadruplet* q2 = &quads[i];
      if (isalpha(q1->arg1[0])){
        if(strcmp(q1->arg1,q2->res) && strcmp(q2->op,"=")){
          return 1;
        }
      }else if (isalpha(q1->arg2[0])){
        if(strcmp(q1->arg2,q2->res) && strcmp(q2->op,"=")){
          return 1;
        }
      }
  }

     return 0;

 
}
void calculeinutile(quadruplet* quads, int indice1, int indice2,int num_quads) {
  quadruplet* q1 = &quads[indice1];
  quadruplet* q2 = &quads[indice2];      

  int saveind2 = indice2;
  quadruplet* qb = &quads[0];
  
  for (int i = 0; i < indice1; i++) {
     
    if (strcmp(qb[i].res, q1->arg1) == 0 && strcmp(qb[i].op, "+") == 0) {
      
       
       
        if (strcmp(qb[i].arg2, q2->arg2) == 0 ) {
           //printf("%d-%d", indice1, indice2);
          for (int e = indice2+1; e < num_quads; e++) {
            //printf("%d-%d", indice1, saveind2);
          // printf("%s%s\n", qb[e].arg1,q2->res);
            if (strcmp(qb[e].op, "=") == 0 && strcmp(qb[e].arg1, q2->res) == 0) {
                
              strcpy(qb[e].arg1, qb[i].arg1);
            }
          }
        }  
      }
    }
  }
int checkexist(quadruplet* quads, int indice1, int indice2,int num_quads){
    quadruplet* q1 = &quads[indice1];
  quadruplet* q2 = &quads[indice2];      

  int saveind2 = indice2;
  quadruplet* qb = &quads[0];
 
  for (int i = 0; i < indice1; i++) {
     
    if (strcmp(qb[i].res, q1->arg1) == 0 && strcmp(qb[i].op, "+") == 0) {
      
      
       
        if (strcmp(qb[i].arg2, q2->arg2) == 0 ) {
           //printf("%d-%d", indice1, indice2);
          for (int e = indice2+1; e < num_quads; e++) {
            //printf("%d-%d", indice1, saveind2);
           //printf("%s%s\n", qb[e].arg1,q2->res);
            if (strcmp(qb[e].op, "=") == 0 && strcmp(qb[e].arg1, q2->res) == 0) {
                
              return 0;
            }
          }
        } 
      }
    }
    return 1;
}
void  maj_oldWithNew(quadruplet* quads,int old,char* new){
    
  quadruplet* q2 = &quads[old]; 
  for(int f=old+1;f<qc;f++){
      quadruplet* q1 = &quads[f];
      if(strcmp(q1->arg1,q2->res)==0){
          strcpy(q1->arg1,new);
      }else if(strcmp(q1->arg2,q2->res)==0){
          strcpy(q1->arg2,new);
      }else  if(strcmp(q1->res,q2->res)==0){
          strcpy(q1->res,new);
      }
  }

}
  
int checkIfResChange(quadruplet* quads,int num_quads,int indice_actuel){
  int changed = 0;
  quadruplet* q1 = &quads[indice_actuel];
  int i ;
   //printf("\n%d\n",indice_actuel);
    for (i= indice_actuel+1; i < num_quads; i++) {
       quadruplet* q2 = &quads[i];
      
      if (isalpha(q1->arg1[0])){
        if(strcmp(q1->res,q2->res)==0){
           //printf("out");
          return 1;
        }
      } 
  }
  
   
     return 0;
 
 
}
int Eliminationredanant(quadruplet* quads,int num_quads,int indice_actuel){
   quadruplet* q1 = &quads[indice_actuel];
    for(int i= 0; i < indice_actuel; i++){
       quadruplet* q2 = &quads[i];
       if(strcmp(q1->res,q2->res)!=0){
          if(strcmp(q1->arg1, q2->arg1) == 0 && strcmp(q1->arg2, q2->arg2) == 0 && strcmp(q1->op, q2->op) == 0 && strcmp(q1->op, "=") != 0){
                quadruplet* qres = &quads[i + 1];
                quadruplet* qchange = &quads[indice_actuel + 1];
                //printf("%s",qchange->arg1);
                strcpy(qchange->arg1, qres->res);

                return 1;
            }
        }
       }
 
    return 0;

}/*
int propagation(quadruplet* quads,int num_quads,int indice_actuel){
   quadruplet* q1 = &quads[indice_actuel];
    for(int i= 0; i < indice_actuel; i++){
       quadruplet* q2 = &quads[i];
       if(strcmp(q1->res,q2->res)!=0){
          if((strcmp(q1->arg1,q2->res)== 0 ||(strcmp(q1->arg2,q2->res)== 0 ))&&(strncmp(q2->arg1, "T", 1) == 0) && strcmp(q2->op, "=") == 0 ){
                quadruplet* qres = &quads[i + 1];
                quadruplet* qchange = &quads[indice_actuel + 1];
                //printf("%s",qchange->arg1);
                strcpy(q1->arg1, q2->arg1);

                return 1;
            }
        }
       }
 
    return 0;
}
//propagation expression
    else if(propagation(quads,num_quads,i)==1){
        //printf("test");
        memmove(q1, q1+1, (num_quads-i)*sizeof(quadruplet));
        num_quads--;
        i--;

      optimized = 1;

    }
*/
int optimize_quads(quadruplet* quads,int num_quads) {
 
    
    int optimized = 1;
    while (optimized) {
        optimized = 0; 
        
        for (int i = 0; i < num_quads; i++) {
            
            quadruplet* q1 = &quads[i];
            for (int j = i+1; j < num_quads; j++) {
               
                quadruplet* q2 = &quads[j];
            // Simplification algébrique             
                  if (strcmp(q1->op, "*") == 0 && ((atoi(q1->arg1)==2 && isalpha(q1->arg2[0])) || (atoi(q1->arg2)==2 && isalpha(q1->arg1[0])) ) ) {
                     // printf("Simplification algebrique\n");

                      Simplify(q1,i);
                      optimized = 1;
                    }else if(strcmp(q1->res, q2->arg1)==0 && strcmp(q2->op,"-")==0 && checkexist(quads,i,j,num_quads)==0){
                    //printf("calulcer");
                     calculeinutile(quads,i,j,num_quads);
                       
                      for (int f = 0; f < i; f++) {
                        quadruplet* qb = &quads[f];
                        if (strcmp(qb->res, q1->arg1) == 0 && strcmp(qb->op, "+") == 0) {
                            memmove(q2, q2+1, (num_quads-f)*sizeof(quadruplet));
                            num_quads--;
                            j--;
                          
                            if(checkIfResChange(quads,num_quads,i+1)==0){
                                
                                memmove(qb, qb+1, (num_quads-f)*sizeof(quadruplet));
                                num_quads--;
                                j--;
                               quadruplet* q11 = &quads[i-1];
                               memmove(q11, q11+1, (num_quads-f)*sizeof(quadruplet));
                                num_quads--;
                                j--;
                   
                            }
                          
                            
                          }
                        }
                     optimized = 1;
                  }       
  
            // Propagation de copie
                  else if ((strcmp(q1->res, q2->arg1) == 0 || strcmp(q1->res, q2->arg2) == 0)  && strcmp(q1->op, "=") == 0 && strncmp(q1->arg1, "T", 1) != 0 && q1->arg1[strlen(q1->arg1) - 1] != ']'){
                    //printf("ddd");
                    if (strcmp(q1->res, q2->arg1) == 0) {
                      strcpy(q2->arg1,q1->arg1);
                      optimized = 1;
                          memmove(q1, q1 + 1, (num_quads - i) * sizeof(quadruplet));
                          num_quads--;
                          i--;
                    } else if (strcmp(q1->res, q2->arg2) == 0) {
                      strcpy( q2->arg2,q1->arg1);
                      optimized = 1;
                          memmove(q1, q1 + 1, (num_quads - i) * sizeof(quadruplet));
                          num_quads--;
                          i--;
                    }

                    } else if ((q2->arg1[strlen(q2->arg1) - 1] == ']') && (strstr(q2->arg1, q1->res) != NULL) && (strcmp(q2->op,"=")==0) &&(strncmp(q1->arg1, "T", 1) != 0)&& (strncmp(q1->arg1, "T", 1) != 0)) {
                        int prefixLength = strstr(q2->arg1, q1->res) - q2->arg1;
                        int suffixLength = strlen(strstr(q2->arg1, q1->res) + strlen(q2->arg1));
            
                        char modifiedStr[100];
                   snprintf(modifiedStr, sizeof(modifiedStr), "%.*s%s%s", prefixLength, q2->arg1, q1->arg1, strstr(q2->arg1, q1->res) + strlen(q1->res) );

                 
                        //printf("Modified string: %s\n", modifiedStr);
                        strcpy(q2->arg1, modifiedStr);
                          memmove(q1, q1 + 1, (num_quads - i) *sizeof(quadruplet));
                          num_quads--;
                          i--;
                        optimized = 1;
                        
                    }
                    else if ((q2->res[strlen(q2->res) - 1] == ']') && (strstr(q2->res, q1->res) != NULL) && (strcmp(q2->op,"=")==0) && (strncmp(q1->arg1, "T", 1) != 0)){
                        int prefixLength = strstr(q2->res, q1->res) - q2->res;
                        int suffixLength = strlen(strstr(q2->res, q1->res) + strlen(q2->arg1));
                //printf("ddd");
                        char modifiedStr[100];
                   snprintf(modifiedStr, sizeof(modifiedStr), "%.*s%s%s", prefixLength, q2->res, q1->arg1, strstr(q2->res, q1->res) + strlen(q1->res));

                        //printf("Modified string: %s\n", modifiedStr);
                        strcpy(q2->res, modifiedStr);
                        
                          memmove(q1, q1 + 1, (num_quads - i) *sizeof(quadruplet));
                          num_quads--;
                          i--;
                        optimized = 1;
                    }

                  

            //Elimination redanant
                else if((strcmp(q1->op,"=")!=0)) {
                  if(Eliminationredanant(quads,num_quads,i)==1){
                    memmove(q1, q1+1, (num_quads-i)*sizeof(quadruplet));
                    num_quads--;
                    i--;
                    optimized=1;
                  }
                 
                } 
 
            }
             
        }
           
         
           
    }
    
    return num_quads;
}

void generateAssemblyCode(quadruplet* quads, int numQuadruplets, const char* fileName) {
      FILE* file = fopen(fileName, "w");
      if (file == NULL) {
          printf("Erreur lors de l'ouverture du fichier.\n");
          return;
      }
 // En-tête du programme assembleur
  fprintf(file, "ORG 100h\n\n");
      for (int i = 0; i < numQuadruplets; i++) {
            quadruplet* quad = &quads[i];

            // Génération du code machine pour chaque quadruplet
            fprintf(file, "; Quadruplet %d\n", i);
            fprintf(file, "MOV AX, %s\n", quadruplets[i].arg1);
            if(strcmp(quadruplets[i].arg2,"vide")!=0){
                fprintf(file, "MOV BX, %s\n", quadruplets[i].arg2);
            }
          if (strcmp(quadruplets[i].op, "+") == 0) {
            fprintf(file, "ADD AX, BX\n");
          } else if (strcmp(quadruplets[i].op, "-") == 0) {
            fprintf(file, "SUB AX, BX\n");
          } else if (strcmp(quadruplets[i].op, "*") == 0) {
            fprintf(file, "MUL BX\n");
          } else if (strcmp(quadruplets[i].op, "/") == 0) {
            fprintf(file, "DIV BX\n");}
          else if (strcmp(quad->op, "BE") == 0) {
              fprintf(file, "CMP %s, %s\n", quad->res, quad->arg1);
              fprintf(file, "JE %s\n", quad->arg1);
          } else if (strcmp(quad->op, "BR") == 0) {
              fprintf(file, "JMP %s\n", quad->arg1);
          }else if (strcmp(quad->op, "BLE") == 0) {
             fprintf(file, "CMP %s, %s\n",  quad->res, quad->arg1);
              fprintf(file, "JLE %s\n", quad->arg1);
          }else if (strcmp(quad->op, "BL") == 0) {
            fprintf(file, "CMP %s, %s\n",  quad->res, quad->arg1);
              fprintf(file, "JL %s\n", quad->arg1);
          }else if (strcmp(quad->op, "BGE") == 0) {
            fprintf(file, "CMP %s, %s\n",  quad->res, quad->arg1);
              fprintf(file, "JGE %s\n", quad->arg1);
          }else if (strcmp(quad->op, "BG") == 0) {
            fprintf(file, "CMP %s, %s\n",  quad->res, quad->arg1);
              fprintf(file, "JG %s\n", quad->arg1);
          }

      fprintf(file, "MOV %s, AX\n", quadruplets[i].res);
    fprintf(file, "\n");
  }

  // Fin du programme assembleur
  fprintf(file, "MOV AH, 4Ch\n");
  fprintf(file, "INT 21h\n");

      fclose(file);
  }
