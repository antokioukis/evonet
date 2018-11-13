library(statnet)

curDir <- ("~/Dropbox/sxoli/ptixiaki/evo3/selection.run.1")
N<-100
setwd(curDir)
library(statnet)
data<-read.table("discrete.txt")

#print (dim(data))
num_nodes <- 10
bracket<-N
orio<-nrow(data)/N
#print (dim(data))
my_data <- matrix(NA, nrow = N, ncol = 10)
#print (dim(my_data))

my_sociomatrix <- matrix(round(runif(num_nodes*num_nodes)), # edge values
                         nrow = num_nodes, #nrow must be same as ncol
                         ncol = num_nodes)

diag(my_sociomatrix) <- 0
sizes<-c()

net <- as.network(x = my_sociomatrix, # the network object
                  directed = TRUE, # specify whether the network is directed
                  loops = FALSE, # do we allow self ties (should not allow them)
                  matrix.type = "adjacency" # the type of input
                  )

network.vertex.names(net) <- LETTERS[1:10]


for (i in 1:orio){
	katw_orio<-(i-1)*bracket
	panw_orio<-(i-1)*bracket+bracket
	selected_rows<-c(katw_orio:panw_orio)
	
	my_row <- data[selected_rows,]
	my_row <- as.numeric(as.character(my_row))

	for (j in 1:N){
		temp<-my_row[j]
		for (k in 1:10){
		#	print (temp)
			ipoloipo<-temp%%10
			piliko<-temp/10
			my_data[[j,k]]<-ipoloipo
			temp<-sprintf("%.0f", piliko)
			temp<-as.numeric(temp)
		}
	}
	#print (dim(my_data))

	sizes<-colSums(my_data, na.rm = FALSE, dims = 1)
	sizes<-sizes/10

	set.vertex.attribute(net,"sizes",sizes)
	set.seed(12345)


	png(file=paste(sprintf("%04d", i),".png",sep=""), width=1024, height=768)
	plot.network(net, # our network object
             #vertex.col = node_colors, # color nodes by gender
             vertex.cex = sizes, # size nodes by their age
             displaylabels = T, # show the node names
             label.pos = 5 # display the names directly over nodes
             )
	dev.off()

}

system("convert -delay 10 *.png example_1.gif")
file.remove(list.files(pattern=".png"))
