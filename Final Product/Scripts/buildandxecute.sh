#John Parkhurst
#10.27.21

#Remeber $# number of arguments
#$n ex. $1 is out to access arguments
#if $1 contains a command we can execute it
if test ! -d $1
then
  echo "Could not find Output Directory"
  echo "Creating..."
  mkdir ./Output
fi
MYPATH=""
for var in "$@"
do
    #Check that it isnt the output directory
    if test ! -d $var
    then
      #If The file exists then append to path
      if test -f $var
      then
        MYPATH+="$var "
      fi
    fi
done
gcc ../Programs/prog03_v1.c -o prog03_v1
gcc ../Programs/prog03_v2.c -o prog03_v2
gcc ../Programs/prog03_v3.c -o prog03_v3
#../Programs/prog03_v1.c $1 $MYPATH
#../Programs/prog03_v2.c $1 $MYPATH
#../Programs/prog03_v3.c $1 $MYPATH
echo "done"
#Tee or >
