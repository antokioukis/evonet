rm(list=ls())
library(foreach)
library(doMC)
registerDoMC(10)

system("make clean")
system("make all")
system("gcc fitnessSimple.c -lm -lgsl -lgslcblas -o fitnessSimple")
n <- 1
r <- 1
N <- 1000
rr <- 0.005
mr <- 0.5
s<- 10
sel <- 1
ploidy <- 1
freq<-1

modechange <- 1
newfreq <- 1
modechangePhrase <- ""

if( sel == 0){
    name <- "neutral"
}else{
    name <- "selection"
}

#if( modechange != 0){
#    if(sel == 1){
#        sel <- 0
#    }else{
#        sel <- 1
#    }
#    modechangePhrase <- paste(" -mod_change ", modechange, " ", newfreq, " ", sep="")
#}else{
 #   modechangePhrase<-""
#}

curDir <- getwd()

randInt <- floor(runif(n, 0, 10000000))

write.table(randInt, file="seeds.txt", quote=F, row.names=F, col.names=F)
j=1
step=0.001
################################################################################################################################################
mr<-0.05
################################################################################################################################################
name<-"free1mr005perc001"
foreach(i = 1:n) %dopar% {
    seed <- randInt[i]
    #print(seed)
    dirName <- paste(name, ".run.", i, sep="")
    dir.create(file.path(curDir, dirName), showWarnings=FALSE)
    working_dir<-file.path(curDir, dirName)
    setwd(file.path(curDir, dirName))
	#na exei na diavasei to evonet
    system(paste("Rscript ",curDir, "/write_file.R > ", working_dir,"/R1R2_input.txt",sep=""))
    #print (paste("Rscript ",curDir, "/write_file.R > ", working_dir,"/R1R2_input.txt",sep=""))
    #mr=mr+step*(i-1)
    #print(mr)
	#tre3imo evonet
    cmd <- paste(curDir, "/evonet -selection ", sel," -key_genes 9 -st_geno R1R2_input.txt ", "-s2 ", s, " -N ", N, " -tarfit 0.95 -generations 1 "," -ploidy ", ploidy, "  -swapping 0 -freq ", freq, " -min_count 10 -max_count 11 -generations ",r ," -n 10 -recomb_rate ",rr ," -mutrate ",mr, " -seed ", seed, " -optimal_num 10", sep="")
    #print (cmd)
    system(cmd)
	#tre3imo fitnessSimple
    #cmd <- paste(curDir, "/fitnessSimple -mu " ,mr, " -l 10 -popsize ", N ," -fm 1 -s ", s, " -p 2 -seed ", seed, sep="")
    #system(cmd)
	#print(cmd)
}

j=1
name<-"free3mr005perc001"
foreach(i = 1:n) %dopar% {
    seed <- randInt[i]
    #print(seed)
    dirName <- paste(name, ".run.", i, sep="")
    dir.create(file.path(curDir, dirName), showWarnings=FALSE)
    working_dir<-file.path(curDir, dirName)
    setwd(file.path(curDir, dirName))
    system(paste("Rscript ",curDir, "/write_file.R > ", working_dir,"/R1R2_input.txt",sep=""))
    cmd <- paste(curDir, "/evonet -selection ", sel," -key_genes 7 -st_geno R1R2_input.txt ", "-s2 ", s, " -N ", N, " -tarfit 0.95 -generations 1 "," -ploidy ", ploidy, "  -swapping 0 -freq ", freq, " -min_count 10 -max_count 11 -generations ",r ," -n 10 -recomb_rate ",rr ," -mutrate ",mr, " -seed ", seed, " -optimal_num 10", sep="")
    system(cmd)
}

j=1
name<-"free5mr005perc001"
foreach(i = 1:n) %dopar% {
    seed <- randInt[i]
    dirName <- paste(name, ".run.", i, sep="")
    dir.create(file.path(curDir, dirName), showWarnings=FALSE)
    working_dir<-file.path(curDir, dirName)
    setwd(file.path(curDir, dirName))
    system(paste("Rscript ",curDir, "/write_file.R > ", working_dir,"/R1R2_input.txt",sep=""))
    cmd <- paste(curDir, "/evonet -selection ", sel," -key_genes 5 -st_geno R1R2_input.txt ", "-s2 ", s, " -N ", N, " -tarfit 0.95 -generations 1 "," -ploidy ", ploidy, "  -swapping 0 -freq ", freq, " -min_count 10 -max_count 11 -generations ",r ," -n 10 -recomb_rate ",rr ," -mutrate ",mr, " -seed ", seed, " -optimal_num 10", sep="")
    system(cmd)
}

