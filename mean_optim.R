n<-100

open_generation_genes1<-c()
open_generation_genes2<-c()
open_generation_genes3<-c()
open_generation_genes4<-c()

curDir <- ("~/Dropbox/sxoli/ptixiaki/evo3/")

for (i in 1:n){
	dirName <- paste(curDir,"/kanonikoi_megalo.run.", i, sep="")					
	setwd(dirName)
	fitness_array<-read.table("fitnesss.txt")
	#mean_free_1[i]<-nrow(fitness_array)
	open_genes_array<-read.table("open_genes.txt")
	open_generation_genes1[i]<-mean(rowMeans (open_genes_array, na.rm = FALSE, dims = 1))

}

for (i in 1:n){
	dirName <- paste(curDir,"/kanonikoi_mikro.run.", i, sep="")
	setwd(dirName)
	fitness_array<-read.table("fitnesss.txt")
	#mean_free_3[i]<-nrow(fitness_array)
	open_genes_array<-read.table("open_genes.txt")
	open_generation_genes2[i]<-mean(rowMeans (open_genes_array, na.rm = FALSE, dims = 1))
}

curDir <- ("~/Dropbox/sxoli/ptixiaki/evo4/")


for (i in 1:n){
	dirName <- paste(curDir,"/misoi_megalo.run.", i, sep="")					
	setwd(dirName)
	fitness_array<-read.table("fitnesss.txt")
	#mean_free_1[i]<-nrow(fitness_array)
	open_genes_array<-read.table("open_genes.txt")
	open_generation_genes3[i]<-mean(rowMeans (open_genes_array, na.rm = FALSE, dims = 1))

}

for (i in 1:n){
	dirName <- paste(curDir,"/misoi_mikro.run.", i, sep="")
	setwd(dirName)
	fitness_array<-read.table("fitnesss.txt")
	#mean_free_3[i]<-nrow(fitness_array)
	open_genes_array<-read.table("open_genes.txt")
	open_generation_genes4[i]<-mean(rowMeans (open_genes_array, na.rm = FALSE, dims = 1))
}

print(mean(open_generation_genes1))
print(mean(open_generation_genes2))
print(mean(open_generation_genes3))
print(mean(open_generation_genes4))