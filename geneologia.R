general<-as.matrix(read.table("father.txt",sep=" "))

ari8mos_grammwn<-nrow(general)

telikos=matrix(nrow=ari8mos_grammwn,ncol=1000)

active_line=unlist(general[2,])
previous_line=unlist(general[1,])


for(j in 1:1000){
		value<-as.numeric(previous_line[active_line[j]])
		if (identical(value, numeric(0))){
			telikos[1,j]<-1
		}
		else{
			#if(!(value %in% telikos[1,])){
				telikos[1,j]<-value
			#}
		}
	}
#for(i in ari8mos_grammwn:2){
#	active_line=unlist(general[i,])
#	previous_line=unlist(general[i-1,])
	#for(j in 1:1000){
		#print(as.numeric(active_line[j]))
		#print(as.numeric(previous_line[active_line[j]]))
	#	telikos[1,j]<-as.numeric(previous_line[active_line[j]])
	#}
#}

for(i in 2:ari8mos_grammwn){
	previous_line=unlist(general[i,])
	#print((previous_line[telikos[1,83]]))
	for(j in 1:1000){
		value<-as.numeric(previous_line[telikos[i-1,j]])

		if (identical(value, numeric(0))){
			telikos[i,j]<-1
		}
		else{
			#if(!(value %in% telikos[i,])){
				telikos[i,j]<-value
			#}
		}
	}
}

j<-1
for(i in 1:1000){
	value<-telikos[j,i]
	if (identical(value, numeric(0))){
		value<-1
	}
	while(!is.na(value)){
		cat(value)
		cat("--->")
		if(j>699){
			break
		}
		value<-telikos[j+1,value]
		if (identical(value, numeric(0))){
			value<-1
		}
		j=j+1
	}
	j<-1
	print(" ")
}