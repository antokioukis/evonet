library(stringr)
write_dir <- "/home/pavlos/synology/kioukis/evo4/"
curDir <- paste("/home/pavlos/synology/kioukis/evo4/500selection1.run.",sep="")
for (i in 1:100){
	print(i)
    popsize<-500
    similarity<-c()
	dis_similarity<-c()

	#dirName <- fdirName
	dirName <- paste(curDir, i, sep="")
	 
	setwd(dirName)

	normal_topo<-read.table("matrix.txt")
	rob_topo<-read.table("robustness.txt")

	normal_discrete<-read.table("discrete.txt")
	rob_discrete<-read.table("rob_discrete.txt")

	normal_topo_matrix<-matrix(nrow=nrow(normal_topo),ncol=1)
	rob_topo_matrix<-matrix(nrow=nrow(rob_topo),ncol=1)

	normal_dis_matrix<-matrix(nrow=nrow(normal_discrete),ncol=1)
	rob_dis_matrix<-matrix(nrow=nrow(rob_discrete),ncol=1)

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
	setwd(write_dir)
	write(similarity, file="topo_sim.tab", ncolumns=num_of_gens, append = TRUE, sep = "\t")

	dis_similarity<-c()
	disc_gens<-length(normal_dis_matrix)/popsize
	meanDiscreteGen <- c()
	for (k in 1:disc_gens){
		normal_dis_generation<-normal_dis_matrix[((k-1)*popsize+1):(k*popsize)]
		meanDiscreteGen[k]<-mean(sapply(normal_dis_generation, str_count, "1"))/10
	    robo_dis_generation<-rob_dis_matrix[((k-1)*popsize+1):(k*popsize)]
	    dis_similarity[k]<-mean(normal_dis_generation==robo_dis_generation)
	}
	setwd(write_dir)
	write(dis_similarity, file="discrete_sim.tab", ncolumns=disc_gens, append = TRUE, sep = "\t")

}

curDir <- paste("/home/pavlos/synology/kioukis/evo4/robustness_3k_bonus/500selection1.run.",sep="")
max_fitness_row <- 0
for (i in 1:100){
	print(i)
	dirName <- paste(curDir, i, sep="") 
	setwd(dirName)
	fitness<-read.table("fitnesss.txt")
	if(nrow(fitness) > max_fitness_row){
		max_fitness_row <- nrow(fitness)
	}
}

fitness_mat <- matrix(nrow=100, ncol=max_fitness_row)
for (i in 1:100){
	print(i)
	dirName <- paste(curDir, i, sep="") 
	setwd(dirName)
	fitness<-read.table("fitnesss.txt")
	for(j in 1:max_fitness_row){
		mikos_fitness = nrow(fitness)
		if(j <= mikos_fitness){
			fitness_mat[i,j] = fitness[j,4]
		}
		else{
			fitness_mat[i,j] = 1
		}
	}
}

curDir <- paste("/home/pavlos/synology/kioukis/evo4/robustness_3k_bonus/",sep="")
setwd(curDir)
write.table(fitness_mat,file="fitness_matrix.tab",sep="\t", rownames=FALSE, colnames=FALSE)


fitness_mean<-colMeans(fitness_mat)



similarity<-scan("similarity.txt", character(), quote = "")
dis_similarity<-scan("dis_similarity.txt", character(), quote = "")

df_sim<-as.data.frame(similarity)
df_sim$ID <- seq.int(length(similarity))
df_sim$dis<-as.vector(dis_similarity)
df_sim$fit<-as.factor(fitness_mean)

library(ggplot2)
library(RColorBrewer)
values = brewer.pal(n = 3, name = "Dark2")

g1<-ggplot()+
    geom_point(data=df_sim, aes(x=df_sim$ID,y=df_sim$similarity,colour=values[1]))+
    geom_point(data=df_sim, aes(x=df_sim$ID,y=df_sim$dis,colour=values[2]))	+
    geom_point(data=df_sim, aes(x=df_sim$ID,y=df_sim$fit,colour=values[3]))+
    #scale_color_discrete(name = "Robustness Levels", labels = c("Topology", "Fitness","Discrete"))
	scale_color_discrete(name = "Robustness Levels", labels = c("Topology","Fitness","Phenotype"))

g4 <- g1 +  theme_bw() +
  theme(axis.line = element_line(),
        axis.ticks.y = element_blank(),        ## <- this line
        axis.text.y = element_blank(),         ## <- and this line
        panel.grid.major = element_blank(),
        panel.grid.minor = element_blank(),
        panel.background = element_blank(),
        panel.border = element_blank()) 



g5<-g4+xlab("Generations") + ylab("Similarity - Fitness")


plot(g5)

setwd("/home/kioukis/")
ggsave("robust-fit.pdf")
