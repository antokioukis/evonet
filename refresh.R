rm(list=ls())
library(foreach)
library(doMC)
registerDoMC(8)

execname = "evonet"
if(Sys.info()["nodename"] == "Maya"){
    execname = "evonetmaya"
}

#system("make clean")
#system("make all")
##system("gcc fitnessSimple.c -O3 -lm -lgsl -lgslcblas -o fitnessSimple") ## the -O3 flag will add some optimizations

rootFolderName = "neutral"
n <- 8
r <- 30000
N <- 500
rr <- 0.005
mr<- 5/N
s<-5
sel <- 1

ploidy <- 1
freq<-30

modechange <- 0
newfreq <- 1
modechangePhrase <- ""


if( modechange != 0){
   if(sel == 1){
       sel <- 0
   }else{
       sel <- 1
   }
   modechangePhrase <- paste(" -mod_change ", modechange, " ", newfreq, " ", sep="")
}else{
    modechangePhrase<-""
}


if( sel == 0){
    name <- "neutral"
}else{
    name <- "selection"
    rootFolderName = name
}

curDir <- getwd()
randInt <- floor(runif(n, 0, 10000000))

dir.create(file.path(curDir, rootFolderName), showWarnings=F)
setwd(file.path(curDir, rootFolderName))
print(getwd())

write.table(randInt, file="seeds", quote=F, row.names=F, col.names=F)

outDirs = array("", n)

outDirs = foreach(i = 1:n) %dopar% {
    setwd(file.path(curDir, rootFolderName))
    seed <- randInt[i]
    dirName <- paste("run", i, sep="")
    working_dir<-file.path(paste(curDir, "/", rootFolderName, sep=""), dirName)
    dir.create(working_dir, showWarnings=FALSE)
    setwd(working_dir)
    system(paste("Rscript ",curDir, "/write_file.R > ", working_dir,"/R1R2_input.txt",sep=""))
    cmd <- paste(curDir, "/", execname, " ", modechangePhrase, " -selection ", sel," -s2 ", s, " -N ", N, " -tarfit 1.0 -ploidy ", ploidy, "  -swapping 0 -freq ", freq, " -min_count 0 -max_count 10 -generations ",r ," -n 10 -recomb_rate ",rr ," -mutrate ",mr, " -seed ", seed, " -optimal_vec 1111111111", sep="")
    system(cmd)
    getwd()
}

#setwd(file.path(curDir))

#outDirs = unlist(outDirs)

#write.table(outDirs, file=paste(curDir, "/", rootFolderName, "/dirs.txt", sep=""), quote = F, col.names = F, row.names = F)

#cmd1 = paste("Rscript ", curDir, "/run.R ", rootFolderName, "/dirs.txt", sep="")
#system(cmd1)

#cmd2 <- paste("Rscript ", curDir, "/plotNetwork.R ", "neutral run1", sep="")
#system(cmd2)
