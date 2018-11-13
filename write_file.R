#used for writing genotypes on a file

N = 100
mode =1
genes = 20

matrix1=matrix(nrow=N,ncol=genes, byrow=TRUE)

if(mode == 1 ){
    for (i in 1:(N/2)){                                        #if (i %% 2 == 0)  matrix1[i,]<-rep(10,10,20)
        matrix1[i,1:10]<-rep(11,10)
    	matrix1[i,11:20]<-rep(10,10)
        
                                        #if (i %% 2 == 1) matrix1[i,]<-rep(11,11,20)
                                        #if (i %% 3 == 2) matrix1[i,]<-rep(12,12,20)
    }
}

if( mode == 2){
    lastbitR1 = 1
    lastbitR2 = 1
    av = array(0, genes)
    number = 2
    i = 1
    for(i in 1:(genes/2)){
        an = bitwShiftL(number, i-1)
        av[i] = bitwOr(an, lastbitR1)
        av[i+genes/2] = bitwOr(an, lastbitR2)
    }
    av
    for(i in 1:N){
        matrix1[i,] = av
    }
    matrix1
}

write.table(matrix1, file = "R1R2_input.txt", sep = " ",
            qmethod = "double",col.names = FALSE, row.names=FALSE)



