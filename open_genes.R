rm(list=ls())

n<-2000

clear<-function(){
  system("clear")
}


read_data <- function(fdirName,curDir,n) {
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
  list12 <- c()
  list13 <- c()
  list14 <- c()
  list15 <- c()
  list16 <- c()

  open_genes_array<-matrix(nrow=15001,ncol=n)

  differences<-c(0.999,0.99,0.98,0.97,0.96,0.95,0.818731,
                0.753638,0.707222,0.670320,0.639407,0.612689,
                0.589105,0.567971,0.548812,0.531286)

  final_array<-matrix(nrow=n,ncol=16)
  for(i in 1:n){
      print(i)
      
      if(i==1548){
        next
      }
      dirName <- paste(curDir,"/",fdirName,"run.", i, sep="")
      if(!dir.exists(file.path(dirName))){next}
      else{
          setwd(dirName)
          open_genes<-read.table("open_genes.txt")
          fitness<-read.table("fitnesss.txt")
          print(fitness[nrow(fitness),4])
          #print(length(unique(fitness[,4])))
          #print(unique(fitness[,4]))
          if(fitness[nrow(fitness),4]<0.96){
              next
          }
      }
          ##edw exeis to meso oro open genes per generation
      open_genes_mean<-rowMeans(open_genes)
      #final_open[,i]<-open_genes_mean
      #plot(open_genes_mean,type="p")
      #print(open_genes_mean)
      temp_data<-cbind(open_genes_mean,fitness[,4])
      #print(temp_data)
      first_tar_fit<-min(which(temp_data[,2] > 0.95))+1
      #pdf("bonus_gens.pdf")
      #plot(x=first_tar_fit:nrow(temp_data),y=temp_data[first_tar_fit:nrow(temp_data),1])
      #dev.off()
      if(first_tar_fit+15000>nrow(fitness)){
            print("poli arga")
            next
      }

      open_genes_array[,i]<-temp_data[first_tar_fit:nrow(temp_data),1]


      colnames(temp_data) <- NULL

      for (j in 1:first_tar_fit){

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
        else if(temp_data[j,2]>differences[11]){
          list11<-c(list11,temp_data[j,1])
        }
        else if(temp_data[j,2]>differences[12]){
          list12<-c(list12,temp_data[j,1])
        }
        else if(temp_data[j,2]>differences[13]){
          list13<-c(list13,temp_data[j,1])
        }
        else if(temp_data[j,2]>differences[14]){
          list14<-c(list14,temp_data[j,1])
        }
        else if(temp_data[j,2]>differences[15]){
          list15<-c(list15,temp_data[j,1])
        }
        else{
          list16<-c(list16,temp_data[j,1])
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
      final_array[i,12]<-mean(list12, na.rm=TRUE)
      final_array[i,13]<-mean(list13, na.rm=TRUE)
      final_array[i,14]<-mean(list14, na.rm=TRUE)
      final_array[i,15]<-mean(list15, na.rm=TRUE)
      final_array[i,16]<-mean(list16, na.rm=TRUE)

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
      list12 <- c()
      list13 <- c()
      list14 <- c()
      list15 <- c()
      list16 <- c()
  }
  
  setwd("~/evo4")
  write.table(open_genes_array,file="after10.txt")
  #plot(x=1:2001,y=rowMeans(open_genes_array,na.rm=TRUE))
  return(final_array)
}

#n<-2000
curDir<-"~/evo4"
fdirName<-"500selection101rr0.05."

output_data<-read_data(fdirName,curDir,n)
setwd(curDir)
write.table(output_data,file="before10.txt")



#h logiki einai:
# diavase to open_genes.txt kai to fitness.txt
# enwse ta 2 txt giati panta 8a exoun to idio length logw oti anikoun sto idio run
# katigoroiopoihse tis grammes twn combined data se bins analoga me to generation fitness
# epanelabe tin diadikasia gia ola ta runs
# bgale to colmean kai plottare to
