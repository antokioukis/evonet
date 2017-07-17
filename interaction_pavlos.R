curDir <- ("~/Dropbox/sxoli/ptixiaki/evo3")

n<-1
i <- 1

for (i in 1:n){

    dirName <- paste(curDir,"/selection.run.", i, sep="")
	setwd(dirName)

    mydata<-read.table("matrix.txt")
    dim(mydata)
    topo_matrix<-matrix(nrow=nrow(mydata),ncol=1)

	#allagi tou matrix gia tin dimiourgia boolean network
	mydata[mydata < 0] <- -1
	mydata[mydata > 0] <-  1
	mydata[mydata == 0] <-  0

	#print(mydata[10000,])

	#creation of topology matrix
	#for (j in 1:nrow(mydata)){
	#	concatenation<-apply(mydata[j,], 1, paste, collapse="")
		#print(concatenation)
	#	topo_matrix[j]<-concatenation
	#}
    topo_matrix<-apply(mydata, 1, paste, collapse="")
    ##nrow(topo_matrix)
    ##length(topo_matrix)
	#print(head(topo_matrix))
    num_of_gens<-nrow(topo_matrix)/500 ## BUG
    num_of_gens<-length(topo_matrix)/500 
	
	survival_mat<-matrix(nrow=num_of_gens,ncol=500)
	#gia ka8e genia
	for (l in 1:num_of_gens){
            ##generation<-topo_matrix[(l-1)*500:l*500] ##BUG
            normal_generation<-topo_matrix[((l-1)*500+1):(l*500)]

		#gia ka8e gonotupo autis tis genias
		for (k in 1:500){
			counter<-0
			topology<-generation[k]
                                        #gia oles tis ipoloipes genies
			for (m in l:num_of_gens){
                            next_generation<-topo_matrix[((m-1)*500+1):(m*500)] ## BUG
                            if(topology %in% next_generation){
                                counter<-counter+1
                                next
                            }
                            else{
                                survival_mat[l,k]<-counter ## BUG, you don't know if the genotype at k is the same
                                print(counter)
                                break
                                
                            }
			}
		}
	}
    print(head(survival_mat))
}

dim(survival_mat)
