@echo off
setlocal
if "%~1"=="" (
  echo Usage: build.cmd OUTPUT_DIRECTORY -- run with pinned x86 MSVC 18.00.40629 on PATH
  exit /b 2
)
if not exist "%~1" mkdir "%~1"
if errorlevel 1 exit /b 1
for %%S in (matrix binding release shader) do (
  cl /nologo /c /O2 /Oy- /GS- /GR- /EHsc /Zl /Gy /arch:SSE2 /fp:precise /Fo"%~1\%%S.obj" "%~dp0%%S.cpp"
  if errorlevel 1 exit /b 1
)
exit /b 0
