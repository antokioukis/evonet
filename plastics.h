#include "counters.h"
#include "deletes.h"


void place_on_plastic_array(personal_records *personal_record,int step){
    int i;
    unsigned int final_res;
    int periodos;

    if(personal_record->ptr_to_plastics->discrete_plastic[0]<0) final_res=0;
    else final_res=1;

    for (i=1;i<genes_per_person;i++){

        if(personal_record->ptr_to_plastics->discrete_plastic[i]<0){final_res=concatenate(final_res,0);}
        else final_res=concatenate(final_res,1);
    }
  //  printf("Thesi Pinaka %d \n",final_res);

    if (personal_record->ptr_personal_plastic_array->plastic_recs[binary_to_decimal(final_res)]==0){
        personal_record->ptr_personal_plastic_array->plastic_recs[binary_to_decimal(final_res)]=step;
       // printf("step %d\n",step);
    }
    else {
        personal_record->isplastic=true;
        //printf("Bin_dec %ld \n",bin_dec(final_res));
        if(binary_to_decimal(final_res)==distance_to_first_gen()) {
            periodos=step;
        }
        else {
            periodos=step-personal_record->ptr_personal_plastic_array->plastic_recs[binary_to_decimal(final_res)];
        }
      //  printf("Periodos %d \n",periodos);
    }

}

/*create new plastic rec multiplying matrix gene_dependencies with the latest plastic records*/
/*call function to make the results discrete*/
/*call function to find the appropriate place on the personal array*/
void create_new_plastic_recs(personal_records *personal_record,int step){
    int i,j;
    float a;
    int b;
    float temp[genes_per_person];
    /*scan individual*/
    for (i=0;i<genes_per_person;i++){
            for(j=0;j<genes_per_person;j++){
                a=personal_record->gene_dependancies->gene_inter_matrix[i][j];
                b=personal_record->ptr_to_plastics->discrete_plastic[j];
                temp[i]+=(a*b);
            }
    }
    /*
    for(i=0;i<genes_per_person;i++){
        printf("Apotelesma pollaplasiasmou %f\n",temp[i]);
    }
    */
    make_discrete(personal_record, temp);
    place_on_plastic_array(personal_record,step);
}

/*check if whole population is plastic*/
int check_pop_plastic(population_list *plist_head){
    population_list *temp=plist_head;
    int j;
    while(temp!=NULL){
        for(j=0;j<group_persons;j++){

            if(!temp->groups->personal_record[j]->isplastic){
                 return 0;
            }

        }
        temp=temp->next;
    }
    return 1;
}

void mature_pop(population_list *plist_head){
    population_list *temp=plist_head;
    int i,total_steps=1;

    while(!check_pop_plastic(temp)){
       // printf("\n");
       // printf("Maturity step %d\n",total_steps);
        while(temp!=NULL){
            for(i=0;i<group_persons;i++){

                if(!(temp->groups->personal_record[i]->isplastic)){
                    create_new_plastic_recs(temp->groups->personal_record[i],total_steps);
                }

            }
            temp=temp->next;
        }
        temp=plist_head;

        if((total_steps%100==0)||(total_steps%50==0)){printf("Maturity step %d\n",total_steps);}
        if (total_steps>200) {remove_immatures(temp); return;}
        total_steps++;
    }
}
