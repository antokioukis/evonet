rm(list=ls())
library(igraph)
N = 100

mod <- "selection"
run <- 1

options(echo=TRUE) # if you want see commands in output file
args <- commandArgs(trailingOnly = TRUE)
if(length(args) > 1){
    mod <-  args[1]
    run <- args[2]
}

dir <- paste(mod, "/run", run, sep="")
a = read.table(paste(dir, "/matrix.txt", sep=""))
k <- dim(a)[1]/N
k
b = read.table((paste(dir, "/discrete.txt", sep="")), colClasses = "character")
fit = as.numeric(read.table((paste(dir, "/fitnesss.txt", sep="")))[,4])

avexp = function(m){
    v = matrix(as.numeric(unlist(sapply(m, strsplit, ''))), nrow=N, byrow=TRUE)
    apply(v, 2, mean)
}

avmat = function(m){
    v = apply(m, 2, mean)
    matrix(v, nrow=sqrt(length(v)), byrow=TRUE)
}

ms <- abs(unlist(lapply(1:k, function(i){ avmat(a[((i-1)*N +1):(i*N),]) })))
msl <- lapply(1:k, function(i){ avmat(a[((i-1)*N +1):(i*N),]) })

mina <- min(ms[ms!=0])
maxa <- max(ms)
mina
maxa
tamin <- 1
tamax <- 20


avexpression = list()
graphs = list()
weights = list()
j = 1
for(i in 1:k){
    avexpression[[i]] <- avexp(b[((i-1)*N +1):(i*N),])
    cc <- msl[[i]]/maxa * (tamax - tamin) + tamin
    cc[cc==1] <-  0
    m <- cc
    graphs[[j]] = graph.adjacency(t(m), mode="directed", weighted=TRUE)
    weights[[j]] <- E(graphs[[j]])$weight
    l <-layout.auto(graphs[[j]])
    j <- j + 1
    print(j)
    ##plot.igraph(g, layout=l)
}


expmat <- matrix(unlist(avexpression), ncol=10, byrow=TRUE)

E(graphs[[2000]])$weight
graphs[[1]]
weights[[1]]


png(paste(dir, "/plot%06d.png", sep=""))
for(i in 1:length(graphs)){
    print(i)
    #i<-1
    ##E(graphs[[i]])$weight <- weights[[i]]
    edge.weights <- weights[[i]]
    edge.color <- array("blue", dim=length(weights[[i]]) )
    edge.color[edge.weights > 0] <- "blue"
    edge.color[edge.weights < 0] <- "red"
    V(graphs[[i]])$color <- sapply(expmat[i,], gray)
    E(graphs[[i]])$color <- edge.color
    if(is.null(edge.weights))
        plot.igraph(graphs[[i]], layout=l, main=paste("i:", i, " fitness:", fit[i], " meanExp:", mean(expmat[i,]), sep="") )
    else
        {
            ##E(graphs[[i]])$weight <- abs(E(graphs[[i]])$weight)
            ##E(weights(graphs[[i]]) <- edge.betweenness(graphs[[i]])
            plot.igraph(graphs[[i]], layout=l, edge.width=abs(weights[[i]]), , main=paste("i:", i, " fitness:", fit[i], " mean.exp:", mean(expmat[i,]), sep="") )
        }
}
dev.off()




#convert test.gif -fuzz 30% -layers Optimize result.gif
make.mov <- function(){
    name <- paste(mod, "_run", run, "_", "plot.gif", sep="")
    unlink(name)
    system(paste("convert -fuzz 30% -layers Optimize -delay 5 ", dir, "/plot*.png ", name, sep=""))
}

make.mov()
