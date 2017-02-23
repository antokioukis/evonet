mutations_matrix<-read.table("father_fitness.txt",sep=" ")

beneficials<-matrix(nrow=nrow(mutations_matrix),ncol=5)
beneficials_thesi<-0

deleterious<-matrix(nrow=nrow(mutations_matrix),ncol=5)
deleterious_thesi<-0

beneficial_final<-matrix(nrow=nrow(mutations_matrix),ncol=5)


for (i in 1:nrow(mutations_matrix)){
	if(mutations_matrix[i,2]-mutations_matrix[i,3]<0){
		beneficials[beneficials_thesi,1]<-mutations_matrix[i,1]
		beneficials[beneficials_thesi,2]<-mutations_matrix[i,2]
		beneficials[beneficials_thesi,3]<-mutations_matrix[i,3]
		beneficials[beneficials_thesi,4]<-mutations_matrix[i,4]
		beneficials[beneficials_thesi,5]<-mutations_matrix[i,5]
		beneficials_thesi<-beneficials_thesi+1
	}
	else{
		deleterious[deleterious_thesi,1]<-mutations_matrix[i,1]
		deleterious[deleterious_thesi,2]<-mutations_matrix[i,2]
		deleterious[deleterious_thesi,3]<-mutations_matrix[i,3]
		deleterious[deleterious_thesi,4]<-mutations_matrix[i,4]
		deleterious[deleterious_thesi,5]<-mutations_matrix[i,5]
		deleterious_thesi<-deleterious_thesi+1
	}
}

beneficials <- beneficials[!is.na(beneficials[,1]),]
deleterious <- deleterious[!is.na(deleterious[,1]),]

#remove first column the number of generation gia na pai3ei to unique meta
beneficial_temp<-beneficials[,-1]
#beneficial_temp<-unique(beneficial_temp)
beneficial_temp<-beneficial_temp[order(beneficial_temp[,1],beneficial_temp[,2],beneficial_temp[,3]),]

counter=0
for (i in 1:nrow(beneficial_temp)){
	for (j in 1:nrow(beneficial_temp)){
		if (beneficial_temp[i,1]==beneficial_temp[j,1] && beneficial_temp[i,2]==beneficial_temp[j,2] && beneficial_temp[i,3]==beneficial_temp[j,3] && beneficial_temp[i,4]==beneficial_temp[j,4]){
			counter=counter+1
		}
	}
	beneficial_final[i,1]<-beneficial_temp[i,1]
	beneficial_final[i,2]<-beneficial_temp[i,2]
	beneficial_final[i,3]<-beneficial_temp[i,3]
	beneficial_final[i,4]<-beneficial_temp[i,4]
	beneficial_final[i,5]<-counter
	counter=0
}


beneficial_final<-beneficial_final[complete.cases(beneficial_final),]

deleterious_temp<-deleterious[,-1]
deleterious_temp<-unique(deleterious_temp)
deleterious_temp<-deleterious_temp[order(deleterious_temp[,1],deleterious_temp[,2],deleterious_temp[,3]),]

#allFitnesses <- unique(c(deleterious_temp[,1], deleterious_temp[,2], beneficial_temp[,1], beneficial_temp[,2]))
#print(allFitnesses)

#column 2: fitness before mutation
#column 3: fitness after mutation
#column 4:number of mutations occurred
#column 5: genotype of father


print("Beneficials")
beneficial_final
#print("Deleterious")
#deleterious_temp
