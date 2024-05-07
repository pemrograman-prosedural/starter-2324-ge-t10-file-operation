t11_02.c

// 12S23038_Alya Triswani
// 12S23048_Grace Caldera Situmorang

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./libs/dorm.h"
#include "./libs/student.h"
#include "./libs/repository.h"

int main(int _argc, char **_argv)
{
    char input[100];
    char kalimat[100];
    char command[50];

    char data_id[10];
    char data_name[25];
    char data_year[5];
    char data_gender[8];
    int ang_gender = 0;

    struct student_t *mhs = malloc(20 * sizeof(struct student_t));
    struct dorm_t *dorms = malloc(20 * sizeof(struct dorm_t));


    unsigned short int stop = 0;

    unsigned short int size_mhs = 1, prt_std = 0;
    unsigned short int size_dorm = 1, prt_dorm = 0;
    unsigned short int poin_drm, poin_std;
    

    FILE *finput_std = fopen("./storage/student-repository.txt", "r");
    FILE *finput_drm = fopen("./storage/dorm-repository.txt", "r");


    // Parse FILE STD
    parse_file_std (finput_std, mhs, &size_mhs, &prt_std, ang_gender);  

    // Parse FILE dorm
    parse_file_drm ( finput_drm, dorms, &size_dorm, &prt_dorm, ang_gender);


    finput_std = fopen("./storage/student-repository.txt", "a");
    finput_drm = fopen("./storage/dorm-repository.txt", "a");

    fprintf(finput_std,"\n");
    fprintf(finput_drm,"\n");

    while (stop != 1) {
        fgets(input, sizeof(input), stdin);
        input[strcspn(input,"\r\n")] = 0;
        strcpy(kalimat, input);

        strcpy(command , strtok(kalimat, "#"));
        if (strcmp(command, "student-add") == 0){

            strcpy(data_id ,strtok(NULL, "#"));
            strcpy(data_name ,strtok(NULL, "#"));
            strcpy(data_year , strtok(NULL, "#"));
            strcpy( data_gender, strtok(NULL, "#"));

            ang_gender = gender_to_value (data_gender);
            
            for(int i = prt_std; i<size_mhs; i++){
                mhs[i] = create_student(data_id, data_name, data_year, ang_gender);
                fprintf(finput_std,"%s|%s|%s|%s\n",mhs[i].id, mhs[i].name, mhs[i].year, gender_to_text (mhs[i].gender));

            }
            size_mhs++;
            prt_std++;

        }else if(strcmp(command, "student-print-all-detail") == 0){
            student_print_detail(mhs, prt_std);

        }else if(strcmp(command, "student-print-all") == 0){
            student_print_all(mhs,prt_std);
            
        }else if(strcmp(command, "dorm-add") == 0){
            strcpy(data_id ,strtok(NULL, "#"));
            
            unsigned short int capacity;
            strcpy(data_year , strtok(NULL, "#"));
            capacity = atoi(data_year);

            strcpy( data_gender, strtok(NULL, "#"));

            ang_gender = gender_to_value (data_gender);

            for(int i = prt_dorm; i<size_dorm; i++){
                dorms[i] = create_dorm(data_id, capacity, ang_gender);

                fprintf(finput_drm,"%s|%d|%s\n",dorms[i].name, dorms[i].capacity, gender_to_text (dorms[i].gender));
            }
            size_dorm++;
            prt_dorm++;

        }else if(strcmp(command, "dorm-print-all-detail") == 0){
            print_all_dorm (dorms, prt_dorm);
            
        }else if(strcmp(command, "dorm-print-all") == 0){
            print_name_dorm (dorms, prt_dorm);

        }else if(strcmp(command, "assign-student") == 0){
            strcpy(data_id ,strtok(NULL, "#"));
            strcpy(data_name, strtok(NULL, "#"));
            
            poin_std = 0;
            poin_drm = 0;

            poin_std = get_index_student (mhs, prt_std, data_id);

            poin_drm = get_index_dorm (dorms, prt_dorm, data_name);
            
            assign_student(mhs, dorms, poin_std, poin_drm);

        }else if(strcmp(command, "---") == 0){
            stop = 1;
        }
    }
    
    fclose(finput_std);
    fclose(finput_drm);
    free(mhs);
    free(dorms);

    return 0;
}



