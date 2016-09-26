#####################################################################################
#initialization
#!/usr/bin/env Rscript
args = commandArgs(trailingOnly=TRUE)

#####################################################################################
#fitness image export


my_fitness=read.table(args[6])

fitness_of_generation<-as.vector(unlist(my_fitness[4]))
num_of_generation<-(1:args[3]-1)

png(filename=args[1])
plot(num_of_generation*as.numeric(args[4]),fitness_of_generation,main= args[3] ,type="l",xlab="Generation Number",ylab="Generation Fitness")

##################################################################################################
#interaction matrixes
number=0
my_interaction_matrixes=as.data.frame(read.table(args[9]))

my_interaction_matrixes[my_interaction_matrixes == 0.0] <- NA

number=as.integer(args[2])*as.integer(args[4])

generations <- split(my_interaction_matrixes,rep(1:as.integer(args[3]),each=number))

atomo<- my_interaction_matrixes[1:10,1:10]
atomo[,1:10]

atomo<- my_interaction_matrixes[11:20,1:10]
atomo[,1:10]

##################################################################################################
##check robustness

a<- read.table(args[7], colClasses=c("character"))
b <- read.table(args[8], colClasses=c("character"))


x <- 1:length(b[,1])

simVector <- sapply(x, function(i){
           mean(unlist(strsplit(a[i,], split="")) == unlist(strsplit(b[i,], split="")))
       })

simMatrix <- matrix(simVector, ncol=1000, byrow=TRUE)

aveSimilarity <- apply(simMatrix, 1, mean)

sink(args[10])
aveSimilarity
sink()

