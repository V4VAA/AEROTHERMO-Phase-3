@echo off
setlocal
set "vsInstaller=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer"
set "vsInstall="
if exist "%vsInstaller%\vswhere.exe" (
    pushd "%vsInstaller%"
    if errorlevel 1 exit /b 1
    for /f "delims=" %%I in ('.\vswhere.exe -latest -version "[18.0,19.0)" -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath') do set "vsInstall=%%I"
    popd
)
if not defined vsInstall (
    echo Visual Studio 2026 with the x64 C++ build tools is required. 1>&2
    exit /b 1
)
call "%vsInstall%\Common7\Tools\VsDevCmd.bat" -no_logo -arch=x64 -host_arch=x64
if errorlevel 1 exit /b %errorlevel%

pushd "%~dp0"
if errorlevel 1 exit /b %errorlevel%
if not exist build\ mkdir build
pushd build
if errorlevel 1 (
    popd
    exit /b 1
)

cl /nologo /std:c++20 /EHsc /O2 /MD /utf-8 /I..\EquilFlow ^
    ..\src\main.cpp ..\src\std_atmosphere.cpp ..\src\shocks.cpp ^
    ..\src\cone.cpp ..\src\stag_properties.cpp ..\src\ArmSutMixing.cpp ^
    ..\EquilFlow\Release\EquilFlowLib.lib /Fe:AE4080.exe /link /IGNORE:4099
set "result=%errorlevel%"
popd
if not "%result%"=="0" goto finish

rem EquilFlow locates GasModels and Species relative to the working directory.
build\AE4080.exe
set "result=%errorlevel%"

:finish
popd
exit /b %result%
