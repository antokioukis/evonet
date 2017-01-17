i=1

data<-c()

con = file("genotype.txt", "r")

while ( TRUE ) {
    line = readLines(con, n = 1)

    if ( length(line) == 0 ) {
        break
    }
    data[i] <- length(unlist(strsplit(line, split=" ")))
    i=i+1
}

png(filename="diff_geno.png")
barplot(data,xlab="Generation Number",ylab="Number of Different Genotypes")
dev.off()

