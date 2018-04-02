#args = commandArgs(trailingOnly=TRUE)

ss <- 20


#population
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


create_sfs<-function(name,pop_size){
    N<-pop_size

    totalSFS <- array(0, N+1)

    fdirName <- name
    outputName <- name

    for(i in 1:n){
        
        #dirName <- paste(name, ".run.", i, sep="")

        dirName <- paste(curDir,"/",fdirName,".run.", i, sep="")
        #setwd(dirName)

        currInput<-paste(dirName, "/neutralOutput000.txt", sep="")
        print(currInput)
        
        a <- read.table(currInput, colClasses="character")
        b <- matrix(as.numeric(unlist(strsplit(x=a[,2], split=''))), ncol=l, byrow=TRUE)
        rowstoconsider <-sample((nrow(b)-N+1):nrow(b),ss)
        d <- b[ rowstoconsider, ]
        sumd <- apply(d,2,sum)
        sfs <- makeSFS(sumd, ss)
        totalSFS <- totalSFS + sfs
    }
    pdf(paste(name,".pdf",sep=""))
    barplot(totalSFS[2:(length(totalSFS)-1)])
    dev.off()
}


curDir <- ("~/Dropbox/sxoli/ptixiaki/evo3")

rr_vec<-c(0,0.0001,0.001,0.005,0.01,0.05,0.1)
#population
#N_vec<-c(200,500,1000)
swapp_vec<-c(1,2)
N_vec<-c(500,1000)
n<-20


for(i in 1:1){ #2
    swapp<-swapp_vec[i]
    for(j in 1:1){ #2
        N<-N_vec[j]
        for (k in 1:1){ #7
            rr<-rr_vec[k]
            dirName<-paste(N,"selection",swapp,"rr",rr,sep="")
            print(dirName)
            create_sfs(dirName,N)
        }
    }
}
