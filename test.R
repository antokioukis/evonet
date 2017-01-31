rm(list=ls())
i=1
j=1
k=1
#number of runs
n=5

data<-c()
hetero <- c()

total_hetero <- c()
total_data <- c()

curDir <- getwd()

name <- "neutral"

computeHetero <- function(x) {
    x <- as.numeric(x)
    #print(x)
    n <- sum(x)
    freqs <- x/n
    return(1.0 - sum(freqs*freqs))
}


newEl <- 1
while (j<n+1){
    active_dir <- file.path(curDir, paste(name,".run.", j, sep=""))
    con = file(paste(active_dir,"/genotype.txt",sep=""), "r")
    while ( TRUE ) {
        line = readLines(con, n = 1)

        if ( length(line) == 0 ) {
            break
        }
        if( newEl == 1){
            total_hetero <- c(total_hetero, 0)
        }
        
        hetero[i] <- computeHetero( unlist(strsplit(line, split=" ")) )
        data[i] <- length(unlist(strsplit(line, split=" ")))
        
        total_hetero[i]<-hetero[i] + total_hetero[i]
        #total_data[i]<-data[i] + total_data [i]
        print(paste("hetero ", hetero[i]))
        i=i+1
    }
    newEl <- 0
    print(i)
    i=1
    j=j+1
}

for(k in 1:length(total_hetero)){
    total_hetero[k]<-total_hetero[k]/n
    print(total_hetero[k])
#    total_data[k]<-total_data [k]/n

}

png(filename="diff_geno.png")
#layout(matrix(1:2, nrow=1, byrow=TRUE))
barplot(total_hetero, xlab="Generation", ylab="Heterozygosity")
#barplot(total_data,xlab="Generation",ylab="Number of Different Genotypes")
dev.off()



