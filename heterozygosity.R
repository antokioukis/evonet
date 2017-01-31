rm(list=ls())
i=1

data<-c()
hetero <- c()

con = file("genotype.txt", "r")



computeHetero <- function(x) {
    x <- as.numeric(x)
    print(x)
    n <- sum(x)
    freqs <- x/n
    return(1.0 - sum(freqs*freqs))
}

while ( TRUE ) {
    line = readLines(con, n = 1)

    if ( length(line) == 0 ) {
        break
    }
    hetero[i] <- computeHetero( unlist(strsplit(line, split=" ")) )
    data[i] <- length(unlist(strsplit(line, split=" ")))
    i=i+1
}

png(filename="diff_geno.png")
layout(matrix(1:2, nrow=1, byrow=TRUE))
barplot(hetero, xlab="Generation", ylab="Heterozygosity")
barplot(data,xlab="Generation",ylab="Number of Different Genotypes")
dev.off()



