n<-50

mean_free_1<-c()
mean_free_3<-c()
mean_free_5<-c()
mean_free_7<-c()

curDir <- ("~/Dropbox/sxoli/ptixiaki/evo3/")

for (i in 1:n){
	dirName <- paste(curDir,"/free1mr005perc001.run.", i, sep="")					
	setwd(dirName)
	fitness_array<-read.table("fitnesss.txt")
	mean_free_1[i]<-nrow(fitness_array)
}

for (i in 1:n){
	dirName <- paste(curDir,"/free3mr005perc001.run.", i, sep="")
	setwd(dirName)
	fitness_array<-read.table("fitnesss.txt")
	mean_free_3[i]<-nrow(fitness_array)
}

for (i in 1:n){
	dirName <- paste(curDir,"/free5mr005perc001.run.", i, sep="")
	setwd(dirName)
	fitness_array<-read.table("fitnesss.txt")
	mean_free_5[i]<-nrow(fitness_array)
}

for (i in 1:n){
	dirName <- paste(curDir,"/free7mr005perc001.run.", i, sep="")
	setwd(dirName)
	fitness_array<-read.table("fitnesss.txt")
	mean_free_7[i]<-nrow(fitness_array)
}

print("mr=005")
print(mean(mean_free_1))
print(mean(mean_free_3))
print(mean(mean_free_5))
print(mean(mean_free_7))


mean_free_1<-c()
mean_free_3<-c()
mean_free_5<-c()
mean_free_7<-c()

for (i in 1:n){
	dirName <- paste(curDir,"/free1mr01perc001.run.", i, sep="")
	setwd(dirName)
	fitness_array<-read.table("fitnesss.txt")
	mean_free_1[i]<-nrow(fitness_array)
}

for (i in 1:n){
	dirName <- paste(curDir,"/free3mr01perc001.run.", i, sep="")
	setwd(dirName)
	fitness_array<-read.table("fitnesss.txt")
	mean_free_3[i]<-nrow(fitness_array)
}

for (i in 1:n){
	dirName <- paste(curDir,"/free5mr01perc001.run.", i, sep="")
	setwd(dirName)
	fitness_array<-read.table("fitnesss.txt")
	mean_free_5[i]<-nrow(fitness_array)
}

for (i in 1:n){
	dirName <- paste(curDir,"/free7mr01perc001.run.", i, sep="")
	setwd(dirName)
	fitness_array<-read.table("fitnesss.txt")
	mean_free_7[i]<-nrow(fitness_array)
}

print("mr=01")
print(mean(mean_free_1))
print(mean(mean_free_3))
print(mean(mean_free_5))
print(mean(mean_free_7))


mean_free_1<-c()
mean_free_3<-c()
mean_free_5<-c()
mean_free_7<-c()

for (i in 1:n){
	dirName <- paste(curDir,"/free1mr015perc001.run.", i, sep="")
	setwd(dirName)
	fitness_array<-read.table("fitnesss.txt")
	mean_free_1[i]<-nrow(fitness_array)
}

for (i in 1:n){
	dirName <- paste(curDir,"/free3mr015perc001.run.", i, sep="")
	setwd(dirName)
	fitness_array<-read.table("fitnesss.txt")
	mean_free_3[i]<-nrow(fitness_array)
}

for (i in 1:n){
	dirName <- paste(curDir,"/free5mr015perc001.run.", i, sep="")
	setwd(dirName)
	fitness_array<-read.table("fitnesss.txt")
	mean_free_5[i]<-nrow(fitness_array)
}

for (i in 1:n){
	dirName <- paste(curDir,"/free7mr015perc001.run.", i, sep="")
	setwd(dirName)
	fitness_array<-read.table("fitnesss.txt")
	mean_free_7[i]<-nrow(fitness_array)
}

print("mr=015")
print(mean(mean_free_1))
print(mean(mean_free_3))
print(mean(mean_free_5))
print(mean(mean_free_7))

mean_free_1<-c()
mean_free_3<-c()
mean_free_5<-c()
mean_free_7<-c()

for (i in 1:n){
	dirName <- paste(curDir,"/free1mr02perc001.run.", i, sep="")
	setwd(dirName)
	fitness_array<-read.table("fitnesss.txt")
	mean_free_1[i]<-nrow(fitness_array)
}

for (i in 1:n){
	dirName <- paste(curDir,"/free3mr02perc001.run.", i, sep="")
	setwd(dirName)
	fitness_array<-read.table("fitnesss.txt")
	mean_free_3[i]<-nrow(fitness_array)
}

for (i in 1:n){
	dirName <- paste(curDir,"/free5mr02perc001.run.", i, sep="")
	setwd(dirName)
	fitness_array<-read.table("fitnesss.txt")
	mean_free_5[i]<-nrow(fitness_array)
}

for (i in 1:n){
	dirName <- paste(curDir,"/free7mr02perc001.run.", i, sep="")
	setwd(dirName)
	fitness_array<-read.table("fitnesss.txt")
	mean_free_7[i]<-nrow(fitness_array)
}

print("mr=02")
print(mean(mean_free_1))
print(mean(mean_free_3))
print(mean(mean_free_5))
print(mean(mean_free_7))
