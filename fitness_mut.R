curDir <- getwd()
time_to_target_fitness<-c()
mut_rate<-c()

for (i in 1:2){
	dirName <- paste(curDir,"/selection.run.", i, sep="")
	setwd(dirName)
	print(mut_rate[i])
	fitness_array<-read.table("fitness.txt")
	time_to_target_fitness[i]<-nrow(fitness_array)
	mut_rate[i]<-fitness_array[i,5]
}

setwd(curDir)
png(filename="fitness_mut.png")
 plot(mut_rate,time_to_target_fitness,xlab="mutation_rate",ylab="Time to target fitness",type="l", main="Generations") 
dev.off()