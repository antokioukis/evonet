curDir<-getwd()
rr_vec<-c(0,0.0001,0.001,0.005,0.01,0.05,0.1)

ave_pop_size1<-c()
ave_pop_size2<-c()
ave_pop_size3<-c()
ave_pop_size4<-c()

ave_pop<-function(pop_size,flag){
	ave_pop_size<-c()
	for (k in 1:length(rr_vec)){ #7
	    rr<-rr_vec[k]
	    ave_first<-c()
	    for (l in 1:25){
	        dir_name<-paste(curDir,"/",pop_size,"selection",flag,"rr",rr,".run.",l,sep="")
	        print(dir_name)
	        setwd(dir_name)
	        my_table<-read.table("fitnesss.txt")
	        ave_first[l]<-nrow(my_table)
	        setwd(curDir)
	    }
	    ave_pop_size[k]<-mean(ave_first)
	}
	return(ave_pop_size)
}


ave_pop_size1<-ave_pop(200,1)
ave_pop_size2<-ave_pop(200,0)
ave_pop_size3<-ave_pop(500,1)
ave_pop_size4<-ave_pop(500,0)

print(ave_pop_size2)
setwd(curDir)
pdf("recomb_pop_size2.pdf")
plot(ave_pop_size1,xaxt = "n", lty=1,xlab='Recombination Rate',ylim=c(1000,4000) ,ylab="Generations for Optimum",main="Effect of Recombination Rate on Models", type="l",col="black")
lines(ave_pop_size2,lty=5,col="black")
lines(ave_pop_size3,lty=1,col="red")
lines(ave_pop_size4,lty=5,col="red")

legend("topleft",c("Row","R1R2"),title="Swapping Model",lty=c(1,5),lwd=c(2.5,2.5),col=c("black","black"))

legend("topright",c("200","500"),title="Population Size",lty=c(1,1),lwd=c(2.5,2.5),col=c("black","red"))

axis(1, at=1:length(rr_vec), labels=rr_vec)
dev.off()