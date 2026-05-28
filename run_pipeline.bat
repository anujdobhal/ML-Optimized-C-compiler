@echo off
REM ============================================================
REM  ML-Optimized C Compiler — Full Pipeline
REM  Usage:  run_pipeline.bat <source_file.c>
REM  Example: run_pipeline.bat test1.c
REM ============================================================

if "%~1"=="" (
    echo Usage: run_pipeline.bat ^<source_file.c^>
    echo Example: run_pipeline.bat "Semantic and Syntax Analysis\test1.c"
    exit /b 1
)

set "PROJECT_DIR=%~dp0"
set "SRC_FILE=%~1"
set "COMPILER_DIR=%PROJECT_DIR%Semantic and Syntax Analysis"
set "ML_DIR=%PROJECT_DIR%ml_module"
set "TAC_FILE=%COMPILER_DIR%\tac.txt"

echo.
echo ============================================================
echo   ML-Optimized C Compiler Pipeline
echo ============================================================
echo   Source: %SRC_FILE%
echo ============================================================

echo.
echo [Step 1/2] Running compiler (Lexer + Parser + AST + TAC)...
echo ------------------------------------------------------------
set "ABS_SRC_FILE=%~f1"

if not exist "%ABS_SRC_FILE%" (
    echo.
    echo [ERROR] Source file not found: %ABS_SRC_FILE%
    exit /b 1
)

pushd "%COMPILER_DIR%"
compiler.exe "%ABS_SRC_FILE%"
set COMPILER_ERR=%ERRORLEVEL%
popd

if %COMPILER_ERR% neq 0 (
    echo.
    echo [ERROR] Compilation failed!
    exit /b %COMPILER_ERR%
)

echo.
echo [Step 2/2] Running ML optimizer on TAC...
echo ------------------------------------------------------------
python "%ML_DIR%\optimizer.py" "%TAC_FILE%"
if errorlevel 1 (
    echo.
    echo [ERROR] ML optimization failed!
    exit /b 1
)

echo.
echo ============================================================
echo   Pipeline Complete!
echo ============================================================
