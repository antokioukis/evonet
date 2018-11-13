rm(list=ls())
library(foreach)
library(doMC)
registerDoMC(30)

system("make clean")
system("make all")

n <- 100 #25
r <- 100000
s <- 5
sel <- 1
ploidy <- 1
freq <- 10
robust_mutations <- 15
seed_pos <- 1
randInt <- floor(runif(1000000, 0, 10000000))
write.table(randInt, file="seeds.txt", quote=F, row.names=F, col.names=F)


################################################################################################################################################
################################################################################################################################################
#-rob X:                     Check for robustness (Binary) 
#-num_of_rob_mutation X:     Number of mutations per robustness check (Integer) 
#-rob_last                   On robust mutations change last bit of R1 R2 interactions (Binary)



create_sim<-function(N,name,mr){
	#mr <- 10/N
	curDir <- getwd()
	sel<-1
  foreach(i = 1:n) %dopar% {
	    seed <- randInt[seed_pos+i]
	    dirName <- paste(name, ".run.", i, sep="")
	    dir.create(file.path(curDir, dirName), showWarnings=FALSE)
	    working_dir<-file.path(curDir, dirName)
	  #  print(working_dir)
	    setwd(working_dir)
	    system(paste("Rscript ",curDir, "/write_file.R > ", working_dir,"/R1R2_input.txt",sep=""))
	 #   print("meta")
	    cmd <- paste(curDir, "/evonet -tarfit 0.95 -key_genes 10 -selection ", sel," -st_geno R1R2_input.txt -s2 ", s, " -N ", N," -ploidy 1 -freq ", freq, " -generations ",r ," -n 10 -mutrate ",mr, " -seed ", seed, " -optimal_num 10",sep="")
	    system(cmd)
      cmd <- paste(curDir, "/fitnessSimple -mu " ,mr, " -l 10 -popsize ", N," -fm 1 -s ", s, " -p 2 -seed ", seed, sep="")
	    system(cmd)
      setwd(curDir)
  }
  seed_pos<<-seed_pos+n
}

################################################################################################################################################
################################################################################################################################################

#rr_vec<-c(0,0.0001,0.001,0.005,0.01,0.05,0.1)
#N_vec<-c(200,500,1000)
#swapp_vec<-c(1,2)
swapp_vec<-c(1)
swapp<-1
N<-500
N_vec<-c(500) #500 1000
mr_vec<-seq(0.05,0.10,by=0.01)


#mr<-mr_vec[1]
#for(j in 1:length(rr_vec)){ #
#        rr<-rr_vec[j]
#        name<-paste("500selection",swapp,"rr",rr,"mr",mr,sep="")
#        print(name)
#        create_sim(swapp,rr,N,name,mr)
#}
rr <- 0.05
for(j in 1:length(mr_vec)){ #
  mr<-mr_vec[j]
	name<-paste("500selection.",mr,sep="")
	create_sim(N,name,mr)
}
