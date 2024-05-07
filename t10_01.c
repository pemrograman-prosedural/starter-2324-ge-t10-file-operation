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

    
    int ang_gender = 0;

    struct student_t *mhs = malloc(20 * sizeof(struct student_t));
    struct dorm_t *dorms = malloc(20 * sizeof(struct dorm_t));


    unsigned short int stop = 0;

    unsigned short int size_mhs = 1, prt_std = 0;
    unsigned short int size_dorm = 1, prt_dorm = 0;


    FILE *finput_std = fopen("./storage/student-repository.txt" , "r");
    FILE *finput_drm = fopen("./storage/dorm-repository.txt" , "r");

    // Parse FILE STD
    parse_file_std (finput_std, mhs, &size_mhs, &prt_std, ang_gender);

    // Parse FILE dorm
    parse_file_drm ( finput_drm, dorms, &size_dorm, &prt_dorm, ang_gender);

    while (stop != 1) {
        fflush(stdin);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input,"\r\n")] = 0;
        strcpy(kalimat, input);

        strcpy(command , strtok(kalimat, "#"));
        if (strcmp(command, "student-print-all-detail") == 0){
            student_print_detail(mhs, prt_std);

        }else if(strcmp(command, "dorm-print-all-detail") == 0){
            print_all_dorm (dorms, prt_dorm);
            
        }else if(strcmp(command, "---") == 0){
            stop = 1;
        }
    }
    
    free(mhs);
    free(dorms);

    return 0;
}


