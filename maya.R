curDir <- ("~/Dropbox/sxoli/ptixiaki/evo3")
n<-25

for (i in 1:n){

    x<-c()	
    time_to_target_fitness <- c()


    #print ("selection")
	dirName <- paste(curDir,"/selection.run.", i, sep="")
	setwd(dirName)
    

    fitness_array<-read.table("fitnesss.txt")
    orio_vector<-nrow(fitness_array)
    #print(orio_vector)
    for (k in 1:orio_vector){
        x[k]<-0
    }

    equilibrium <-read.table("equilibrium_period.txt")

    for (j in 1:nrow(equilibrium)){
    	thesi<-equilibrium[j,]
    	x[thesi]<-x[thesi]+1
    }

    scaler<-max(x)
    fitness_vec<-fitness_array[,4]
    fitness_vec<-100*fitness_vec


#    temp_plot<-1:orio_vector
#    positions<-barplot(x) 
#    mid <- x/2 
    
    setwd("~/Dropbox/sxoli/ptixiaki/evo3")
    png(file=paste(sprintf("%04d", i),".png",sep=""))
    m<-barplot(x, main = "barplot",xlab="Generations",ylab="Frequency of Equilibria")

    xlims <- par('usr')[1:2] # <-- get xlims
    par(new=T)

    lines(m,fitness_vec,col="red",lwd=3,xlim=xlims,yaxt="n")
    axis(side = 4,col="red",col.ticks="red",at=0:105,lwd.ticks=10)
    mtext(side = 4, line = 3, 'Fitness')

    dev.off()    
 
}
#print(getwd())
system("convert 00*.png selection_equilibria.pdf")
system("rm 00*.png")

curDir <- ("~/Dropbox/sxoli/ptixiaki/evo3")

for (i in 1:n){

    x<-c()  
    time_to_target_fitness <- c()

    
    dirName <- paste(curDir,"/neutral.run.", i, sep="")
    setwd(dirName)
        
    fitness_array<-read.table("fitnesss.txt")
    orio_vector<-nrow(fitness_array)
    #print(orio_vector)
    for (k in 1:orio_vector){
        x[k]<-0
    }
    #print(tail(fitness_array))
    equilibrium <-read.table("equilibrium_period.txt")

    for (j in 1:nrow(equilibrium)){
        thesi<-equilibrium[j,]
        x[thesi]<-x[thesi]+1
    }

    scaler<-max(x)
    fitness_vec<-fitness_array[,4]
    fitness_vec<-100*fitness_vec


#    temp_plot<-1:orio_vector
#    positions<-barplot(x) 
#    mid <- x/2 
    
    setwd("~/Dropbox/sxoli/ptixiaki/evo3")
    png(file=paste(sprintf("%04d", i),".png",sep=""))
    m<-barplot(x, main = "barplot",xlab="Generations",ylab="Frequency of Equilibria")

    xlims <- par('usr')[1:2] # <-- get xlims
    par(new=T)

    lines(m,fitness_vec,col="red",lwd=3,xlim=xlims,yaxt="n")
    axis(side = 4,col="red",col.ticks="red",at=0:105,lwd.ticks=10)
    mtext(side = 4, line = 3, 'Fitness')

    dev.off()    
}  

#print(getwd())
system("convert 00*.png neutral_equilibria.pdf")
system("rm 00*.png")