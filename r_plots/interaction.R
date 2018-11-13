library(foreach)
library(doMC)
registerDoMC(10)

curDir <- ("~/Dropbox/sxoli/ptixiaki/evo3")

n<-25

foreach(i = 1:n) %dopar% {

	dirName <- paste(curDir,"/selection.run.", i, sep="")
	setwd(dirName)

	mydata<-read.table("matrix.txt")
	topo_matrix<-matrix(nrow=nrow(mydata),ncol=1)

	#allagi tou matrix gia tin dimiourgia boolean network
	mydata[mydata < 0] <- -1
	mydata[mydata > 0] <-  1
	mydata[mydata == 0] <-  0

	#print(mydata[10000,])

	#creation of topology matrix
	for (j in 1:nrow(mydata)){
		concatenation<-apply(mydata[j,], 1, paste, collapse="")
		#print(concatenation)
		topo_matrix[j]<-concatenation
	}
	#topo_matrix<-apply(mydata, 1, paste, collapse="")
	#topo_matrix<-mydata
	#print(head(topo_matrix))
	#print(nrow(topo_matrix))

	#oi dio autes entoles exoun to idio apotelesma
	num_of_gens<-nrow(topo_matrix)/500
	num_of_gens<-length(topo_matrix)/500

	generation<-matrix(nrow=500,ncol=1)
	survival_mat<-matrix(nrow=num_of_gens,ncol=500)
	#gia ka8e genia
	for (l in 1:num_of_gens){
		katw_orio1<-((l-1)*500)+1
		panw_orio1<-l*500
	

		generation<-topo_matrix[katw_orio1:panw_orio1]

		generation<-topo_matrix[((l-1)*500+1):(l*500)]
		#print(head(generation))
		#gia ka8e gonotupo autis tis genias
		for (k in 1:500){
			counter<-0
			topology<-generation[k]
			#gia oles tis ipoloipes genies
			for (m in l:num_of_gens){
				katw_orio2<-((m-1)*500)+1
				panw_orio2<-m*500
				next_generation<-topo_matrix[katw_orio2:panw_orio2]
				if(topology %in% next_generation){
					counter<-counter+1
					next
				}
				else{
					survival_mat[l,k]<-counter
					#print(counter)
				}
			}
		}
	}
	#final<-survival_mat[complete.cases(survival_mat),]
	final<-survival_mat[rowSums(is.na(survival_mat)) != ncol(survival_mat),]
	last <- apply(final, 1, function(x) { mean(x, na.rm=TRUE) })

    setwd("~/Dropbox/sxoli/ptixiaki/evo3")
	png(paste("selection",sprintf("%04d", i),".png",sep=""))
    plot(last, type="l",main = "Topology Robustness",xlab="Generations",ylab="Generations Survived")
    dev.off()
}

curDir <- ("~/Dropbox/sxoli/ptixiaki/evo3")

n<-25
foreach(i = 1:n) %dopar% {

	dirName <- paste(curDir,"/neutral.run.", i, sep="")
	setwd(dirName)

	mydata<-read.table("matrix.txt")
	topo_matrix<-matrix(nrow=nrow(mydata),ncol=1)

	#allagi tou matrix gia tin dimiourgia boolean network
	mydata[mydata < 0] <- -1
	mydata[mydata > 0] <-  1
	mydata[mydata == 0] <-  0

	#print(mydata[10000,])

	#creation of topology matrix
	for (j in 1:nrow(mydata)){
		concatenation<-apply(mydata[j,], 1, paste, collapse="")
		#print(concatenation)
		topo_matrix[j]<-concatenation
	}
	#topo_matrix<-apply(mydata, 1, paste, collapse="")
	#topo_matrix<-mydata
	#print(head(topo_matrix))
	#print(nrow(topo_matrix))
	num_of_gens<-nrow(topo_matrix)/500
	
	generation<-matrix(nrow=500,ncol=1)
	survival_mat<-matrix(nrow=num_of_gens,ncol=500)
	#gia ka8e genia
	for (l in 1:num_of_gens-1){
		katw_orio1<-((l-1)*500)+1
		panw_orio1<-l*500
		#print(katw_orio)
		#print(panw_orio)
		generation<-topo_matrix[katw_orio1:panw_orio1]
		#print(head(generation))
		#gia ka8e gonotupo autis tis genias
		for (k in 1:499){
			counter<-0
			topology<-generation[k]
			#gia oles tis ipoloipes genies
			for (m in l:num_of_gens-1){
				katw_orio2<-((m-1)*500)+1
				panw_orio2<-m*500
				next_generation<-topo_matrix[katw_orio2:panw_orio2]
				if(topology %in% next_generation){
					counter<-counter+1
					next
				}
				else{
					survival_mat[l,k]<-counter
					#print(counter)
				}
			}
		}
	}
	#final<-survival_mat[complete.cases(survival_mat),]
	final<-survival_mat[rowSums(is.na(survival_mat)) != ncol(survival_mat),]
	last <- apply(final, 1, function(x) { mean(x, na.rm=TRUE) })
	
    setwd("~/Dropbox/sxoli/ptixiaki/evo3")
	png(paste("neutral",sprintf("%04d", i),".png",sep=""))
    plot(last, type="l",main = "Topology Robustness",xlab="Generations",ylab="Generations Survived")
    dev.off()
}

system("convert neutral*.png neutral_interaction.pdf")
system("rm neutral*.png")

system("convert selection*.png selection_interaction.pdf")
system("rm selection*.png")