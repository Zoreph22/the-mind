#!/bin/sh

while true
do
	clear
	rm -rfv ServerProject
	rm -rfv ClientProject
	rm -rfv BotProject
	rm -rfv Shared
	doxygen Doxyfile_ServerProject
	doxygen Doxyfile_ClientProject
	doxygen Doxyfile_BotProject
	doxygen Doxyfile_Shared
	echo Appuyez sur une touche pour regénérer la documentation...
	read NONE
done