j=1
name<-"free7mr005perc001"
foreach(i = 1:n) %dopar% {
    seed <- randInt[i]
    dirName <- paste(name, ".run.", i, sep="")
    dir.create(file.path(curDir, dirName), showWarnings=FALSE)
    working_dir<-file.path(curDir, dirName)
    setwd(file.path(curDir, dirName))
    system(paste("Rscript ",curDir, "/write_file.R > ", working_dir,"/R1R2_input.txt",sep=""))
    cmd <- paste(curDir, "/evonet -selection ", sel," -key_genes 3 -st_geno R1R2_input.txt ", "-s2 ", s, " -N ", N, " -tarfit 0.95 -generations 1 "," -ploidy ", ploidy, "  -swapping 0 -freq ", freq, " -min_count 10 -max_count 11 -generations ",r ," -n 10 -recomb_rate ",rr ," -mutrate ",mr, " -seed ", seed, " -optimal_num 10", sep="")
    system(cmd)
}

################################################################################################################################################
mr<-0.1
################################################################################################################################################
name<-"free1mr01perc001"
foreach(i = 1:n) %dopar% {
    seed <- randInt[i]
    #print(seed)
    dirName <- paste(name, ".run.", i, sep="")
    dir.create(file.path(curDir, dirName), showWarnings=FALSE)
    working_dir<-file.path(curDir, dirName)
    setwd(file.path(curDir, dirName))
    #na exei na diavasei to evonet
    system(paste("Rscript ",curDir, "/write_file.R > ", working_dir,"/R1R2_input.txt",sep=""))
    #print (paste("Rscript ",curDir, "/write_file.R > ", working_dir,"/R1R2_input.txt",sep=""))
    #mr=mr+step*(i-1)
    #print(mr)
    #tre3imo evonet
    cmd <- paste(curDir, "/evonet -selection ", sel," -key_genes 9 -st_geno R1R2_input.txt ", "-s2 ", s, " -N ", N, " -tarfit 0.95 -generations 1 "," -ploidy ", ploidy, "  -swapping 0 -freq ", freq, " -min_count 10 -max_count 11 -generations ",r ," -n 10 -recomb_rate ",rr ," -mutrate ",mr, " -seed ", seed, " -optimal_num 10", sep="")
    #print (cmd)
    system(cmd)
    #tre3imo fitnessSimple
    #cmd <- paste(curDir, "/fitnessSimple -mu " ,mr, " -l 10 -popsize ", N ," -fm 1 -s ", s, " -p 2 -seed ", seed, sep="")
    #system(cmd)
    #print(cmd)
}

j=1
name<-"free3mr01perc001"
foreach(i = 1:n) %dopar% {
    seed <- randInt[i]
    #print(seed)
    dirName <- paste(name, ".run.", i, sep="")
    dir.create(file.path(curDir, dirName), showWarnings=FALSE)
    working_dir<-file.path(curDir, dirName)
    setwd(file.path(curDir, dirName))
    system(paste("Rscript ",curDir, "/write_file.R > ", working_dir,"/R1R2_input.txt",sep=""))
    cmd <- paste(curDir, "/evonet -selection ", sel," -key_genes 7 -st_geno R1R2_input.txt ", "-s2 ", s, " -N ", N, " -tarfit 0.95 -generations 1 "," -ploidy ", ploidy, "  -swapping 0 -freq ", freq, " -min_count 10 -max_count 11 -generations ",r ," -n 10 -recomb_rate ",rr ," -mutrate ",mr, " -seed ", seed, " -optimal_num 10", sep="")
    system(cmd)
}

j=1
name<-"free5mr01perc001"
foreach(i = 1:n) %dopar% {
    seed <- randInt[i]
    dirName <- paste(name, ".run.", i, sep="")
    dir.create(file.path(curDir, dirName), showWarnings=FALSE)
    working_dir<-file.path(curDir, dirName)
    setwd(file.path(curDir, dirName))
    system(paste("Rscript ",curDir, "/write_file.R > ", working_dir,"/R1R2_input.txt",sep=""))
    cmd <- paste(curDir, "/evonet -selection ", sel," -key_genes 5 -st_geno R1R2_input.txt ", "-s2 ", s, " -N ", N, " -tarfit 0.95 -generations 1 "," -ploidy ", ploidy, "  -swapping 0 -freq ", freq, " -min_count 10 -max_count 11 -generations ",r ," -n 10 -recomb_rate ",rr ," -mutrate ",mr, " -seed ", seed, " -optimal_num 10", sep="")
    system(cmd)
}

