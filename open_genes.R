curDir <- ("~/Dropbox/sxoli/ptixiaki/evo3")
n<-1

dirName <- paste(curDir,"/selection.run.", n, sep="")
setwd(dirName)
open_genes_array<-read.table("open_genes.txt")
fitness_array<-read.table("fitnesss.txt")

open_generation_genes<-rowMeans (open_genes_array, na.rm = FALSE, dims = 1)


png(filename="open_genes3.png")
	plot(fitness_array[,4],open_generation_genes,xlab="Generation_Fitness",ylab="open_genes",type="p", main="Generations",col="red")
	#lines(fitness_array5[,4],open_generation_genes5,type="p",col="blue")
	#lines(fitness_array10[,4],open_generation_genes10,type="p",col="black") 
dev.off()