## get the file
dirName <- "./selection/run3"
file = basename(dirName)

options(echo=TRUE) # if you want see commands in output file
args <- commandArgs(trailingOnly = TRUE)
if(length(args) > 0){
    file <-  basename(args[1])
    dirName <- args[1]
    setwd(dirname(args[1]))
}

N <- 100

fileName <- paste(dirName,  "/matrix.txt", sep="")
fitnessName <- paste(dirName, "/fitnesss.txt", sep="")

fitness <- read.table(fitnessName, head=F)

trim <- function (x) gsub("^\\s+|\\s+$", "", x)

getPop <- function(fileName, N=500){
    print("GetPop")
    allData <- list()
    con <- file(fileName, "r")
    line <- lapply(readLines(con), trim)
    close(con)
    
    print("File read")
    dimData <- length(line)/N
    j <- 0

    for( i in 1:dimData){
        if(dimData > 100 & (i %% floor(dimData/100) == 0)){
            j <- j+1;
            print(j)
        }
        df <- data.frame()
        allData <- append(allData, list(df))
        allData[[i]] <- matrix(unlist(lapply(line[((i-1)*N+1):(i*N)], function(x){as.numeric(unlist(strsplit(x, split="\\s+")))})), nrow=N, byrow=TRUE)
    }
    return(allData)
}


getPopStr <- function(fileName, N=500){
    allData <- list()
    con <- file(fileName, "r")
    line <- readLines(con)
    close(con)
    
    dimData <- length(line)/N
    for( i in 1:dimData){
        df <- c()
        allData <- append(allData, list(df))
    }
    
    for( i in 1:length(line)){
        index <- floor((i-1)/N + 1)
        allData[[index]] <- c(allData[[index]], as.character(line[i]))
    }
    
    return(allData)
}

getHomozygosity = function(m)
    {
        het = apply(m, 1, function(x){ sum(x*x)/(sum(x)*sum(x)) })
        return(het)
    }

data <- getPopStr(fileName, N=N)
dataMat <- getPop(fileName, N=N)
dataMat[[1]]
## for each generation, how many times do we observe
## each network
het <- lapply(data, function(x){ as.numeric(table(x))})
##het2 = getHeterozygosity(dataMat)

## which is the maximum frequency that we observe a network
## for each generation
maxFreq <- unlist(lapply(het, max))

## all generations
x <- 1:length(fitness[,4])
## this is the same, I can use ins to restrict the analysis for only some generations
ins <- x

## unique names
allNames <- unique(unlist(lapply(data, function(x){
    names(table(x))})))
length(allNames)

occs <- rep(0, length(allNames))
names(occs) <- allNames
## nrow: generations
## ncol: all (matrix) haplotypes
occsMatrix <- matrix(0, nrow=dim(fitness)[1], ncol=length(occs)) 

for(i in 1:dim(fitness)[1]){
    occs <- rep(0, length(allNames))
    names(occs) <- allNames
    occs[names(table(data[[i]]))] <- as.numeric(table(data[[i]]))
    occsMatrix[i,] <- as.numeric(occs)
}



colnames(occsMatrix) <- allNames

save(allNames, file=paste(file, ".allNames.RData", sep=""))
          
grnOccs = function(v){
    v1 = v > 0
    occs = 0
    for(i in 2:length(v1)){
        if( (i==2 & v1[i] == TRUE) | (v1[i-1] == FALSE & v1[i] == TRUE) ){
            occs = occs + 1
        }
    }
    return(occs)
}

#apply(occsMatrix, 2, grnOccs)

highGRNinds <- which(apply(occsMatrix, 2, max) > N/2)
highOccs <- occsMatrix[, highGRNinds] ## named matrix

ll <- dim(highOccs)[2]
means <- unlist(lapply(1:ll, function(ii){mean(fitness[which(highOccs[,ii] > N/2), 4])}))
means2 <- c(0, means)
means3 <- c(means[-1], 0)

names(means) <- colnames(highOccs)

xx <- 1:length(means)
intInds <- means-means2[-length(means2)] > 0.01
intInds2 <- means-means3 < -0.01

timesFirstOccurences = as.numeric(apply(occsMatrix, 2, function(x) { min(which(x >  0))}))

nonZeroNets = as.numeric(apply(occsMatrix, 1, function(x){ length(which(x > 0)) } ))

### homozygosity plots
het2 = getHomozygosity(occsMatrix)

