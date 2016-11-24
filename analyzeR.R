a <- read.table("R1.txt")

dec2bin <- function(x, n=10)
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
                                   gindex=1,
                                   regLength=30){

    ## a <- a[,1]
    ## g <- 75
    ## k <- 1000
    ## n <- 10
    ## gindex <- 4
    ## ss <- -1
    #regLength=30
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

    asample <- sample(x=b, size=ss, replace=F)

    alignment <- array("", ss)

    for( i in 1:ss){
        alignment[i] <- dec2bin(asample[i], regLength)
    }
    
    return(alignment)
}


a
al <- getGenerationAlignment(a[,1], g=75, n=10, k=1000, ss=10, gindex=1, regLength=30)

unique(al)


write.table(sort(getGenerationAlignment(a[,1], g=75, n=10, k=1000, gindex=1, regLength=30)), file='R1.alignment', quote=F, row.names=F, col.names=F)
