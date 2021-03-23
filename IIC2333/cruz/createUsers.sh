#!/bin/bash

if [[ $# -lt 1 ]];
then
  echo "Usage: $0 logins_file"
fi

FILENAME=$1

echo "Reading users from $1 ..."

while read line
do
  #echo "Read line $line"
  LOGIN=`echo $line | cut -f 1 -d " "`
  PASSW=`echo $line | cut -f 2 -d " "`
  GROUP=`echo $line | cut -f 3 -d " "`
  NAME1=`echo $line | cut -f 2 -d "\""`
  NAME2=`echo $line | cut -f 4 -d "\""`
  NAME="$NAME1 $NAME2"
  #echo "[$LOGIN],[$PASSW],[$GROUP],[$NAME1],[$NAME2],[$NAME]"
  echo "--> Creating user $LOGIN ($NAME) in group $GROUP"
  RUN="adduser --home /user/$LOGIN --ingroup $GROUP --disabled-password --gecos \"$NAME,,,\" $LOGIN"
  #echo "[$RUN]"
  adduser --home /user/$LOGIN --ingroup $GROUP --disabled-password --gecos "$NAME,,," $LOGIN
  echo "Setting password for $LOGIN"
  RUN="echo -e \"$PASSW\n$PASSW\n\" | passwd -q $LOGIN"
  #echo "[$RUN]"
  echo -e "$PASSW\n$PASSW\n" | passwd -q $LOGIN
done < $1

echo "Done!"

