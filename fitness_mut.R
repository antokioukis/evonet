curDir <- ("~/Dropbox/sxoli/ptixiaki/evo3")
#curDir <- getwd()
time_to_target_fitness3<-c()
time_to_target_fitness5<-c()
time_to_target_fitness10<-c()

mut_rate<-c()
time_to_pavlos<-c()
time_to_finish<-c()
n<-1
sum<-0
counts=0
for (i in 1:n){
	dirName <- paste(curDir,"/selection5.run.", i, sep="")
	setwd(dirName)
	fitness_array<-read.table("fitnesss.txt")
	pavlos_array<-read.table("generations.txt")
	#time_array<-read.table("time_Output.txt")

	#try catch epeidi ta perissotera einai adeia
	#an kapoio den einai adeio 8a tipwsei se poio einai gia na parw ta seed apo ekei gia na mporw na to kanw reproduce
	#equilibrium_steps<-tryCatch(read.table("equilibrium_steps.txt"),error=function(e) NULL)
	#equilibrium_period<-tryCatch(read.table("equilibrium_period.txt"),error=function(e) NULL)
	#if (inherits(equilibrium_steps, 'try-error')) {print ("equilibrium") 
	#counts = counts+1
	#print (i) }
	#if (inherits(equilibrium_period, 'try-error')) print ("equilibrium")

	time_to_target_fitness5[i]<-nrow(fitness_array)
	#time_to_pavlos[i]<-pavlos_array[1,1]
	#print(time_to_pavlos[i])
	mut_rate[i]<-fitness_array[1,5]
	#sum<-time_array+sum
}

for (i in 1:n){
	dirName <- paste(curDir,"/selection10.run.", i, sep="")
	setwd(dirName)
	fitness_array<-read.table("fitnesss.txt")
	time_to_target_fitness10[i]<-nrow(fitness_array)
}

for (i in 1:n){
	dirName <- paste(curDir,"/selection3.run.", i, sep="")
	setwd(dirName)
	fitness_array<-read.table("fitnesss.txt")
	time_to_target_fitness10[i]<-nrow(fitness_array)
}


#counts
#print(sum/300)
png(filename="fitness_mut.png")
 plot(mut_rate,time_to_target_fitness5,xlab="mutation_rate",ylab="Time to target fitness",type="p", main="Generations",col="red") 
 lines(mut_rate,time_to_target_fitness10,col="blue")
 lines(mut_rate,time_to_target_fitness3,col="black")
dev.off()
