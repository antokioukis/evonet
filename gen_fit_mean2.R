read_data <- function(fdirName,curDir,n) {
  for(i in 1:n){
    #print(i)
    #dirName <- fdirName
    dirName <- paste(curDir,"/",fdirName,"run.", i, sep="")
    setwd(dirName)
    open_genes<-read.table("open_genes.txt")
    fitness<-read.table("fitnesss.txt")
    if(fitness[nrow(fitness),4]<0.95){
        next
    }

    ##edw exeis to meso oro open genes per generation
    open_genes_mean<-rowMeans(open_genes)
    temp_data<-cbind(generations=1:nrow(fitness),fitness=fitness[,4],open_genes_mean)
    write.table(temp_data,file="gen_fit_me.txt")
  }
}

run_seperate <- function(fdirName,curDir,n) {

  keep_runs1<-c()
  keep_runs2<-c()
  keep_runs3<-c()
  keep_runs4<-c()
  keep_runs5<-c()
  keep_runs6<-c()

  max_gens_needed_95<-c(rep.int(0,6))
  max_gens_needed<-c(rep.int(0,6))

  for (i in 1:n){
    if(i==948){
      next
    }
    dirName <- paste(curDir,"/",fdirName,"run.", i, sep="")
    setwd(dirName)
    temp_data<-read.table("gen_fit_me.txt")
    tar_fit_gen<-min(which(temp_data[,2] > 0.95))+1

    for (j in 1:6){
      min_open_genes<-j-1.5
      max_open_genes<-j-0.5
      if(temp_data[tar_fit_gen,3]<min_open_genes || temp_data[tar_fit_gen,3]>max_open_genes){
        next
      }
      #print(max_gens_needed_95[j])
      #print(tar_fit_gen)

      if (max_gens_needed_95[j]<tar_fit_gen){
          print(i)
          max_gens_needed_95[j]<-tar_fit_gen
      }
      if (max_gens_needed[j]<nrow(temp_data)){
          print(i)
          print(nrow(temp_data))
          max_gens_needed[j]<-nrow(temp_data)
      }
      if(j==1){
        keep_runs1<-c(keep_runs1,i)
      }
      if(j==2){
        keep_runs2<-c(keep_runs2,i)
      }
      if(j==3){
        keep_runs3<-c(keep_runs3,i)
      }
      if(j==4){
        keep_runs4<-c(keep_runs4,i)
      }
      if(j==5){
        keep_runs5<-c(keep_runs5,i)
      }
      if(j==6){
        keep_runs6<-c(keep_runs6,i)
      }
    }

  }

  list1<-list(keep_runs1,keep_runs2,keep_runs3,keep_runs4,keep_runs5,keep_runs6,max_gens_needed_95,max_gens_needed)
  print(max_gens_needed_95)
  print(max_gens_needed)
  return(list1)
}


plot_kept<-function(fdirName,curDir,keep_runs,min_open_genes,max_open_genes,max_gens_needed_95,max_gens_needed){
  after_data<-matrix(nrow=15000,ncol=length(keep_runs))
  row_num<-1
  if(length(keep_runs)){
    pdf(paste("mean_",min_open_genes,max_open_genes,"_genes.pdf",sep=""))
    for(i in keep_runs){
        print(i)
        dirName <- fdirName
        dirName <- paste(curDir,"/",fdirName,"run.", i, sep="")
        setwd(dirName)
        data<-read.table("gen_fit_me.txt")

        tar_fit_gen<-min(which(data[,2] > 0.95))+1

        #print (i)
        after_data[,row_num]<-data[(tar_fit_gen+1):nrow(data),3]

        #print(max_gens_needed_95)
        #print(max_gens_needed)
        pros8eteos<-max_gens_needed_95-tar_fit_gen
        data[,1]<-data[,1]+pros8eteos

        #print(length(data[,1]))
        #print(length(data[,3]))

        if(row_num==1){
          plot(x=data[,1],y=data[,3],xaxs="i",yaxs="i",ylim=c(0,5), xlim=c(0,max_gens_needed),col="grey",type="l",lwd=1,ylab="Mean of Open Genes",xlab="Generations")
        }
        else{
          lines(x=data[,1],y=data[,3],xaxs="i",yaxs="i",ylim=c(0,5), xlim=c(0,max_gens_needed),col="grey",type="l",lwd=1)
          }
          row_num<-row_num+1
      }
      lines(x=(max_gens_needed_95+1):max_gens_needed,y=rowMeans(after_data),col="blue",lwd=3)
      abline(v = max_gens_needed_95, col="red", lwd=3)
      title("Size changes in GRNs over time")
      mtext(paste(length(keep_runs),"/",2000," runs: mean open genes ",min_open_genes,"-",max_open_genes," when fitness=0.95:",sep=""))
      setwd(curDir)
      dev.off()
  }
}


n<-2000
curDir<-"~/evo4"
fdirName<-"500selection101rr0.05."
#final_open<-matrix(nrow=100,ncol=1000)
#keep_runs<-
read_data(fdirName,curDir,n)
keep_runs<-run_seperate(fdirName,curDir,n)
keep_runs_backup<-keep_runs

for (i in 1:6){
  max_gens_needed_95<-unlist(keep_runs[7])[i]
  max_gens_needed<-unlist(keep_runs[8])[i]
  min_open_genes<-i-1.5
  max_open_genes<-i-0.5
  #corresponding runs of range min_open_genes - max_open_genes
  corr_runs<-unlist(keep_runs_backup[i])
  corr_runs<-corr_runs[!(corr_runs==948)]

  print(corr_runs)
  if (!length(corr_runs)==0){
    plot_kept(fdirName,curDir,corr_runs,min_open_genes,max_open_genes,max_gens_needed_95,max_gens_needed)
  }
}
i<-3