j=1
name<-"free7mr01perc001"
foreach(i = 1:n) %dopar% {
    seed <- randInt[i]
    dirName <- paste(name, ".run.", i, sep="")
    dir.create(file.path(curDir, dirName), showWarnings=FALSE)
    working_dir<-file.path(curDir, dirName)
    setwd(file.path(curDir, dirName))
    system(paste("Rscript ",curDir, "/write_file.R > ", working_dir,"/R1R2_input.txt",sep=""))
    cmd <- paste(curDir, "/evonet -selection ", sel," -key_genes 3 -st_geno R1R2_input.txt ", "-s2 ", s, " -N ", N, " -tarfit 0.95 -generations 1 "," -ploidy ", ploidy, "  -swapping 0 -freq ", freq, " -min_count 10 -max_count 11 -generations ",r ," -n 10 -recomb_rate ",rr ," -mutrate ",mr, " -seed ", seed, " -optimal_num 10", sep="")
    system(cmd)
}

################################################################################################################################################
mr<-0.15
################################################################################################################################################
name<-"free1mr015perc001"
foreach(i = 1:n) %dopar% {
    seed <- randInt[i]
    #print(seed)
    dirName <- paste(name, ".run.", i, sep="")
    dir.create(file.path(curDir, dirName), showWarnings=FALSE)
    working_dir<-file.path(curDir, dirName)
    setwd(file.path(curDir, dirName))
    #na exei na diavasei to evonet
    system(paste("Rscript ",curDir, "/write_file.R > ", working_dir,"/R1R2_input.txt",sep=""))
    #print (paste("Rscript ",curDir, "/write_file.R > ", working_dir,"/R1R2_input.txt",sep=""))
    #mr=mr+step*(i-1)
    #print(mr)
    #tre3imo evonet
    cmd <- paste(curDir, "/evonet -selection ", sel," -key_genes 9 -st_geno R1R2_input.txt ", "-s2 ", s, " -N ", N, " -tarfit 0.95 -generations 1 "," -ploidy ", ploidy, "  -swapping 0 -freq ", freq, " -min_count 10 -max_count 11 -generations ",r ," -n 10 -recomb_rate ",rr ," -mutrate ",mr, " -seed ", seed, " -optimal_num 10", sep="")
    #print (cmd)
    system(cmd)
    #tre3imo fitnessSimple
    #cmd <- paste(curDir, "/fitnessSimple -mu " ,mr, " -l 10 -popsize ", N ," -fm 1 -s ", s, " -p 2 -seed ", seed, sep="")
    #system(cmd)
    #print(cmd)
}

j=1
name<-"free3mr015perc001"
foreach(i = 1:n) %dopar% {
    seed <- randInt[i]
    #print(seed)
    dirName <- paste(name, ".run.", i, sep="")
    dir.create(file.path(curDir, dirName), showWarnings=FALSE)
    working_dir<-file.path(curDir, dirName)
    setwd(file.path(curDir, dirName))
    system(paste("Rscript ",curDir, "/write_file.R > ", working_dir,"/R1R2_input.txt",sep=""))
    cmd <- paste(curDir, "/evonet -selection ", sel," -key_genes 7 -st_geno R1R2_input.txt ", "-s2 ", s, " -N ", N, " -tarfit 0.95 -generations 1 "," -ploidy ", ploidy, "  -swapping 0 -freq ", freq, " -min_count 10 -max_count 11 -generations ",r ," -n 10 -recomb_rate ",rr ," -mutrate ",mr, " -seed ", seed, " -optimal_num 10", sep="")
    system(cmd)
}

j=1
name<-"free5mr015perc001"
foreach(i = 1:n) %dopar% {
    seed <- randInt[i]
    dirName <- paste(name, ".run.", i, sep="")
    dir.create(file.path(curDir, dirName), showWarnings=FALSE)
    working_dir<-file.path(curDir, dirName)
    setwd(file.path(curDir, dirName))
    system(paste("Rscript ",curDir, "/write_file.R > ", working_dir,"/R1R2_input.txt",sep=""))
    cmd <- paste(curDir, "/evonet -selection ", sel," -key_genes 5 -st_geno R1R2_input.txt ", "-s2 ", s, " -N ", N, " -tarfit 0.95 -generations 1 "," -ploidy ", ploidy, "  -swapping 0 -freq ", freq, " -min_count 10 -max_count 11 -generations ",r ," -n 10 -recomb_rate ",rr ," -mutrate ",mr, " -seed ", seed, " -optimal_num 10", sep="")
    system(cmd)
}

j=1
name<-"free7mr015perc001"
foreach(i = 1:n) %dopar% {
    seed <- randInt[i]
    dirName <- paste(name, ".run.", i, sep="")
    dir.create(file.path(curDir, dirName), showWarnings=FALSE)
    working_dir<-file.path(curDir, dirName)
    setwd(file.path(curDir, dirName))
    system(paste("Rscript ",curDir, "/write_file.R > ", working_dir,"/R1R2_input.txt",sep=""))
    cmd <- paste(curDir, "/evonet -selection ", sel," -key_genes 3 -st_geno R1R2_input.txt ", "-s2 ", s, " -N ", N, " -tarfit 0.95 -generations 1 "," -ploidy ", ploidy, "  -swapping 0 -freq ", freq, " -min_count 10 -max_count 11 -generations ",r ," -n 10 -recomb_rate ",rr ," -mutrate ",mr, " -seed ", seed, " -optimal_num 10", sep="")
    system(cmd)
}

