#population
N <- 1000

#Length of neutral region
l <- 2000


makeSFS <- function(ar, n){
    sfs <- array(0, n+1)
    for( i in ar){
        sfs[i+1] <- sfs[i+1]+1
    }
    names(sfs) <- 0:(n)
    return(sfs)
}

totalSFS <- array(0, N+1)

#for(i in 1:35){

    a<-read.table("neutralOutput.txt",colClasses="character")
    #a <- read.table(paste("./run", i, "/neutralOutput.txt", sep=""), colClasses="character")

    b <- matrix(as.numeric(unlist(strsplit(x=a[,2], split=''))), ncol=l, byrow=TRUE)

    d <- b[ (nrow(b)-N+1):nrow(b), ]

    sumd <- apply(d,2,sum)

    sfs <- makeSFS(sumd, N)

    totalSFS <- totalSFS + sfs

#}

barplot(totalSFS[2:(length(totalSFS)-1)])

pdf("sfs.pdf")
barplot(sfs[2:length(sfs)])
dev.off()
