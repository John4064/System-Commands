#John Parkhurst
#11/5/21
#This just builds our three Executables
rm ./Output/*.out
gcc prog03_v1.c -o prog03_v1
gcc prog03_v2.c -o prog03_v2
gcc prog03_v3.c -o prog03_v3
echo "Built"