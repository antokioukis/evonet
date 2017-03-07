curDir <- ("~/Dropbox/sxoli/ptixiaki/evo3")
#curDir <- getwd()
time_to_target_fitness<-c()
mut_rate<-c()
time_to_pavlos<-c()

counts=0
for (i in 1:1000){
	#print(i)
	dirName <- paste(curDir,"/selection.run.", i, sep="")
	#print(dirName)
	setwd(dirName)
	#print(mut_rate[i])
	#fitness_array<-read.table("fitnesss.txt")
	#pavlos_array<-read.table("generations.txt")

	#try catch epeidi ta perissotera einai adeia
	#an kapoio den einai adeio 8a tipwsei se poio einai gia na parw ta seed apo ekei gia na mporw na to kanw reproduce
	equilibrium_steps<-tryCatch(read.table("equilibrium_steps.txt"),error=function(e) NULL)
	equilibrium_period<-tryCatch(read.table("equilibrium_period.txt"),error=function(e) NULL)
	if (inherits(equilibrium_steps, 'try-error')) {print ("equilibrium") 
	counts = counts+1
	print (i) }
	if (inherits(equilibrium_period, 'try-error')) print ("equilibrium")

	#time_to_target_fitness[i]<-nrow(fitness_array)
	#time_to_pavlos[i]<-pavlos_array[1,1]
	#print(time_to_pavlos[i])
	#mut_rate[i]<-fitness_array[i,5]
}
counts
setwd(curDir)
#png(filename="fitness_mut2.png")
 #plot(mut_rate,time_to_target_fitness,xlab="mutation_rate",ylab="Time to target fitness",type="l", main="Generations",col="green") 
 #lines(mut_rate,time_to_pavlos,col="red")
#dev.off()
