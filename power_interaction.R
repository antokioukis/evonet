library(foreach)
library(doMC)
registerDoMC(10)

curDir <- ("~/Dropbox/sxoli/ptixiaki/evo3")

n<-25

foreach(i = 1:n) %dopar% {

	dirName <- paste(curDir,"/selection.run.", i, sep="")
	setwd(dirName)

	mydata<-read.table("matrix.txt")

	num_of_gens<-nrow(mydata)/500
	
	generation<-matrix(nrow=500,ncol=1)
	mean_power<-c()
	#gia ka8e genia
	for (l in 1:num_of_gens-1){
		katw_orio1<-((l-1)*500)+1
		panw_orio1<-l*500
		#print(katw_orio)
		#print(panw_orio)
		generation<-mydata[katw_orio1:panw_orio1,]
		#print(head(generation))
		#gia ka8e gonotupo autis tis genias
		mean_power[l]<-mean(as.matrix(generation))
	}

	#print(mean_power)

    setwd("~/Dropbox/sxoli/ptixiaki/evo3")
	png(paste("selection",sprintf("%04d", i),".png",sep=""))
    plot(mean_power, type="l",main = "Power of Interaction",xlab="Generations",ylab="Power")
    dev.off()
}

system("convert selection*.png selection_power_0.pdf")
system("rm selection*.png")


foreach(i = 1:n) %dopar% {

	dirName <- paste(curDir,"/neutral.run.", i, sep="")
	setwd(dirName)

	mydata<-read.table("matrix.txt")

	num_of_gens<-nrow(mydata)/500
	
	generation<-matrix(nrow=500,ncol=1)
	mean_power<-c()
	#gia ka8e genia
	for (l in 1:num_of_gens-1){
		katw_orio1<-((l-1)*500)+1
		panw_orio1<-l*500
		#print(katw_orio)
		#print(panw_orio)
		generation<-mydata[katw_orio1:panw_orio1,]
		#print(head(generation))
		#gia ka8e gonotupo autis tis genias
		mean_power[l]<-mean(as.matrix(generation))
	}

	#print(mean_power)

    setwd("~/Dropbox/sxoli/ptixiaki/evo3")
	png(paste("neutral",sprintf("%04d", i),".png",sep=""))
    plot(mean_power, type="l",main = "Power of Interaction",xlab="Generations",ylab="Power")
    dev.off()
}

system("convert neutral*.png neutral_power_0.pdf")
system("rm neutral*.png")

foreach(i = 1:n) %dopar% {

	dirName <- paste(curDir,"/selection.run.", i, sep="")
	setwd(dirName)

	mydata<-read.table("matrix.txt")

	num_of_gens<-nrow(mydata)/500
	
	generation<-matrix(nrow=500,ncol=1)
	mean_power<-c()
	#gia ka8e genia
	for (l in 1:num_of_gens-1){
		katw_orio1<-((l-1)*500)+1
		panw_orio1<-l*500
		#print(katw_orio)
		#print(panw_orio)
		generation<-mydata[katw_orio1:panw_orio1,]
		#print(head(generation))

		new<-generation[generation!=0]

		#gia ka8e gonotupo autis tis genias
		mean_power[l]<-mean(as.matrix(new))
	}

	#print(mean_power)

    setwd("~/Dropbox/sxoli/ptixiaki/evo3")
	png(paste("selection",sprintf("%04d", i),".png",sep=""))
    plot(mean_power, type="l",main = "Power of Interaction",xlab="Generations",ylab="Power")
    dev.off()
}

system("convert selection*.png selection_power_NA.pdf")
system("rm selection*.png")

foreach(i = 1:n) %dopar% {

	dirName <- paste(curDir,"/neutral.run.", i, sep="")
	setwd(dirName)

	mydata<-read.table("matrix.txt")

	num_of_gens<-nrow(mydata)/500
	
	generation<-matrix(nrow=500,ncol=1)
	mean_power<-c()
	#gia ka8e genia
	for (l in 1:num_of_gens-1){
		katw_orio1<-((l-1)*500)+1
		panw_orio1<-l*500
		#print(katw_orio)
		#print(panw_orio)
		generation<-mydata[katw_orio1:panw_orio1,]
		#print(head(generation))

		new<-generation[generation!=0]

		#gia ka8e gonotupo autis tis genias
		mean_power[l]<-mean(as.matrix(new))
	}

	#print(mean_power)

    setwd("~/Dropbox/sxoli/ptixiaki/evo3")
	png(paste("neutral",sprintf("%04d", i),".png",sep=""))
    plot(mean_power, type="l",main = "Power of Interaction",xlab="Generations",ylab="Power")
    dev.off()
}

system("convert neutral*.png neutral_power_NA.pdf")
system("rm neutral*.png")