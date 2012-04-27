#!/bin/bash

for i in svg/*.svg 
do 
	j=${i:4}
	echo ${j%.svg}
	convert "$i" -resize 27x27 "png/${j%.svg}.png" 
done
