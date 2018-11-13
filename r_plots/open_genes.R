rm(list=ls())

read_data <- function(fdirName,curDir,n) {
  final_open<-matrix(nrow=500,ncol=100)
  vec<-c()
  list1 <- c()
  list2 <- c()
  list3 <- c()
  list4 <- c()
  list5 <- c()
  list6 <- c()
  list7 <- c()
  list8 <- c()
  list9 <- c()
  list10 <- c()
  list11 <- c()
  mylist <- list(list1,list2,list3,list4,list5,list6, list7,list8 ,list9, list10,list11)
  differences<-c(1.000000,0.818731,0.753638,0.707222,0.670320,0.639407,0.612689,0.589105,0.567971,0.548812,0.531286)
  final_array<-matrix(nrow=100,ncol=11)
  for(i in 1:n) {
      print(i)
    #dirName <- fdirName
      dirName <- paste(curDir,"/",fdirName,"run.", i, sep="")
      if(!dir.exists(file.path(dirName))){next}
      else{
          setwd(dirName)
          open_genes<-read.table("open_genes.txt")
          fitness<-read.table("fitnesss.txt")
          ##print(fitness[nrow(fitness),4])
          print(length(unique(fitness[,4])))
          #print(unique(fitness[,4]))
          if(fitness[nrow(fitness),4]<0.80){
              next
          }
          ##edw exeis to meso oro open genes per generation
      open_genes_mean<-rowMeans(open_genes)
      #final_open[,i]<-open_genes_mean
      #plot(open_genes_mean,type="p")
      #print(open_genes_mean)
          temp_data<-cbind(open_genes_mean,fitness[,4])
          print(temp_data)
      colnames(temp_data) <- NULL
      for (j in 1:nrow(temp_data)){
        if(temp_data[j,2]>differences[1]){
          list1<-c(list1,temp_data[j,1])
        }
        else if(temp_data[j,2]>differences[2]){
          list2<-c(list2,temp_data[j,1])
        }
        else if(temp_data[j,2]>differences[3]){
          list3<-c(list3,temp_data[j,1])
        }
        else if(temp_data[j,2]>differences[4]){
          list4<-c(list4,temp_data[j,1])
        }
        else if(temp_data[j,2]>differences[5]){
          list5<-c(list5,temp_data[j,1])
        }
        else if(temp_data[j,2]>differences[6]){
          list6<-c(list6,temp_data[j,1])
        }
        else if(temp_data[j,2]>differences[7]){
          list7<-c(list7,temp_data[j,1])
        }
        else if(temp_data[j,2]>differences[8]){
          list8<-c(list8,temp_data[j,1])
        }
        else if(temp_data[j,2]>differences[9]){
          list9<-c(list9,temp_data[j,1])
        }
        else if(temp_data[j,2]>differences[10]){
          list10<-c(list10,temp_data[j,1])
        }
        else{
          list11<-c(list11,temp_data[j,1])
        }
      }
      final_array[i,1]<-mean(list1, na.rm=TRUE)
      final_array[i,2]<-mean(list2, na.rm=TRUE)
      final_array[i,3]<-mean(list3, na.rm=TRUE)
      final_array[i,4]<-mean(list4, na.rm=TRUE)
      final_array[i,5]<-mean(list5, na.rm=TRUE)
      final_array[i,6]<-mean(list6, na.rm=TRUE)
      final_array[i,7]<-mean(list7, na.rm=TRUE)
      final_array[i,8]<-mean(list8, na.rm=TRUE)
      final_array[i,9]<-mean(list9, na.rm=TRUE)
      final_array[i,10]<-mean(list10, na.rm=TRUE)
          final_array[i,11]<-mean(list11, na.rm=TRUE)
          ##final_array[is.na(final_array)] <- 0
      list1 <- c()
      list2 <- c()
      list3 <- c()
      list4 <- c()
      list5 <- c()
      list6 <- c()
      list7 <- c()
      list8 <- c()
      list9 <- c()
      list10 <- c()
      list11 <- c()
    }
  }
  return(final_array)
}

n<-100
curDir<-"~/evo3"
fdirName<-"500selection1rr0.05."
#final_open<-matrix(nrow=100,ncol=1000)

output_data<-read_data(fdirName,curDir,n)
plot(colMeans(output_data, na.rm=TRUE))

output_data

#final_data<-colMeans(final_data,na.rm=TRUE)
output_data2<-output_data
output_data
keep_vec<-c()
for (i in 1:nrow(output_data2)){

  print(sum(output_data2[i,]))
  if(sum(output_data2[i,])!=0){ keep_vec<-c(keep_vec,i)}
}

output_data2<-output_data2[keep_vec,]

y <- colMeans(output_data, na.rm=TRUE)
x <- differences<-c(1.000000,0.818731,0.753638,0.707222,0.670320,0.639407,0.612689,0.589105,0.567971,0.548812,0.531286)

output_data

library(ggplot2)
data <- data.frame(opengenes=x, fitbin=y)
ggplot(data, aes(x=opengenes, y=fitbin)) + geom_point(shape=1)


plot_vec<-c(colMeans(output_data2))

plot(seq(0, 1, 0.1),plot_vec,ylab="Mean open genes",xlab="Generation Fitness")

#h logiki einai:
# diavase to open_genes.txt kai to fitness.txt
# enwse ta 2 txt giati panta 8a exoun to idio length logw oti anikoun sto idio run
# katigoroiopoihse tis grammes twn combined data se bins analoga me to generation fitness
# epanelabe tin diadikasia gia ola ta runs
# bgale to colmean kai plottare to
