library(ggplot2)
library(reshape2)
library(RColorBrewer)
mr_vec<-c(0.05,0.1,0.15,0.20,0.25)
new_bins<-c(0.54,0.56,0.58,0.61,0.63,0.67,0.7,0.75,0.81,0.95)
generations_total<-c(seq(1,max(mr_diff_mat)))


df <- melt(mr_diff_mat)
df$rowid <- 1:5


g1<-ggplot(df, aes(Var2, value, group=factor(rowid))) + geom_line(aes(color=factor(rowid)))
g2<-g1+xlab("Fitness Step") + ylab("Generations")
g3<-g2 + scale_color_manual(name="Mutation Rate", 
                        labels = mr_vec, 
                        values = brewer.pal(n = 5, name = "Set1"))
g3<-g3 + theme(panel.grid.major = element_blank(), panel.grid.minor = element_blank(),
panel.background = element_blank(), axis.line = element_line(colour = "black"))

plot(g3)
setwd("/home/kioukis/")
ggsave("mut_rate.pdf")




recomb_rate_parse<-function(rr_vec,bins,n){
    ave_ti_rr<-matrix(nrow=length(rr_vec),ncol=length(bins))
    for (l in 1:length(rr_vec)){
        fitness_time<-matrix(nrow=n,ncol=length(bins))
        curDir <- paste("/home/kioukis/brassica_cretica/evo3/data_rr/500selection1rr",rr_vec[l],"mr0.05.run.",sep="")
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
                    fitness_time[i,j]<-nrow(fitness)
                }
                else{
                    fitness_time[i,j]<-find_index
                }
            }

        }
        #average time gia auto to mutation rate
        ave_rr<-colMeans(fitness_time)
        ave_ti_rr[l,]<-ave_rr
    }
    return(ave_ti_rr)
}

calc_step_size<-function(input_mat){
    diff_size<-length(bins)-1
    diff_mat<-matrix(nrow=length(rr_vec),ncol=diff_size)
    for (i in 1:nrow(diff_mat)){
        #print (i)
        for (j in 1:ncol(diff_mat)){
            #print(j)
            #print(input_mat[i,j])
            diff_mat[i,j]<-input_mat[i,j+1]-input_mat[i,j]
        }
    }
    return(diff_mat)
}

n<-100
bins<-c(0.53,0.54,0.56,0.58,0.61,0.63,0.67,0.7,0.75,0.81,0.95)
rr_vec<-c(0.05,0.1,0.15,0.20,0.25)

ave_ti_rr<-recomb_rate_parse(rr_vec,bins,n)
ave_ti_rr<-10*ave_ti_rr
rr_diff_mat<-calc_step_size(ave_ti_rr)



library(ggplot2)
library(reshape2)
library(RColorBrewer)
generations_total<-c(seq(1,max(mr_diff_mat)))


df <- melt(rr_diff_mat)
df$rowid <- 1:5

ggplot(data=df, aes(x=time, y=value, group=variable)) + geom_line()

g1<-ggplot(df, aes(Var2, value, group=factor(rowid))) + geom_line(aes(color=factor(rowid)))
g2<-g1+xlab("Fitness Step") + ylab("Generations")
g3<-g2 + scale_color_manual(name="Recombination Rate", 
                        labels = rr_vec, 
                        values = brewer.pal(n = 5, name = "Set1"))
g3<-g3 + theme(panel.grid.major = element_blank(), panel.grid.minor = element_blank(),
panel.background = element_blank(), axis.line = element_line(colour = "black"))

plot(g3)
setwd("/home/kioukis/")
ggsave("rec_rate.pdf")
