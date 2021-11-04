#John Parkhurst
#10/29/21
#Recorder asks users for command then put in list
#Then print list to file
#Default Value
myArr=()
while true
do
  echo "Please enter a command:"
  read comm
  #If not redirect
  if [[ "$comm" =~ .*">".* ]];
   then
      #Exit cond
      echo "Invalid Command Redirects to File"
    else
      #now check if valid command
      if type $comm &> /dev/null
      then
        $comm
        #ask to record command, discard it, stop record
        echo "Press 1 to record, 2 to discard, 3 to stop"
        read choice
        #If statement for choice
        if test $choice == 1
        then
          #record
          myArr+=($comm)
          #echo "$comm" >> $fileName
        elif test $choice == 2
        then
          echo "Discarded"
        elif test $choice == 3
        then
          echo "What would you like to save the file as?"
          read fileName
          #OUTPUT LIST TO FILENAME
          echo ${myArr[@]} > $fileName
          exit
        fi
      else
        echo "Invalid Command"
      fi
  fi
done
exit

