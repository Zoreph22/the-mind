@echo off
:loop
	cls
	del /s /f /q ServerProject
	del /s /f /q ClientProject
	del /s /f /q BotProject
	del /s /f /q Shared

	doxygen Doxyfile_Shared
	echo Appuyez sur une touche pour reg‚n‚rer la documentation...
	pause >NUL
goto loop

	doxygen Doxyfile_ServerProject
	doxygen Doxyfile_ClientProject
	doxygen Doxyfile_BotProject