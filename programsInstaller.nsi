!define /D_UNICODE

Outfile "Password-creator(v6)_installer.exe" ; MODIFY IF NEEDED

!define APP_ORIGINAL_FOLDER "C:\Users\Admin\Desktop\GithubRepos\Projects\Qt\Password-creator\Password-creator\x64\Password-creator(v6)" ; MODIFY IF NEEDED
!define INSTALL_FOLDER "$PROGRAMFILES64\Emalice"

!define SHORTCUT_FOLDER "$SMPROGRAMS\Emalice"

!define APP_NAME "Password-creator(v6)"
!define APP_VERSION "6.0"
!define APP_PUBLISHER "Émile Laforce"
!define APP_SIZE_MB 47.6

!macro DefineConstants
  !define APP_EXE "${APP_NAME}.exe"
  !define APP_INSTALL_LOCATION "${INSTALL_FOLDER}\${APP_NAME}"
  !define REGISTRY_UINSTALL_FOLDER "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}"
!macroend

Section
  !insertmacro DefineConstants

  SetOutPath "${INSTALL_FOLDER}"
  File /r "${APP_ORIGINAL_FOLDER}"

  WriteRegStr HKLM "${REGISTRY_UINSTALL_FOLDER}" "DisplayName" "${APP_NAME}"
  WriteRegStr HKLM "${REGISTRY_UINSTALL_FOLDER}" "DisplayIcon" "${APP_INSTALL_LOCATION}\${APP_EXE}"
  WriteRegStr HKLM "${REGISTRY_UINSTALL_FOLDER}" "UninstallString" '"${APP_INSTALL_LOCATION}\uninstaller.exe"'
  WriteRegStr HKLM "${REGISTRY_UINSTALL_FOLDER}" "DisplayVersion" "${APP_VERSION}"
  WriteRegStr HKLM "${REGISTRY_UINSTALL_FOLDER}" "Publisher" "${APP_PUBLISHER}"
  WriteRegStr HKLM "${REGISTRY_UINSTALL_FOLDER}" "InstallLocation" "${APP_INSTALL_LOCATION}"
  IntOp $R0 ${APP_SIZE_MB} * 1024
  WriteRegDWORD HKLM "${REGISTRY_UINSTALL_FOLDER}" "EstimatedSize" $R0

  WriteUninstaller "${APP_INSTALL_LOCATION}\uninstaller.exe"
  
  CreateDirectory "${SHORTCUT_FOLDER}"
  CreateShortcut "${SHORTCUT_FOLDER}\${APP_NAME}.lnk" "${APP_INSTALL_LOCATION}\${APP_EXE}"
SectionEnd

Section "Uninstall"
  DeleteRegKey HKLM "${REGISTRY_UINSTALL_FOLDER}"

  RMDir /r "${APP_INSTALL_LOCATION}"

  Delete "${SHORTCUT_FOLDER}\${APP_NAME}.lnk"
SectionEnd