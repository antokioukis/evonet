curDir=`pwd`
for i in `seq 35`;do 
    cd run$i
    tail -1000 neutralOutput.txt > neutralOutputLastGen.txt
    cd $curDir
done
