rm(list=ls())

read_fitness <- function(fdirName,curDir,n) {
  final_fitness<-matrix(nrow=11,ncol=100)
  differences<-c(1.000000,0.818731,0.753638,0.707222,0.670320,0.639407,0.612689,0.589105,0.567971,0.548812,0.531286)
  rev_differences <- rev(differences)
  for(i in 1:n) {
      print(i)
      dirName <- paste(curDir,"/",fdirName, i, sep="")
      setwd(dirName)
      fitness<-read.table("fitnesss.txt")
      for (j in 1:(length(rev_differences)-1)){
        min_index <- min(which(fitness>rev_differences[j]))
        final_fitness[j,i] <- min_index
      }
      final_fitness[11,i] <- nrow(fitness)
  }
  return (final_fitness)
}


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
      dirName <- paste(curDir,"/",fdirName, i, sep="")
      if(!dir.exists(file.path(dirName))){next}
      else{
          setwd(dirName)
          open_genes<-read.table("open_genes.txt")
          fitness<-read.table("fitnesss.txt")
          ##print(fitness[nrow(fitness),4])
          print(length(unique(fitness[,1])))
          #print(unique(fitness[,4]))
          #if(fitness[nrow(fitness),1]<0.80){
          #    next
          #}
          ##edw exeis to meso oro open genes per generation
      open_genes_mean<-rowMeans(open_genes)
      #final_open[,i]<-open_genes_mean
      #plot(open_genes_mean,type="p")
      #print(open_genes_mean)
      temp_data<-cbind(open_genes_mean,fitness[,1])
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
curDir<-"/home/antonios/Downloads/evonet/"
fdirName<-"500selection.0.05.run."
#final_open<-matrix(nrow=100,ncol=1000)

output_data<-read_data(fdirName,curDir,n)
'''
plot(colMeans(output_data, na.rm=TRUE))

output_data

#final_data<-colMeans(final_data,na.rm=TRUE)
output_data2<-output_data
output_data
keep_vec<-c()
for (i in 1:nrow(output_data2)){
  print(sum(output_data2[i,]))
  if(sum(output_data2[i,])!=0){
    keep_vec<-c(keep_vec,i)
  }
}


output_data2<-output_data2[keep_vec,]
'''
y <- colMeans(output_data, na.rm=TRUE)
trans_out_data <- melt(t(output_data))
y[is.nan(y)] <- 0
x <- differences<-c(1.000000,0.818731,0.753638,0.707222,0.670320,0.639407,0.612689,0.589105,0.567971,0.548812,0.531286)

output_data
fit_data <- read_fitness(fdirName,curDir,n)
fit_data[10,64] <- 500 # den 3erw giati alla to run 64 den brike kati, logika ekane megalo alma apo to ena sto allo difference
fit_data <- data.frame(fit_data)
# mesos oros genias pou epiase auto to fitness level
trans_fit_data <- melt(t(fit_data))
rev_differences<-rev(c(1.000000,0.818731,0.753638,0.707222,0.670320,0.639407,0.612689,0.589105,0.567971,0.548812,0.531286))
replace_columns <- rep(rev_differences, each=100)
trans_fit_data$Var2 <- replace_columns
library(ggplot2)

g1 <- ggplot(trans_fit_data, aes(x=Var2,y=value, group=Var2)) + geom_boxplot()
g2 <- g1 + geom_point(aes(y=rep(y, each=100)),col='red') +
  scale_y_continuous(
    "mpg (US)", 
    sec.axis = sec_axis(~ . * 0.00001, name = "mpg (UK)")
  )

'''
data <- data.frame(opengenes=x, fitbin=y)
ggplot(data, aes(x=opengenes, y=fitbin)) + geom_point(shape=1, col='red')


plot_vec<-c(colMeans(output_data2))

plot(seq(0, 1, 0.1),plot_vec,ylab="Mean open genes",xlab="Generation Fitness")
'''
#h logiki einai:
# diavase to open_genes.txt kai to fitness.txt
# enwse ta 2 txt giati panta 8a exoun to idio length logw oti anikoun sto idio run
# katigoroiopoihse tis grammes twn combined data se bins analoga me to generation fitness
# epanelabe tin diadikasia gia ola ta runs
# bgale to colmean kai plottare to

# to parataw gia twra giati prepei na doulepsw kai ligo gia ton ilia
# h teleutaia idea einai na na exeis grouped barplot 2 koutia ana fitness level to ena na deixnei to fitness kai to allo na deixnei ta open genes