################################################################################################################################################
mr<-0.2
################################################################################################################################################
name<-"free1mr02perc001"
foreach(i = 1:n) %dopar% {
    seed <- randInt[i]
    #print(seed)
    dirName <- paste(name, ".run.", i, sep="")
    dir.create(file.path(curDir, dirName), showWarnings=FALSE)
    working_dir<-file.path(curDir, dirName)
    setwd(file.path(curDir, dirName))
    #na exei na diavasei to evonet
    system(paste("Rscript ",curDir, "/write_file.R > ", working_dir,"/R1R2_input.txt",sep=""))
    #print (paste("Rscript ",curDir, "/write_file.R > ", working_dir,"/R1R2_input.txt",sep=""))
    #mr=mr+step*(i-1)
    #print(mr)
    #tre3imo evonet
    cmd <- paste(curDir, "/evonet -selection ", sel," -key_genes 9 -st_geno R1R2_input.txt ", "-s2 ", s, " -N ", N, " -tarfit 0.95 -generations 1 "," -ploidy ", ploidy, "  -swapping 0 -freq ", freq, " -min_count 10 -max_count 11 -generations ",r ," -n 10 -recomb_rate ",rr ," -mutrate ",mr, " -seed ", seed, " -optimal_num 10", sep="")
    #print (cmd)
    system(cmd)
    #tre3imo fitnessSimple
    #cmd <- paste(curDir, "/fitnessSimple -mu " ,mr, " -l 10 -popsize ", N ," -fm 1 -s ", s, " -p 2 -seed ", seed, sep="")
    #system(cmd)
    #print(cmd)
}

j=1
name<-"free3mr02perc001"
foreach(i = 1:n) %dopar% {
    seed <- randInt[i]
    #print(seed)
    dirName <- paste(name, ".run.", i, sep="")
    dir.create(file.path(curDir, dirName), showWarnings=FALSE)
    working_dir<-file.path(curDir, dirName)
    setwd(file.path(curDir, dirName))
    system(paste("Rscript ",curDir, "/write_file.R > ", working_dir,"/R1R2_input.txt",sep=""))
    cmd <- paste(curDir, "/evonet -selection ", sel," -key_genes 7 -st_geno R1R2_input.txt ", "-s2 ", s, " -N ", N, " -tarfit 0.95 -generations 1 "," -ploidy ", ploidy, "  -swapping 0 -freq ", freq, " -min_count 10 -max_count 11 -generations ",r ," -n 10 -recomb_rate ",rr ," -mutrate ",mr, " -seed ", seed, " -optimal_num 10", sep="")
    system(cmd)
}

j=1
name<-"free5mr02perc001"
foreach(i = 1:n) %dopar% {
    seed <- randInt[i]
    dirName <- paste(name, ".run.", i, sep="")
    dir.create(file.path(curDir, dirName), showWarnings=FALSE)
    working_dir<-file.path(curDir, dirName)
    setwd(file.path(curDir, dirName))
    system(paste("Rscript ",curDir, "/write_file.R > ", working_dir,"/R1R2_input.txt",sep=""))
    cmd <- paste(curDir, "/evonet -selection ", sel," -key_genes 5 -st_geno R1R2_input.txt ", "-s2 ", s, " -N ", N, " -tarfit 0.95 -generations 1 "," -ploidy ", ploidy, "  -swapping 0 -freq ", freq, " -min_count 10 -max_count 11 -generations ",r ," -n 10 -recomb_rate ",rr ," -mutrate ",mr, " -seed ", seed, " -optimal_num 10", sep="")
    system(cmd)
}

j=1
name<-"free7mr02perc001"
foreach(i = 1:n) %dopar% {
    seed <- randInt[i]
    dirName <- paste(name, ".run.", i, sep="")
    dir.create(file.path(curDir, dirName), showWarnings=FALSE)
    working_dir<-file.path(curDir, dirName)
    setwd(file.path(curDir, dirName))
    system(paste("Rscript ",curDir, "/write_file.R > ", working_dir,"/R1R2_input.txt",sep=""))
    cmd <- paste(curDir, "/evonet -selection ", sel," -key_genes 3 -st_geno R1R2_input.txt ", "-s2 ", s, " -N ", N, " -tarfit 0.95 -generations 1 "," -ploidy ", ploidy, "  -swapping 0 -freq ", freq, " -min_count 10 -max_count 11 -generations ",r ," -n 10 -recomb_rate ",rr ," -mutrate ",mr, " -seed ", seed, " -optimal_num 10", sep="")
    system(cmd)
}