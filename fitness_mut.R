curDir <- ("~/evonet")
#curDir <- getwd()
time_to_target_fitness<-c()
mut_rate<-c()
time_to_pavlos<-c()

for (i in 1:100){
	#print(i)
	dirName <- paste(curDir,"/selection.run.", i, sep="")
	#print(dirName)
	setwd(dirName)
	#print(mut_rate[i])
	fitness_array<-read.table("fitnesss.txt")
	pavlos_array<-read.table("generations.txt")
	time_to_target_fitness[i]<-nrow(fitness_array)
	time_to_pavlos[i]<-pavlos_array[1,1]
	#print(time_to_pavlos[i])
	mut_rate[i]<-fitness_array[i,5]
}

setwd(curDir)
png(filename="fitness_mut2.png")
 plot(mut_rate,time_to_target_fitness,xlab="mutation_rate",ylab="Time to target fitness",type="l", main="Generations",col="green") 
 lines(mut_rate,time_to_pavlos,col="red")
dev.off()
