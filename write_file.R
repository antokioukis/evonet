#used for writing genotypes on a file

matrix1=matrix(nrow=1000,ncol=20,byrow=TRUE)

for (i in 1:500){
	#if (i %% 2 == 0)  matrix1[i,]<-rep(10,10,20)
    matrix1[i,1:10]<-rep(10,10)
    matrix1[i,11:15]<-rep(11,5)
    matrix1[i,16:20]<-rep(10,5)


	#if (i %% 2 == 1) matrix1[i,]<-rep(11,11,20)
	#if (i %% 3 == 2) matrix1[i,]<-rep(12,12,20)

}

for (i in 501:1000){
	#if (i %% 2 == 0)  matrix1[i,]<-rep(10,10,20)
    matrix1[i,1:10]<-rep(10,10)
    matrix1[i,11:20]<-rep(11,10)
	#if (i %% 2 == 1) matrix1[i,]<-rep(11,11,20)
	#if (i %% 3 == 2) matrix1[i,]<-rep(12,12,20)

}

write.table(matrix1, file = "R1R2_input.txt", sep = " ",
            qmethod = "double",col.names = FALSE, row.names=FALSE)
