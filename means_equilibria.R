library(foreach)
library(doMC)
registerDoMC(10)


curDir <- ("~/Dropbox/sxoli/ptixiaki/evo3")
n<-25
meta_vec_pval<-c()
prin_vec_pval<-c()

foreach(i = 1:n) %dopar% {
    x<-c()

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

    maximum_fitness=max(fitness_vec)
    temp<-which(maximum_fitness==fitness_vec)
    first_occ<-temp[1]
    #print(first_occ)

    my_fitness<-fitness_vec[first_occ:length(fitness_vec)]
    my_x<-x[first_occ:length(x)]
    meta_vec_pval[i]<-cor.test(my_fitness,my_x)$p.value

    my_fitness<-fitness_vec[1:first_occ]
    my_x<-x[1:first_occ]
    prin_vec_pval[i]<-cor.test(my_fitness,my_x)$p.value
}

print("Selection")
print("P-value correlation prin apo reach of optimum")
print(mean(prin_vec_pval))
print("P-value correlation meta apo reach of optimum")
print(mean(meta_vec_pval))


foreach(i = 1:n) %dopar% {

    x<-c()

    #print ("selection")
    dirName <- paste(curDir,"/neutral.run.", i, sep="")
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

    meta_vec_pval[i]<-cor.test(fitness_vec,x)$p.value

 
}
print("Neutral")
print("P-value correlation")
print(mean(meta_vec_pval))