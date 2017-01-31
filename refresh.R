rm(list=ls())
library(foreach)
library(doMC)
registerDoMC(10)

system("make clean")
system("make all")

n <- 10
r <- 8001
N <- 200
rr <- 0.005
mr <- 0.005
s<- 2
sel <- 1
ploidy <- 1

modechange <- 7000
newfreq <- 1
modechangePhrase <- ""

if( sel == 0){
    name <- "neutral"
}else{
    name <- "selection"
}

if( modechange != 0){
    if(sel == 1){
        sel <- 0
    }else{
        sel <- 1
    }
    modechangePhrase <- paste(" -mod_change ", modechange, " ", newfreq, " ", sep="")
}

curDir <- getwd()

randInt <- floor(runif(n, 0, 10000000))

write.table(randInt, file="seeds.txt", quote=F, row.names=F, col.names=F)

foreach(i = 1:n) %dopar% {
    seed <- randInt[i]
    print(seed)
    dirName <- paste(name, ".run.", i, sep="")
    dir.create(file.path(curDir, dirName), showWarnings=FALSE)
    setwd(file.path(curDir, dirName))
    cmd <- paste(curDir, "/evonet -selection ", sel, " ", modechangePhrase, " -s2 ", s, " -N ", N, " -ploidy ", ploidy, "  -swapping 0 -freq ", 200, " -min_R1R2 10 -max_R1R2 10 -min_count 10 -max_count 11 -generations ",r ," -n 10 -recomb_rate ",rr ," -mutrate ",mr, " -seed ", seed, sep="")
    system(cmd)
}

#system(paste("Rscript countMut.R ", n,sep=""))
system("Rscript test.R")
