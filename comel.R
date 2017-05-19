


name="neutral"

getcommon = function(name1, name2){
    allData1 = list()
    allData2 = list()
    arc1 = list.files(path=name1, pattern = "\\.*allNames.RData")
    arc2 = list.files(path=name2, pattern = "\\.*allNames.RData")    

    i = 0
    for(f in arc1){
        i = i + 1
        load(file=paste(name1, "/",f, sep=""))
        allData1[[i]] = allNames    
    }

    i = 0
    for(f in arc2){
        i = i + 1
        load(file=paste(name2, "/",f, sep=""))
        allData2[[i]] = allNames    
    }

    common = matrix(0, nrow=length(arc), ncol=length(arc))
    
    for(i in 1:length(arc1)){
        for(j in 1:length(arc2)){
            common[i,j] = length(intersect(allData1[[i]], allData2[[j]]))
        }
    }

    common
}

getcommon("neutral", "neutral")
getcommon("neutral", "selection")
getcommon("selection", "selection")
