#png(filename="test.png")
#plot(x=1:5, y=rep(5,5), pch=19, cex=12, col=rgb(.25, .5, .3), xlim=c(0,6))  
#dev.off()

mydata = read.delim2('genotype.txt',header=TRUE,fill=TRUE)
png(filename="test.png")
plot(x=0:mydata[1,], y=rep(0,length(mydata[1,])), pch=19, cex=50, col="red", xlim=c(0,6))
plot(x=mydata[1,]:mydata[2,], y=rep(length(mydata[1,]),length(mydata[2,])), pch=19, cex=50, col="black", xlim=c(0,6))