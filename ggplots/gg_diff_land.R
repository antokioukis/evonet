setwd("/home/pavlos/synology/kioukis/evo4/diff_land")
recomb_data<-read.table("fit_land_recomb.txt")
no_recomb_data<-read.table("fit_land_no_recomb.txt")
data<-no_recomb_data-recomb_data

#how much faster is recombination fitness reaching optimum

library(ggplot2)
library(reshape2)
library(RColorBrewer)
new_bins<-c(0.53,0.54,0.56,0.58,0.61,0.63,0.67,0.7,0.75,0.81,0.95)
generations_total<-c(seq(1,max(data)))
optimal_vec<-c("1111111111","1111100000","1100110011","1010101010")

colnames(data)<-new_bins
df <- melt(data)
df$rowid <- 1:4


g1<-ggplot(df, aes(variable, value, group=factor(rowid))) + geom_line(aes(color=factor(rowid)))
g2<-g1+xlab("Fitness") + ylab("Generations Difference")
g3<-g2 + scale_color_manual(name="Fitness Landscape", 
                        labels = optimal_vec, 
                        values = brewer.pal(n = 5, name = "Set1"))
g3<-g3 + theme(panel.grid.major = element_blank(), panel.grid.minor = element_blank(),
panel.background = element_blank(), axis.line = element_line(colour = "black"))

plot(g3)
setwd("/home/antonios/")
ggsave("diff_land_recomb_comp.pdf")





library(ggplot2)
library(reshape2)
library(RColorBrewer)
no_recomb_data<-read.table("diff_land_no_recomb.tab")
new_bins<-c(0.53,0.54,0.56,0.58,0.61,0.63,0.67,0.7,0.75,0.81,0.95)
generations_total<-c(seq(1,max(no_recomb_data)))
optimal_vec<-c("1111111111","1111100000","1100110011","1010101010")

colnames(data)<-new_bins
df <- melt(no_recomb_data)
df$rowid <- 1:4


g1<-ggplot(df, aes(variable, value, group=factor(rowid))) + geom_line(aes(color=factor(rowid)))
g2<-g1+xlab("Fitness") + ylab("Generations")
g3<-g2 + scale_color_manual(name="Fitness Landscape", 
                        labels = optimal_vec, 
                        values = brewer.pal(n = 5, name = "Set1"))
g3<-g3 + theme(panel.grid.major = element_blank(), panel.grid.minor = element_blank(),
panel.background = element_blank(), axis.line = element_line(colour = "black"))
plot(g3)
setwd("/home/kioukis/")
ggsave("diff_land_no_recomb_pavlos.pdf")