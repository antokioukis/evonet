max_gens_needed_95<-1
max_gens_needed<-1
read_data <- function(fdirName,curDir,n,min_open_genes,max_open_genes) {
  keep_runs<-c()
  for(i in 1:n){
      #print(i)
    #dirName <- fdirName
      dirName <- paste(curDir,"/",fdirName,"run.", i, sep="")
      if(!dir.exists(file.path(dirName))){
        next
      }
      else{
          setwd(dirName)
          open_genes<-read.table("open_genes.txt")
          fitness<-read.table("fitnesss.txt")
          #print(fitness[nrow(fitness),4])
          #print(length(unique(fitness[,4])))
          #print(unique(fitness[,4]))
          if(fitness[nrow(fitness),4]<0.96){
              next
          }
          ##edw exeis to meso oro open genes per generation
          open_genes_mean<-rowMeans(open_genes)
          #final_open[,i]<-open_genes_mean
          #plot(open_genes_mean,type="p")
          #print(open_genes_mean)
          temp_data<-cbind(generations=1:nrow(fitness),fitness=fitness[,4],open_genes_mean)
        #  write.table(temp_data,file="gen_fit_me.txt")
          tar_fit_gen<-min(which(temp_data[,2] > 0.95))+1
          #print(tar_fit_gen)
          if(temp_data[tar_fit_gen,3]<min_open_genes || temp_data[tar_fit_gen,3]>max_open_genes){
            next
          }
          if (max_gens_needed_95<tar_fit_gen){
              max_gens_needed_95<<-tar_fit_gen
          }
          if (max_gens_needed<nrow(temp_data)){
              max_gens_needed<<-nrow(temp_data)
          }
          write.table(temp_data,file="gen_fit_me.txt")
          keep_runs<-c(keep_runs,i)
      }
  }
  #print(max_gens_needed_95)
  #print(max_gens_needed)
  return(keep_runs)
}

plot_kept<-function(fdirName,curDir,keep_runs,min_open_genes,max_open_genes){
  after_data<-matrix(nrow=15000,ncol=length(keep_runs))
  row_num<-1
  if(length(keep_runs)){
    pdf(paste("means",min_open_genes,"_",max_open_genes,".pdf",sep=""))
    for(i in keep_runs){

        #print(i)
        dirName <- fdirName
        dirName <- paste(curDir,"/",fdirName,"run.", i, sep="")
        setwd(dirName)
        data<-read.table("gen_fit_me.txt")
        tar_fit_gen<-min(which(data[,2] > 0.95))+1
        print(tar_fit_gen)

        after_data[,row_num]<-data[(tar_fit_gen+1):nrow(data),3]

        pros8eteos<-max_gens_needed_95-tar_fit_gen
        data[,1]<-data[,1]+pros8eteos

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
      dev.off()
  }
}

n<-100
curDir<-"~/evo4"
fdirName<-"500selection51rr0.05."
#final_open<-matrix(nrow=100,ncol=1000)
for (i in 0:5){
 # i<-1
  print(i)
  max_gens_needed_95<<-1
  max_gens_needed<<-1
  min_open_genes<-i-0.5
  max_open_genes<-i+0.5
  keep_runs<-read_data(fdirName,curDir,n,min_open_genes,max_open_genes)
  keep_runs_backup<-keep_runs
  print(keep_runs)
  setwd(curDir)
  #print(max_gens_needed_95)
  #print(max_gens_needed)
  if (length(keep_runs_backup)==0){
    next
  }
  plot_kept(fdirName,curDir,keep_runs_backup,min_open_genes,max_open_genes)
}
