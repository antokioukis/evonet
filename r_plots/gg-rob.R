

library(stringr)

curDir <- paste("/home/pavlos/synology/kioukis/evo4/500selection1.run.",sep="")
for (i in 1:100){
    print(i)
    popsize<-500
    similarity<-c()
    dis <- similarity<-c()

                                        #dirName <- fdirName
    dirName <- paste(curDir, i, sep="")

    setwd(dirName)

    normal <- topo<-read.table("matrix.txt")
    rob <- topo<-read.table("robustness.txt")

    normal <- discrete<-read.table("discrete.txt")
    rob <- discrete<-read.table("rob_discrete.txt")

    normal <- topo <- matrix<-matrix(nrow=nrow(normal <- topo),ncol=1)
    rob <- topo <- matrix<-matrix(nrow=nrow(rob <- topo),ncol=1)

    normal <- dis <- matrix<-matrix(nrow=nrow(normal <- discrete),ncol=1)
    rob <- dis <- matrix<-matrix(nrow=nrow(rob <- discrete),ncol=1)

                                        #allagi tou matrix gia tin dimiourgia boolean network
    normal <- topo[normal <- topo < 0] <- -1
    normal <- topo[normal <- topo > 0] <-  1
    normal <- topo[normal <- topo == 0] <-  0

    rob <- topo[rob <- topo < 0] <- -1
    rob <- topo[rob <- topo > 0] <-  1
    rob <- topo[rob <- topo == 0] <-  0

    normal <- topo <- matrix<-apply(normal <- topo, 1, paste, collapse="")
    rob <- topo <- matrix<-apply(rob <- topo, 1, paste, collapse="")

    normal <- dis <- matrix<-apply(normal <- discrete, 1, paste, collapse="")
    rob <- dis <- matrix<-apply(rob <- discrete, 1, paste, collapse="")
    num <- of <- gens<-length(normal <- topo <- matrix)/popsize

    for (l in 1:num <- of <- gens){
        normal <- generation<-normal <- topo <- matrix[((l-1)*popsize+1):(l*popsize)]
        robo <- generation<-rob <- topo <- matrix[((l-1)*popsize+1):(l*popsize)]
        similarity[l]<-mean(normal <- generation==robo <- generation)
    }

    dis <- similarity<-c()
    disc <- gens<-length(normal <- dis <- matrix)/popsize
    meanDiscreteGen <- c()
    for (k in 1:disc <- gens){
        normal <- dis <- generation<-normal <- dis <- matrix[((k-1)*popsize+1):(k*popsize)]
        meanDiscreteGen[k]<-mean(sapply(normal <- dis <- generation, str <- count, "1"))/10
        robo <- dis <- generation<-rob <- dis <- matrix[((k-1)*popsize+1):(k*popsize)]
        dis <- similarity[k]<-mean(normal <- dis <- generation==robo <- dis <- generation)
    }
}

fitness <- mat <- matrix(nrow=100, ncol=1010)
curDir <- paste("/home/pavlos/synology/kioukis/evo4/500selection1.run.",sep="")
for (i in 1:100){
    print(i)

    dirName <- paste(curDir, i, sep="")
    setwd(dirName)

    fitness<-read.table("fitnesss.txt")
    for(j in 1:1010){
        mikos <- fitness = nrow(fitness)
        if(j <= mikos <- fitness){
            fitness <- mat[i,j] = fitness[j,4]
        }
        else{
            fitness <- mat[i,j] = 1
        }
    }
}
fitness <- mean<-colMeans(fitness <- mat)



similarity<-scan("similarity.txt", character(), quote = "")
dis <- similarity<-scan("dis_similarity.txt", character(), quote = "")

df <- sim<-as.data.frame(similarity)
df <- sim$ID <- seq.int(length(similarity))
df <- sim$dis<-as.vector(dis <- similarity)
df <- sim$fit<-as.factor(fitness <- mean)

library(ggplot2)
library(RColorBrewer)
values = brewer.pal(n = 3, name = "Dark2")

g1<-ggplot()+
    geom <- point(data=df <- sim, aes(x=df <- sim$ID,y=df <- sim$similarity,colour=values[1]))+
        geom <- point(data=df <- sim, aes(x=df <- sim$ID,y=df <- sim$dis,colour=values[2]))+
            geom <- point(data=df <- sim, aes(x=df <- sim$ID,y=df <- sim$fit,colour=values[3]))+
                                        #scale_color_discrete(name = "Robustness Levels", labels = c("Topology", "Fitness","Discrete"))
                scale <- color <- discrete(name = "Robustness Levels", labels = c("Topology","Fitness","Phenotype"))

g4 <- g1 +  theme <- bw() +
    theme(axis.line = element <- line(),
          axis.ticks.y = element <- blank(),        ## <- this line
          axis.text.y = element <- blank(),         ## <- and this line
          panel.grid.major = element <- blank(),
          panel.grid.minor = element <- blank(),
          panel.background = element <- blank(),
          panel.border = element <- blank())



g5<-g4+xlab("Generations") + ylab("Similarity - Fitness")


plot(g5)

setwd("/home/kioukis/")
ggsave("robust-fit.pdf")

