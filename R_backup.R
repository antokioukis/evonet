#####################################################################################
#initialization
#!/usr/bin/env Rscript


install.packages("stringdist")
args = commandArgs(trailingOnly=TRUE)

if (length(args)==0) {
  stop("At least one argument must be supplied (input file).n", call.=FALSE)
}

#####################################################################################
#fitness images export

my_fitness=read.table(args[6])

fitness_of_generation<-as.vector(unlist(my_fitness[4]))
num_of_generation<-as.vector(as.numeric(unlist(my_fitness[1])))

png(filename=args[1])
plot(num_of_generation,fitness_of_generation,main= args[5] ,type="l",xlab="Generation Number",ylab="Generation Fitness")

#####################################################################################
#matrix interaction export

#####################################################################################
###R1-R2

setwd("~/Dropbox/sxoli/ptixiaki/evo3")
my_R1=read.table("R1.txt")
my_R2=read.table("R2.txt")

mean(hamming.distance(my_R1 & my_R2))

#split ana generation
generation_R2 <- split(my_R2,rep(1:6,each=10*1000))
generation_R1 <- split(my_R1,rep(1:6,each=10*1000))

mesoi_oroi_R1<-c(1:args[4])
for(i in 1:args[4]){
  mesoi_oroi_R1[i]<-mean(unlist(generation_R1[[i]]))
}

mesoi_oroi_R2<-c(1:args[4])
for(i in 1:args[4]){
  mesoi_oroi_R2[i]<-mean(unlist(generation_R2[[i]]))
} 


png(filename=args[2])
plot(num_of_generation,mesoi_oroi,main="R1",type="l",xlab="Generation Number",ylab="mean R1")
dev.off()

##################################################################################################
##check robustness