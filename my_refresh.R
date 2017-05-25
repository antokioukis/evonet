rm(list=ls())
library(foreach)
library(doMC)
registerDoMC(10)

system("make clean")
system("make all")

n <- 25
r <- 15000
N <- 500
rr <- 0.005
mr <- 5/N
s<- 5
sel <- 1
ploidy <- 1
freq<-1

curDir <- getwd()

randInt <- floor(runif(n, 0, 10000000))

write.table(randInt, file="seeds.txt", quote=F, row.names=F, col.names=F)
j=1
step=0.001
################################################################################################################################################
mr<-0.05
################################################################################################################################################
name<-"selection"
foreach(i = 1:n) %dopar% {
    seed <- randInt[i]
    dirName <- paste(name, ".run.", i, sep="")
    dir.create(file.path(curDir, dirName), showWarnings=FALSE)
    working_dir<-file.path(curDir, dirName)
    setwd(file.path(curDir, dirName))
    system(paste("Rscript ",curDir, "/write_file.R > ", working_dir,"/R1R2_input.txt",sep=""))
    cmd <- paste(curDir, "/evonet -selection ", sel," -key_genes 10 -st_geno R1R2_input.txt ", "-s2 ", s, " -N ", N, " -tarfit 1.0 "," -ploidy ", ploidy, "  -swapping 0 -freq ", freq, " -min_count 10 -max_count 11 -generations ",r ," -n 10 -recomb_rate ",rr ," -mutrate ",mr, " -seed ", seed, " -optimal_num 10", sep="")
    system(cmd)
}

sel<-0
name<-"neutral"
foreach(i = 1:n) %dopar% {
    seed <- randInt[i]
    dirName <- paste(name, ".run.", i, sep="")
    dir.create(file.path(curDir, dirName), showWarnings=FALSE)
    working_dir<-file.path(curDir, dirName)
    setwd(file.path(curDir, dirName))
    system(paste("Rscript ",curDir, "/write_file.R > ", working_dir,"/R1R2_input.txt",sep=""))
    cmd <- paste(curDir, "/evonet -selection ", sel," -key_genes 10 -st_geno R1R2_input.txt ", "-s2 ", s, " -N ", N, " -tarfit 1.0 "," -ploidy ", ploidy, "  -swapping 0 -freq ", freq, " -min_count 10 -max_count 11 -generations ",r ," -n 10 -recomb_rate ",rr ," -mutrate ",mr, " -seed ", seed, " -optimal_num 10", sep="")
    system(cmd)
}

system("Rscript maya.R")
system("Rscript means_equilibria.R")