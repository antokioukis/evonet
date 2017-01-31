args = commandArgs(trailingOnly=TRUE)

ss <- 20
n=args[1]

#population
N <- 1000

#Length of neutral region
l <- 1000

makeSFS <- function(ar, n){
    sfs <- array(0, n+1)
    for( i in ar){
        sfs[i+1] <- sfs[i+1]+1
    }
    names(sfs) <- 0:(n)
    return(sfs)
}

totalSFS <- array(0, N+1)

for(i in 1:n){
#    print(i)
### a<-read.table("neutralOutput.txt",colClasses="character")
    a <- read.table(paste("./run", i, "/neutralOutput000.txt", sep=""), colClasses="character")
    b <- matrix(as.numeric(unlist(strsplit(x=a[,2], split=''))), ncol=l, byrow=TRUE)
    rowstoconsider <-sample((nrow(b)-N+1):nrow(b),ss)
    d <- b[ rowstoconsider, ]
    sumd <- apply(d,2,sum)
    sfs <- makeSFS(sumd, ss)
    totalSFS <- totalSFS + sfs
}



pdf("sfs.pdf")
barplot(totalSFS[2:(length(totalSFS)-1)])
dev.off()

