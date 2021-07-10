for file in file1.txt file2.txt file3.txt file4.txt
do 
    echo "Step2 $file"
    time ./9-step2 $file
    echo " "
done