pdf(paste(file, "_homozygosityVSFitness.pdf", sep=""))
par(mar=c(4,4,3,4))
plot(het2, pch=16, cex=0.7, col="black", axes=F, xlab="Generations", ylab="Heterozygosity")
points(lowess(het2), type='l', col="red", lw=2)
axis(side=1)
axis(side=2)
par(new=T)
plot(fitness[,4], col="blue", type='l', axes=F)
axis(side=4)
dev.off()


his = hist(timesFirstOccurences, breaks=100, col="lightgray", border = "gray", axes=F, xlab="", ylab="", plot=F)
his2= hist(nonZeroNets, breaks=100, col="lightgray", border = "gray", axes=F, xlab="", ylab="", plot=F)

pdf(paste(file, "_timesFirstOccurences.pdf", sep=""))
par(mar=c(5,8,3,5))
plot(ins, nonZeroNets, col="lightgray", axes=F, type='l')
axis(side=2, pos=4)
par(new=TRUE)
#plot(his2$mids, his2$counts, col="darkgray", axes=F, type='l')
#par(new=TRUE)
##hist(timesFirstOccurences, breaks=100, col="lightgray", border = "gray", axes=F, xlab="", ylab="")
plot(his$mids, his$counts, col="red", type='l', axes=F, lwd=2)
axis(side=1)
axis(side=2)
mtext(side=1, "Generations", 2.5)
mtext(side=2, "Number of new GRNs", 2.5)
par(new=TRUE)
plot(fitness[ins,4], type='l', col='blue', axes=F, xlab="", ylab="")
axis(side=4)
mtext(side=4, text="Fitness", 2.5)
dev.off()

intNames1 <- names(means)[intInds]
intNames2 <- names(means)[intInds2]
    
pdf(paste(file, "_highGRN", file, ".pdf", sep=""))
for(i in 1:length(highGRNinds)){
    plot(occsMatrix[, highGRNinds[i]], type='l', ylim=c(0,N), col="black")
    par(new=TRUE)
    plot(fitness[ins,4], type='l', col='blue', axes=F, xlab="", ylab="")
    axis(side=4)
}
dev.off()

pdf(paste("ALL_highGRNPlots_neutral18", file, ".pdf", sep=""))
for(i in 1:length(highGRNinds)){
    plot(occsMatrix[, highGRNinds[i]], type='l', ylim=c(0,N), axes=F, col=i%%5+1)
    if(i == 1) axis(side=1)
    par(new=TRUE)
    plot(fitness[ins,4], type='l', col='blue', axes=F, xlab="", ylab="")
    if(i == 1) axis(side=4)
    par(new=TRUE)
}
dev.off()



## for(j in 1:5){
##     rm(occsMatrix, obList, file, data, dataMat, dirName, fileName, fitness, fitnessName, getPop, getPopStr, N ,trim)
##     j
##     load(paste("20170417_1600.run.", j, ".RData", sep=""))

##     het <- lapply(data, function(x){ as.numeric(table(x))})
##     maxFreq <- unlist(lapply(het, max))
##     x <- 1:length(fitness[,4])
##     ins <- x
##     allNames <- unique(unlist(lapply(data, function(x){names(table(x))})))
##     occs <- rep(0, length(allNames))
##     names(occs) <- allNames
##     ## nrow: generations
##     ## ncol: all (matrix) haplotypes
##     occsMatrix <- matrix(0, nrow=dim(fitness)[1], ncol=length(occs)) 
##     for(i in 1:dim(fitness)[1]){
##         occs <- rep(0, length(allNames))
##         names(occs) <- allNames
##         occs[names(table(data[[i]]))] <- as.numeric(table(data[[i]]))
##         occsMatrix[i,] <- as.numeric(occs)
##     }
##     colnames(occsMatrix) <- allNames
##     highGRNinds <- which(apply(occsMatrix, 2, max) > N/2)
##     highOccs <- occsMatrix[, highGRNinds] ## named matrix
##     ll <- dim(highOccs)[2]
##     means <- unlist(lapply(1:ll, function(ii){mean(fitness[which(highOccs[,ii] > N/2), 4])}))
##     means2 <- c(0, means)
##     means3 <- c(means[-1], 0)
##     names(means) <- colnames(highOccs)
##     xx <- 1:length(means)
##     names(xx) <- names(means)
##     intInds <- means-means2[-length(means2)] > 0.01
##     intInds2 <- means-means3 < -0.01

