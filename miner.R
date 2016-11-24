###########################################################################################
interaction<-as.data.frame(read.table("/home/antonios/Dropbox/sxoli/ptixiaki/evo3/matrix.txt"))

out_matrix = matrix(nrow=10,ncol=10) # ka8eta ta gonidia orizontia pws e3elissontai ston xrono
in_matrix = matrix(nrow=10,ncol=10) # ka8eta ta gonidia orizontia pws e3elissontai ston xrono

outdegree<-function(n){
	for (i in 1:10){ #10 sto final loop
  		range3=(i*10000)+1
  		range4=(i*10000)+10000
  		generation<-interaction[range3:range4,]
  		#to 1 edw einai gia to prwto gonidio
  		gene<-generation[seq(n,10000, by=10 ),]
  		average_out_degree=mean(10-rowSums(gene==0.0))
  		#print(average_out_degree)
  		out_matrix[n,i]<-average_out_degree
	}
	return(out_matrix)
}

indegree<-function(n){
	for (i in 1:10){ #10 sto final loop
  		range3=(i*10000)+1
  		range4=(i*10000)+10000
  		generation<-interaction[range3:range4,]
  		#to 1 edw einai gia to prwto gonidio
  		#gene<-generation[,seq(n,10000, by=10 )]
  		gene<-generation[,n]
  		average_in_degree=mean(10-colSums(gene==0.0))
  		#print(average_out_degree)
  		in_matrix[n,i]<-average_in_degree
	}
	return(in_matrix)
}

for (i in 1:10){
	out_matrix<-outdegree(i)
	#in_matrix<-indegree(i)
}

print(out_matrix)
#print(in_matrix)
print(rowMeans(out_matrix, na.rm = FALSE, dims = 1))
#print(rowMeans(in_matrix, na.rm = FALSE, dims = 1))