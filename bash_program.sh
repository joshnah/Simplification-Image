#! /bin/bash

if [ $# -lt 2 ];
then
  printf "USAGE: 	./bash_program.sh <nom_du_fichier> <les distance_seuils>\n"
  exit 0
  fi

name=$1 
shift
while [ -n "$1" ]; do
  printf "\n"
  echo Distance: $1
  printf "\n"
  ./bezier_3 $name $1
  printf "\n**************************\n"
  ./bezier_2 $name $1
  printf "\n**************************\n"
  ./tache6 $name $1
  printf "\n**************************\n"
  ./tache5 $name
  printf "\n**************************\n"
  shift
done