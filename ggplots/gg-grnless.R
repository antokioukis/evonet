library(ggplot2)
library(RColorBrewer)
curDir <- "/home/pavlos/synology/kioukis/evo4/simulations/grnless_small_mr/500selection."
mr_vec <- c(0.05, 0.06, 0.07, 0.08, 0.09, 0.1)
mr_vec_str <- c("0.05", "0.06", "0.07", "0.08", "0.09","0.10")
plot_mr_vec <- rep(mr_vec_str, each=200)
 
grn_vec <- c("No GRN","EvoNET")
plot_grn_vec <- rep(grn_vec, times=600)

times_vec <- character(0)
vec_counter <- 1
#for (i in 1:1){
for (i in 1:length(mr_vec)){
    for (j in 1:100){
        active_dir <- paste(curDir,mr_vec[i],".run.",j,sep="")
        print(active_dir)
        setwd(active_dir)
        evonet_fitness <- read.table("fitnesss.txt")
        grn_less_fitness <- read.table("GRNgenerations.txt")
        evonet_time <- nrow(evonet_fitness)
        fitness_simple_time <- grn_less_fitness[1]
        if(fitness_simple_time > 10000){
            #times_vec[vec_counter] <- 10000
            times_vec[vec_counter] <- fitness_simple_time
        }
        else{
            times_vec[vec_counter] <- fitness_simple_time
        }        
        vec_counter <- vec_counter + 1 
        times_vec[vec_counter] <- evonet_time * 10 #10 genies frequency sta simulations tou evonet
        vec_counter <- vec_counter + 1
    }
}

#https://www.r-graph-gallery.com/265-grouped-boxplot-with-ggplot2/^B

#dataframe 3 kolwnes prwti to mutation rate ka8e run
#deuteri to apo pou proerxetai? evonet h fitnessSImple
#triti to poso tou pire gia na ftasei to optimum
data <- data.frame(plot_mr_vec,plot_grn_vec,"times"=log(unlist(as.list(times_vec))))

g1 <- ggplot(data, aes(x=plot_mr_vec, y=times, fill=plot_grn_vec)) + geom_boxplot()
g2 <- g1 + scale_fill_manual(values=c("white", "gray"))
g3 <- g2 + theme(panel.grid.major = element_blank(), panel.grid.minor = element_blank(),
    panel.background = element_blank(), axis.line = element_line(colour = "black"))
g4 <- g3 + xlab("Mutation Rate") + ylab("Generations (log scale)")
g5 <- g4 + labs(fill="GRN presence")

plot(g5)

setwd("/home/pavlos/synology/kioukis/evo4/ggplots/")
ggsave("grnless1.pdf")

