a <- read.table("R1.txt")


dec2bin <- function(x, n=30)
{
    y <- ""
    for ( i in 1:n ){
        y <- paste(y, x%%2, sep="")
        x <- x%/%2
    }
    return(y)
}

getGenerationAlignment <- function(a, ## dataset
                                   g, ## generation
                                   k=1000, ## individuals per generation
                                   n=10, ## genes per individual
                                   ss=-1,
                                   gindex=1 ){
    if(gindex == n){
        gindex <- 0
    }
    if(ss == -1){
        ss = k
    }
    ## the individuals of generation g
    b <- a[ ((g-1)*(k*n) + 1):(g*k*n)+1 ]
    ## get the gene 'geneindex' from this generation
    b <- b[ 1:length(b) %% n == gindex ]
    print(length(b))
    asample <- sample(x=b, size=ss, replace=F)
    alignment <- array("", ss)
    for( i in 1:ss){
        alignment[i] <- dec2bin(asample[i], 30)
    }
    return(alignment)
}

#getGenerationAlignment(a[,1], g=10, n=10, k=100, gindex=1)

write.table(getGenerationAlignment(a[,1], g=10, n=10, k=1000, ss=1000, gindex=1), file='R1.alignment', quote=F, row.names=F, col.names=F)

R1_data=as.data.frame(read.table("R1.txt"))

sink("R1.alignment")
for (i in 1:11-1){
    range1=(i*10000)+1
    range2=(i*10000)+10000
    generation=R1_data[range1:range2,]
    print(count_NAs_generations(i))
    print(dim(apomonwmenoi))
}
sink()
