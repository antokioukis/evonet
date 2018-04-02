library(ggplot2)

n<-2000


after <- as.matrix(bonus_gens_open_genes<-read.table("after10.txt"))
#unique(as.integer(which(after > 4.)/15000))
l <- 3
k <- which(after[1,] > l-0.5 & after[1,] < l+0.5)
after <- after[,k]
k
#bonus_generations <- dim(bonus_gens_open_genes)[1]
vafter <- as.vector(after)
xafter <- rep(1:dim(after)[1], dim(after)[2])
col <- rep(1:dim(after)[2], each=dim(after)[1])
dafter <- data.frame(generations=xafter, extragenes=vafter)
pdf("after10.pdf")
p1<-ggplot(dafter, aes(x=generations, y=extragenes)) + geom_point(shape=1, colour=col) + geom_smooth(method=lm)
p2<-p1 + ggtitle("Trajectories of a sample on mean open genes") +theme(plot.title = element_text(hjust = 0.5))
p3<-p2+labs(x = "Generations after reaching target fitness", y="Mean Neutral Open Genes")
show(p3)
dev.off()

#########################################################################################################################
output_data<-read.table("before10.txt")
#final_data<-colMeans(final_data,na.rm=TRUE)
output_data2<-output_data
keep_vec<-c()

keep_vec <- apply(output_data2, 1, function(x) all(is.na(x)))
output_data2 <- output_data2[ !keep_vec, ]


#y <- colMeans(output_data2, na.rm=TRUE)
x <-    differences<-c(0.999,0.99,0.98,0.97,0.96,0.95,0.818731,
                0.753638,0.707222,0.670320,0.639407,0.612689,
                0.589105,0.567971,0.548812,0.531286)
grammes<-c(seq(16,1,-1))
output_data3<-as.matrix(output_data2[,grammes])

means <- apply(output_data3, 2, mean , na.rm=TRUE)
medians <- apply(output_data3, 2, median)

levels <- rev(differences)
xl <- nrow(output_data3)
xlev <- rep(levels, each=xl)
y <- as.vector(output_data3)

num_runs_vec<-c()
for (i in 1:length(differences)){
  count<-0
  for (j in 1:nrow(output_data3)){
    if(!is.na(output_data3[j,i])){
      count<-count+1
    }
  }
  num_runs_vec<-c(num_runs_vec,count)
}
num_runs_vec

data <- data.frame(fitness=xlev, value=y)

data2 <- data.frame(x=levels, y=medians)
data3 <- data.frame(x=levels, y=means)

data4<-data.frame(x=levels, y=num_runs_vec)

diairetis<-n/5

pdf("before10.pdf")
p1 <- ggplot(data, aes(x=fitness, y=value)) + geom_boxplot(aes(group=xlev))
p2 <- p1 #+ geom_point(data2, mapping=aes(x=x, y=y, colour="red"))
p3 <- p2+  geom_point(data3, mapping=aes(x=x, y=y, colour="means"))
p4 <- p3+labs(x = "Mean Generation Fitness", y="Mean Open Genes of Generation")
p5 <- p4 + ggtitle("The push to bigger GRNs") +theme(plot.title = element_text(hjust = 0.5))
p6 <- p5 + geom_point(data4, mapping=aes(x=x, y=y/diairetis, colour="runs"))
#p6 <- scale_y_continuous(sec.axis = sec_axis(~.*20))
p7 <- p6 %+% scale_y_continuous(sec.axis = sec_axis(~ . * diairetis , name = "Number of runs reaching fitness level"), limits = c(0, 5))
print(p7)

dev.off()
