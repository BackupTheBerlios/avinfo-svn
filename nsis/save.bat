@echo off
echo Creating list, please wait
title Creating list, please wait
set tmplist=%TEMP%\avinfo.%random%.temp
dir /s /b %1>%tmplist%
start /b /wait avinfo -l=%tmplist% -t:html-list >list.html
del %tmplist%
