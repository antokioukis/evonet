#fitness images export
setwd("~/Dropbox/Sxoli/ptixiaki/evo3/")

my_fitness=read.table("fitness.txt")

fitness_of_generation<-as.vector(unlist(my_fitness[4]))
num_of_generation<-as.vector(as.numeric(unlist(my_fitness[1])))

png(filename="~/Dropbox/Sxoli/ptixiaki/evo3/fit10.png")
plot(num_of_generation,fitness_of_generation,main="s^2 = 10",type="l",xlab="Generation Number",ylab="Generation Fitness")
dev.off()

#matrix interaction export

interaction_matrixes=read.table("newMatrix.txt")

dim(interaction_matrixes)


##interaction_matrixes[interaction_matrixes == 0] <- NA
auxMatrix <- interaction_matrixes; #[interaction_matrixes == 0] <- NA
auxMatrix[auxMatrix == 0] <- NA

auxMatrix[[21000]]

atomo <- split(interaction_matrixes,rep(1:21000,each=10))
auxAtomo <- split(auxMatrix,rep(1:21000,each=10))

findNAs <- function(element){
    apply(element, 2, function(x){ sum(is.na(x))})
}

length(atomo)
for(i in 1:1000){
  kenes_stiles[i]<-sum(is.na.data.frame(atomo[i]))/10
  sum<-0
}

png(filename="~/Dropbox/Sxoli/ptixiaki/evo3/non_interaction.png")
hist(kenes_stiles,main="Non Interacting Genes",xlab="Number of non interacting Genes",ylab="Number of Individuals")

dev.off()