##     ## plot(xx, means)
##     ## points(xx[c(intInds)], means[ names(means)[intInds] ], pch=16, col="red")
##     ## points(xx[c(intInds2)], means[ names(means)[intInds2] ], pch=16, col="red")
##     ## points(xx[ intNames1.2 ], means[ intNames1.2 ], pch=16, col="blue")
##     ## points(xx[ intNames2.2 ], means[ intNames2.2 ], pch=16, col="blue")
##     ## points(xx[ intNames1.5 ], means[ intNames1.5 ], pch=16, col="orange")
##     ## points(xx[ intNames2.5 ], means[ intNames2.5 ], pch=16, col="orange")
##     ## points(xx[ intNames1.3 ], means[ intNames1.3 ], pch=16, col="black")
##     ## points(xx[ intNames2.3 ], means[ intNames2.3 ], pch=16, col="black")

##     intNames1 <- names(means)[intInds]
##     intNames2 <- names(means)[intInds2]
    
##     ##intNames1.5 <- names(means)[intInds]
##     ##intNames2.5 <- names(means)[intInds2]
    
##     setX <- list(intNames1, intNames2, occsMatrix)
##     eval(parse(text=paste(paste("set",j, sep=""), "setX", sep=" <- ")), envir=.GlobalEnv)
##     eval(parse(text=paste("save(set", j, ", file=paste(\"intNames.\",",j,",\".RData\", sep=\"\")) ", sep="")))
    
    
## }


## for(j in 1:5 ){
##     load(paste("intNames.", j, ".RData", sep=""))
## }

## lm <- matrix(0, nrow=5, ncol=5)
## for(j in 1:5){
##     for(i in 1:5){
##         cmd <- paste( "length(intersect(colnames(set", j, "[[3]]),", " colnames(set", i, "[[3]])) )", sep="")
##         lm[i,j] <- eval(parse(text=cmd), envir=.GlobalEnv)
##     }
## }

## lm

## for(j in 1:5){
##     j
##     rm(file, data, dataMat, dirName, fileName, fitness, fitnessName, getPop, getPopStr, N ,trim)
##     load(paste("20170417_1600.run.", j, ".RData", sep=""))


##     het <- lapply(data, function(x){ as.numeric(table(x))})

##     maxFreq <- unlist(lapply(het, max))

##     x <- 1:length(fitness[,4])
##     ins <- x

##     allNames <- unique(unlist(lapply(data, function(x){
##         names(table(x))})))

##     occs <- rep(0, length(allNames))
##     names(occs) <- allNames
##     ## nrow: generations
##     ## ncol: all (matrix) haplotypes
##     occsMatrix <- matrix(0, nrow=dim(fitness)[1], ncol=length(occs)) 

##     for(i in 1:dim(fitness)[1]){
##         occs <- rep(0, length(allNames))
##         names(occs) <- allNames
##         occs[names(table(data[[i]]))] <- as.numeric(table(data[[i]]))
##         occsMatrix[i,] <- as.numeric(occs)
##     }
##     colnames(occsMatrix) <- allNames

##     highGRNinds <- which(apply(occsMatrix, 2, max) > N/2)
##     highOccs <- occsMatrix[, highGRNinds] ## named matrix

##     ll <- dim(highOccs)[2]
##     means <- unlist(lapply(1:ll, function(ii){mean(fitness[which(highOccs[,ii] > N/2), 4])}))
##     means2 <- c(0, means)
##     means3 <- c(means[-1], 0)
    
##     names(means) <- colnames(highOccs)
    
##     xx <- 1:length(means)
##     intInds <- means-means2[-length(means2)] > 0.01
##     intInds2 <- means-means3 < -0.01

    
##     plot(xx, means)
##     points(xx[c(intInds)], means[ names(means)[intInds] ], pch=16, col="red")
##     points(xx[c(intInds2)], means[ names(means)[intInds2] ], pch=16, col="red")

##     intNames1 <- names(means)[intInds]
##     intNames2 <- names(means)[intInds2]
    
##     pdf(paste("highGRNPlots_", file, ".pdf", sep=""))
##     for(i in 1:length(highGRNinds)){
##         plot(occsMatrix[, highGRNinds[i]], type='l', ylim=c(0,N), col="black")
##         par(new=TRUE)
##         plot(fitness[ins,4], type='l', col='blue', axes=F, xlab="", ylab="")
##         axis(side=4)
##     }
##     dev.off()

##     pdf(paste("ALL_highGRNPlots_", file, ".pdf", sep=""))
##     for(i in 1:length(highGRNinds)){
##         plot(occsMatrix[, highGRNinds[i]], type='l', ylim=c(0,N), axes=F, col=i%%5+1)
##         if(i == 1) axis(side=1)
##         par(new=TRUE)
##         plot(fitness[ins,4], type='l', col='blue', axes=F, xlab="", ylab="")
##         if(i == 1) axis(side=4)
##         par(new=TRUE)
##     }
##     dev.off()
    
## }



## dev.off()


## }
