rm(list=ls())
library(foreach)
library(doMC)
registerDoMC(8)

#system("make clean")
system("make all")

n <- 2000 #25
r <- 100000
s<- 5
sel <- 1
ploidy <- 1
freq<-1
robust_mutations<-15

randInt <- floor(runif(n, 0, 10000000))
write.table(randInt, file="seeds.txt", quote=F, row.names=F, col.names=F)


################################################################################################################################################
################################################################################################################################################

create_sim<-function(swapp,rr,N,name){
	mr <- 10/N
	curDir <- getwd()
	sel<-1
	foreach(i = 1:n) %dopar% {
	    seed <- randInt[i]
	    dirName <- paste(name, ".run.", i, sep="")
	    dir.create(file.path(curDir, dirName), showWarnings=FALSE)
	    working_dir<-file.path(curDir, dirName)
	    print(working_dir)
	    setwd(file.path(curDir, dirName))
	    system(paste("Rscript ",curDir, "/write_file.R > ", working_dir,"/R1R2_input.txt",sep=""))
	    print("meta")
	    cmd <- paste(curDir, "/evonet -tarfit 0.95 -key_genes 5 -selection ", sel," -st_geno R1R2_input.txt -s2 ", s, " -N ", N," -ploidy ", ploidy, " -swapping ",swapp," -freq ", freq, " -generations ",r ," -n 10 -recomb_rate ",rr ," -mutrate ",mr, " -seed ", seed, " -optimal_num 10", sep="")
	   	print(cmd)
	    system(cmd)
	}
}

################################################################################################################################################
################################################################################################################################################

#rr_vec<-c(0,0.0001,0.001,0.005,0.01,0.05,0.1)
#N_vec<-c(200,500,1000)
#swapp_vec<-c(1,2)
swapp_vec<-c(1)
rr_vec<-(0.05)
N_vec<-c(500) #500 1000

for(i in 1:1){ #2
	swapp<-swapp_vec[i]
	for(j in 1:1){ #3
		N<-N_vec[j]
		for (k in 1:1){ #7
			rr<-rr_vec[k]
			name<-paste(N,"selection6",swapp,"rr",rr,sep="")
			print(name)
			create_sim(swapp,rr,N,name)
		}
	}
}

#system("Rscript rob_top.R")
