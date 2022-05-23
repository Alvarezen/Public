@echo off

del *.obj *.ilk *.pdb *.ini

rmdir /q /s .vs

rmdir /q /s ..\.vscode

move *.exe ../bin/
