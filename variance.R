generation_fitness=read.table("fitness.txt")

genotype_fit=read.table("genotype_fit.txt",fill=T)

vector_variance<-c()

for(i in 1:243){
variance<-unlist(genotype_fit[i,])
variance <- variance[!is.na(variance)]
vector_variance[i]<-var(variance)
}

print(generation_fitness[,4])

png(filename="variance.png")
 plot(vector_variance, type="l", main="Generations") 
 par(new=TRUE)
 plot(generation_fitness[,4],type="l",col="red")
dev.off()