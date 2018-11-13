fitness_parse<-function(optimum_vec,bins,n){
    fit_mat<-matrix(nrow=length(optimum_vec),ncol=length(bins))
    for (l in 1:length(optimum_vec)){
        fitness_time<-matrix(nrow=n,ncol=length(bins))
        curDir <- paste("/home/antonios/evo4/500selection",optimum_vec[l],"mr.run.",sep="")
        #curDir <- paste("/home/pavlos/synology/kioukis/evo4/diff_land/500selection",optimum_vec[l],".run.",sep="")
        for (i in 1:n){
            dirName <- paste(curDir, i, sep="")
            #print(dirName)
            setwd(dirName)
            find_index<-1
            fitness<-read.table("fitnesss.txt")
            #gia ka8e bin
            for (j in 1:length(bins)){
                search_for<-bins[j]
                find_index<-min(which(fitness[,4]>search_for))
                if(!is.finite(find_index)){
                    fitness_time[i,j]<-nrow(fitness)*10
                }
                else{
                    fitness_time[i,j]<-find_index*10
                }
            }

        }
        print(colMeans(fitness_time))
        print(l)
        fit_mat[l,]<-colMeans(fitness_time)
    }
    return(fit_mat)
}

bins<-c(0.53,0.54,0.56,0.58,0.61,0.63,0.67,0.7,0.75,0.81,0.95)
optimal_vec<-c("1111111111","1111100000","1100110011","1010101010")
n<-100


b<-4 # Or some other number
a<-sapply(bins, function (x) rep(x,b))
a<-as.vector(a)

fitmat1<-fitness_parse(optimal_vec,bins,n)
print(fitmat1)

setwd("/home/antonios")
library(ggplot2)
library(reshape2)
library(RColorBrewer)
generations_total<-c(seq(1,max(fitmat1)))
df <- as.data.frame(melt(fitmat1))
df$Var2<-a

g1<-ggplot(data=df, aes(x=df$Var2, y=value,group=df$Var1)) + geom_line(aes(color=factor(df$Var1)))
g2<-g1+xlab("Fitness") + ylab("Generations")+ scale_color_manual(name="Fitness Landscape", 
                        labels = optimal_vec, 
                        values = brewer.pal(n = 4, name = "Set1"))
g3<-g2 + theme(panel.grid.major = element_blank(), panel.grid.minor = element_blank(),
panel.background = element_blank(), axis.line = element_line(colour = "black"))
g4<-g3+scale_x_continuous(limits =c(0.53,0.95))
plot(g4)
ggsave("fit_land_no_recomb.pdf")