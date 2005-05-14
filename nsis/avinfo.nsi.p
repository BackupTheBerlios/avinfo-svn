; avinfo-install.nsi
;
; This script is based on example2.nsi and base.msi from nsis examples
;
;--------------------------------

#include "../src/ver.h"
!include "MUI.nsh"

; The name of the installer
Name AVINFO_SIGNATURE 

; The file to write
OutFile AVINFO_INSTALLER_NAME

; The default installation directory
InstallDir $PROGRAMFILES\avinfo

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)


 !define MUI_ABORTWARNING
;--------------------------------

; Pages


!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
  
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES


!insertmacro MUI_LANGUAGE "English"

; The stuff to install
Section "Binaries (required)" SecBinaries


  SectionIn RO
  
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File "..\src\avinfo.exe"
  
  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\avinfo "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\avinfo" "DisplayName" "AVInfo"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\avinfo" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\avinfo" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\avinfo" "NoRepair" 1
  WriteUninstaller "uninstall.exe"
  
SectionEnd


Section "Template file" SecTemplates

	SetOutPath $INSTDIR
	
	File "..\src\avinfo.tpl"

SectionEnd

Section "Configuration file" SecConfig

	SetOutPath $INSTDIR
	
	File "..\src\avinfo.cfg"

SectionEnd

SectionGroup "Documentation" SecDoc

Section "Russian"SecEnDoc

	SetOutPath $INSTDIR\docs
	
	File "..\doc\readme.ru.html"

SectionEnd

Section "English" SecRuDoc

	SetOutPath $INSTDIR\docs
	
	File "..\doc\readme.en.html"

SectionEnd


SectionGroupEnd

Section "Register in App Paths" SecReg
	
	  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\App Paths\avinfo.exe" "" "$INSTDIR\avinfo.exe"
	  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\App Paths\avinfo.exe" "Path" "$INSTDIR\avinfo.exe"

SectionEnd

Section "Shell extension" SecShell

	WriteRegStr HKCR "Directory\shell\Generate List (avinfo)" "" "&Generate List (avinfo)"
	WriteRegStr HKCR "Directory\shell\Generate List (avinfo)\command" "" "$\"$INSTDIR\save.bat$\" $\"%1$\""
	SetOutPath $INSTDIR
	File "save.bat"

SectionEnd



  LangString Desc_SecBinaries ${LANG_ENGLISH} "AVInfo executible"
  LangString Desc_SecTemplates ${LANG_ENGLISH} "File with templates (recommended)"
  LangString Desc_SecConfig ${LANG_ENGLISH} "Sample configuration file (recommended)"
  LangString Desc_SecRuDoc ${LANG_ENGLISH} "Russian Documentation"
  LangString Desc_SecEnDoc ${LANG_ENGLISH} "English Documentation"
  LangString Desc_SecDoc ${LANG_ENGLISH} "Documentation"
  LangString Desc_SecReg ${LANG_ENGLISH} "Registration of regestry key in App Paths allow to run AVInfo by typing 'avinfo' in command prompt (some like adding in %path%) N.B. this not work with pipes"
  LangString Desc_SecShell ${LANG_ENGLISH} "Add 'GenerareList (avinfo)' command to context menu of folders"
  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${SecBinaries} $(DESC_SecBinaries)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecTemplates} $(DESC_SecTemplates)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecConfig} $(DESC_SecConfig)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecRuDoc} $(DESC_SecRuDoc)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecEnDoc} $(DESC_SecEnDoc)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecDoc} $(DESC_SecDoc)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecReg} $(DESC_SecReg)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecShell} $(DESC_SecShell)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END




;--------------------------------

; Uninstaller

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\avinfo"
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\App Paths\avinfo.exe"
  DeleteRegKey HKCR "Directory\shell\Generate List (avinfo)\command" 
  DeleteRegKey HKCR "Directory\shell\Generate List (avinfo)" 

  ; Remove files and uninstaller
  Delete $INSTDIR\save.bat
  Delete $INSTDIR\docs\readme.ru.html
  Delete $INSTDIR\docs\readme.en.html
  Delete $INSTDIR\avinfo.exe
  Delete $INSTDIR\avinfo.cfg
  Delete $INSTDIR\avinfo.tpl
  Delete $INSTDIR\uninstall.exe
  ; Remove directories used

  RMDir "$INSTDIR\docs\russian"
  RMDir "$INSTDIR\docs\english"
  RMDir "$INSTDIR\docs"
  RMDir "$INSTDIR"

SectionEnd
