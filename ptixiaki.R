#####################################################################################
#initialization
#!/usr/bin/env Rscript
args = commandArgs(trailingOnly=TRUE)

if (length(args)==0) {
  stop("At least one argument must be supplied (input file).n", call.=FALSE)
}

#####################################################################################
#fitness images export
setwd("~/Dropbox/Sxoli/ptixiaki/evo3/")

my_fitness=read.table(args[6])

fitness_of_generation<-as.vector(unlist(my_fitness[4]))
num_of_generation<-as.vector(as.numeric(unlist(my_fitness[1])))

png(filename=args[1])
plot(num_of_generation,fitness_of_generation,main= args[5] ,type="l",xlab="Generation Number",ylab="Generation Fitness")

#####################################################################################
#matrix interaction export

interaction_matrixes=read.table(args[7])

interaction_matrixes[interaction_matrixes == 0] <- NA

atomo <- split(interaction_matrixes,rep(1:(as.numeric(args[3])*as.numeric(args[4])),each=10))

findNAs <- function(element){
  apply(element, 2, function(x){ sum(is.na(x))})
}

kenes_stiles<-lapply(atomo,findNAs)

#####################################################################################
###R1R2

my_R1R2=read.table(args[8])

#split ana generation
generation_R1R2 <- split(my_R1R2,rep(1:args[4],each=10*as.numeric(args[3])))

mesoi_oroi<-c(1:args[4])
for(i in 1:args[4]){
  mesoi_oroi[i]<-mean(unlist(generation_R1R2[[i]]))
} 

png(filename=args[2])
plot(num_of_generation,mesoi_oroi,main="R1R2",type="l",xlab="Generation Number",ylab="mean R1R2")
dev.off()


