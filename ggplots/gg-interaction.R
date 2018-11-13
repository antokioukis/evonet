#gia ka8e optimal vec
#    gia ka8e 1 apo 100 runs
#        diavase to matrix.txt
#        3exwrise tis genies
#            500 atoma h genia
#            5000 grammes h ka8e mia genia sto interaction matrix
#            bres mou to a8roisma twn 5k grammwn
#            bale mou ena point pou simainei a8roisma genias des pws pane auta ta simeia oso pernane oi genies


#diavase kai to fitnesss.txt kai bres apo poio mexri poio simeio einai ta bins sou
#pare to vector pou 8a girizoun oi sinartiseis kai bres mou to average expression gia to sigkekrimeno bin
#gia ola ta run kai bgale mou to mean
#kai meta na plottaroume mono ta mean twn mean
#bins<-c(0.53,0.54,0.56,0.58,0.61,0.63,0.67,0.7,0.75,0.81,0.95)
#giati ston ave_bin exw na stin prwti 8esi

#stin average sum bin
#anti na metras to mean
#metra posa megalitera tou 0 posa mikrotera kai kane return to pli8os tous
bins<-c(0.53,0.54,0.56,0.58,0.61,0.63,0.67,0.7,0.75,0.81)
optimal_vec <- c("1111111111","1111100000","1100110011","1010101010")
library(ggplot2)
library(foreach)
library(doMC)
registerDoMC(30)

R1R2_sum <- function(R1,R2){
    generations <- seq(1,nrow(R1),500)
    summ_r1<-c()
    summ_r2<-c()
    for (i in 2:length(generations)){
        katw_orio <- generations[i-1]
        panw_orio <- generations[i]
        data_r1 <- R1[katw_orio:panw_orio,]
        data_r2 <- R2[katw_orio:panw_orio,]
        summ_r1<-c(summ_r1,sum(log10(data_r1)))
        summ_r2<-c(summ_r2,sum(log10(data_r2)))
    }
    print(length(summ_r1))
    return(list(summ_r1,summ_r2))
    #plot((summ_r1))
}

inter_sum <- function(inter_matrix){
    generations <- seq(1,nrow(inter_matrix),500)
    summation_vec<-c()
    for (i in 2:length(generations)){
        katw_orio <- generations[i-1]
        panw_orio <- generations[i]
        data <- inter_matrix[katw_orio:panw_orio,]
        pos_counter<-0
        for (j in 1:nrow(data)){
            for (k in 1:ncol(data)){
                if(data[j,k]>0){
                    pos_counter<-pos_counter+1
                }
            }
        }
        print(pos_counter)
        summation_vec<-c(summation_vec,sum(data))
    }
    return(summation_vec)
}

inter_pos <- function(inter_matrix,flag){
    generations <- seq(1,nrow(inter_matrix),500)
    pos_vec<-c()
    #print(length(generations))
    for (i in 2:length(generations)){
        katw_orio <- generations[i-1]
        panw_orio <- generations[i]
        data <- inter_matrix[katw_orio:panw_orio,]
        #pos_counter<-0
        #for (j in 1:nrow(data)){
        #    for (k in 1:ncol(data)){
        #        if(data[j,k]>0){
        #            pos_counter<-pos_counter+1
        #        }
        #    }
        #}
        #print(pos_counter)
        if(flag==1){
            pos_counter <- length(which(data>0))
        #print(pos_counter)
        }
        else{
            pos_counter <- length(which(data<0))
        }
        pos_vec<-c(pos_vec,pos_counter)
    }
    return(pos_vec)
}

find_average_fitness <- function(fitness){
    fitness_vec<-c()
    for (j in 1:length(bins)){
        search_for<-bins[j]
        find_index<-min(which(fitness>search_for))
        if(!is.finite(find_index)){
            fitness_vec[j]<-length(fitness)
        }
        else{
            fitness_vec[j]<-find_index
        }
    }
    return (fitness_vec)
}

average_pos_bin <- function(fitness_vec,pos_vec){
    ave_pos_bin_vec<-c()
    for (i in 2:length(fitness_vec)){
        katw_orio <- fitness_vec[i-1]
        panw_orio <- fitness_vec[i]
        data<-pos_vec[katw_orio:panw_orio]
        ave_pos_bin_vec[i]<-mean(data)
    }
    return(ave_pos_bin_vec)
}

runs<-100
final_mat <- matrix(nrow=4,ncol=10)
final_mat_pos <- matrix(nrow=4,ncol=10)
final_mat_neg <- matrix(nrow=4,ncol=10)
for (i in 1:length(optimal_vec)){
#for (i in 1:1){
    base_name<-paste("/home/pavlos/synology/kioukis/evo4/500selection",optimal_vec[i],".run.",sep="")
    #ave_bin <- matrix(nrow=100,ncol=10)
    ave_pos_bin <- matrix(nrow=100,ncol=10)   
    ave_neg_bin <- matrix(nrow=100,ncol=10)    
    for (j in 1:runs){
    #ave_pos_bin_list<-foreach(j = 1:runs,.combine = append) %dopar% {
        dir_name <- paste(base_name,j,sep="")
        print(dir_name)
        setwd(dir_name)
        #r1 <- read.table("R1.txt")
        #r2 <- read.table("R2.txt")
        #r1r2list <- R1R2_sum(r1,r2)
        #mikos_r1r2list <- length(r1r2list)
        #r1_sum <- r1r2list[1]
        #r2_sum <- r1r2list[2]
        inter_matrix <- read.table("matrix.txt")
        pos_vec<-inter_pos(inter_matrix,1)
        neg_vec<-inter_pos(inter_matrix,0)
        fitness_tab <- read.table("fitnesss.txt")
        fitness <- fitness_tab[,4]
        fitness_vec<-find_average_fitness(fitness)
        #print(fitness_vec)
        ave_pos <- average_pos_bin(fitness_vec,pos_vec)
        ave_neg <- average_pos_bin(fitness_vec,neg_vec)
        print(ave_pos)
        #ave_pos <- average_positive(fitness_vec,generations_sum)
        #ave_bin[j,] <- ave_pos_bin
        #return (ave_pos)
        ave_pos_bin[j,] <- ave_pos
        ave_neg_bin[j,] <- ave_neg
    }
    #final_mat[i,] <- colMeans(ave_bin,na.rm="TRUE")
    final_mat_pos[i,] <- colMeans(ave_pos_bin,na.rm="TRUE")
    final_mat_neg[i,] <- colMeans(ave_neg_bin,na.rm="TRUE")

}