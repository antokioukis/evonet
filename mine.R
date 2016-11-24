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

#number=as.integer(args[2])*as.integer(args[4])
#generations <- split(my_interaction_matrixes,rep(1:as.integer(args[3]),each=number))

count_NAs_generations<-function(x){
	range1=(x*10000)+1
	range2=(x*10000)+10000
	return (sum(is.na(my_interaction_matrixes[range1:range2,1:10])))
}

sink("countNa.txt")
for (i in 1:args[3]-1){
	print(count_NAs_generations(i))
}
sink()


	############apomonwmenoi komboi #########################################################
my_interaction_matrixes=as.data.frame(read.table(args[9]))

#an mia grammi exei 9 midenika tote exoume apomwnomeno kombo
sink("apomonwmenoi.txt")
for (i in 1:args[3]-1){
	range3=(i*10000)+1
	range4=(i*10000)+10000
	generation=my_interaction_matrixes[range3:range4,]
	apomonwmenoi=generation[rowSums(generation==0.0)==10,]
	print(dim(apomonwmenoi))
}
sink()

#an mia grammi exei 9 midenika tote exoume apomwnomeno kombo
sink("ri8mizomena.txt")
for (i in 1:args[3]-1){
	range3=(i*10000)+1
	range4=(i*10000)+10000
	generation=my_interaction_matrixes[range3:range4,]
	ri8mizomena=generation[rowSums(generation==0.0)<=1,]
	print(dim(ri8mizomena))
}
sink()

##################################################################################################
##check robustness

a<- read.table(args[7], colClasses=c("character"))
b <- read.table(args[8], colClasses=c("character"))


x <- 1:length(b[,1])

simVector <- sapply(x, function(i){
           mean(unlist(strsplit(a[i,], split="")) == unlist(strsplit(b[i,], split="")))
       })

simMatrix <- matrix(simVector, ncol=100, byrow=TRUE)

aveSimilarity <- apply(simMatrix, 1, mean)

sink(args[10])
aveSimilarity
sink()

###################################################################################################
###### create graph fitness + number of generations needed to 90%

anakata=read.table("/home/antonios/Dropbox/sxoli/ptixiaki/evo3/fitnessanakata.txt")
deka_assoi=read.table("/home/antonios/Dropbox/sxoli/ptixiaki/evo3/fitnessdekaassoi.txt")
deka_midenika=read.table("/home/antonios/Dropbox/sxoli/ptixiaki/evo3/fitnessmidenika.txt")
pente_assoi_pente_midenika=read.table("/home/antonios/Dropbox/sxoli/ptixiaki/evo3/fitnesspenteassoi.txt")

anakata <- anakata[-c(50:101), ]
deka_assoi <- deka_assoi[-c(50:101), ]
deka_midenika <- deka_midenika [-c(50:101), ]
pente_assoi_pente_midenika <- pente_assoi_pente_midenika [-c(50:501),]

anakata <- anakata[,-c(1, 2, 3) ]
deka_assoi <- deka_assoi[,-c(1, 2, 3) ]
deka_midenika <- deka_midenika [,-c(1, 2, 3) ]
pente_assoi_pente_midenika <- pente_assoi_pente_midenika [,-c(1, 2, 3) ]

png(filename="fitness_generations")

plot(deka_midenika,col="red",type="l",xlab="Generation Number",ylab="Generation Fitness")
lines(deka_assoi,col="blue",type="l",xlab="Generation Number",ylab="Generation Fitness")

lines(pente_assoi_pente_midenika,col="black",type="l",xlab="Generation Number",ylab="Generation Fitness")
lines(anakata,col="green",type="l",xlab="Generation Number",ylab="Generation Fitness")

legend('bottomright', legend=c("0000000000","1111100000","1010101010","1111111111") , lty=1, col=c('red', 'black', 'green','blue'), bty='n', cex=.75)

dev.off()

###################################################################################################