library(foreach)
library(doMC)
library(stringr)
registerDoMC(10)
rm(list=ls())


image_creation <- function(fdirName,outputName) {
	foreach(i = 1:n) %dopar% {
		similarity<-c()
		dis_similarity<-c()

		#dirName <- fdirName
	    dirName <- paste(curDir,"/",fdirName,".run.", i, sep="")
		setwd(dirName)

	    normal_topo<-read.table("matrix.txt")
	    rob_topo<-read.table("robustness.txt")

	    normal_discrete<-read.table("discrete.txt")
	    rob_discrete<-read.table("rob_discrete.txt")

	    normal_topo_matrix<-matrix(nrow=nrow(normal_topo),ncol=1)
	    rob_topo_matrix<-matrix(nrow=nrow(rob_topo),ncol=1)

	    normal_dis_matrix<-matrix(nrow=nrow(normal_discrete),ncol=1)
	    rob_dis_matrix<-matrix(nrow=nrow(rob_discrete),ncol=1)

	    #print(nrow(normal_topo)==nrow(rob_topo))
	    #print(nrow(normal_discrete)==nrow(rob_discrete))

		#allagi tou matrix gia tin dimiourgia boolean network
		normal_topo[normal_topo < 0] <- -1
		normal_topo[normal_topo > 0] <-  1
		normal_topo[normal_topo == 0] <-  0

		rob_topo[rob_topo < 0] <- -1
		rob_topo[rob_topo > 0] <-  1
		rob_topo[rob_topo == 0] <-  0


	    normal_topo_matrix<-apply(normal_topo, 1, paste, collapse="")
	    rob_topo_matrix<-apply(rob_topo, 1, paste, collapse="")

	    normal_dis_matrix<-apply(normal_discrete, 1, paste, collapse="")
	    rob_dis_matrix<-apply(rob_discrete, 1, paste, collapse="")

	    num_of_gens<-length(normal_topo_matrix)/popsize 
	    for (l in 1:num_of_gens){
		    normal_generation<-normal_topo_matrix[((l-1)*popsize+1):(l*popsize)]
		    robo_generation<-rob_topo_matrix[((l-1)*popsize+1):(l*popsize)]
		    similarity[l]<-mean(normal_generation==robo_generation)
		}

		dis_similarity<-c()
		disc_gens<-length(normal_dis_matrix)/popsize
		meanDiscreteGen <- c()
		for (k in 1:disc_gens){
			normal_dis_generation<-normal_dis_matrix[((k-1)*popsize+1):(k*popsize)]
			meanDiscreteGen[k]<-mean(sapply(normal_dis_generation, str_count, "1"))/10
		    robo_dis_generation<-rob_dis_matrix[((k-1)*popsize+1):(k*popsize)]
		    dis_similarity[k]<-mean(normal_dis_generation==robo_dis_generation)
		}
		setwd(curDir)
        pdf(paste(outputName, i, ".pdf", sep=""))
        plot(similarity, type="l",main = "Topology Robustness",xlab="Generations",ylab="Level of similarity", ylim=c(0,1))
        lines(dis_similarity,type="l",col="red")
    	lines(meanDiscreteGen, type='l', col='blue')
        legend("bottomright",c("Topology","Discrete"),lty=c(1,1),lwd=c(2.5,2.5),col=c("black","red"))
        dev.off()
	}
}


pdf_creation <- function(dirName) {
	fdirName <- dirName
	outputName <- dirName
	image_creation(fdirName,outputName)

	setwd(curDir)

	system(paste("pdftk ",dirName,"*.pdf cat output ",dirName, ".pdf",sep=""))
	system(paste("rm ",dirName,"*.png",sep=""))
}

curDir <- ("~/Dropbox/sxoli/ptixiaki/evo3")
n<-25

popsize<-1000
pdf_creation("1kneutral2")
pdf_creation("1kneutral5")
pdf_creation("1kselection2")
pdf_creation("1kselection5")
