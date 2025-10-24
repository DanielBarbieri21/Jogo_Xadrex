@echo off
REM Script de instalação para MateCheck no Windows
REM Desenvolvido por Daniel Barbieri Dev

echo ========================================
echo MateCheck - Instalador para Windows
echo Desenvolvido por Daniel Barbieri Dev
echo ========================================
echo.

REM Verificar se o MinGW está instalado
where gcc >nul 2>nul
if %errorlevel% neq 0 (
    echo ERRO: GCC não encontrado!
    echo.
    echo Para instalar o MinGW:
    echo 1. Baixe o MSYS2 de https://www.msys2.org/
    echo 2. Instale o MSYS2
    echo 3. Abra o MSYS2 e execute: pacman -S mingw-w64-x86_64-gcc
    echo 4. Adicione C:\msys64\mingw64\bin ao PATH
    echo.
    pause
    exit /b 1
)

REM Verificar se o Make está instalado
where make >nul 2>nul
if %errorlevel% neq 0 (
    echo ERRO: Make não encontrado!
    echo.
    echo Para instalar o Make:
    echo 1. No MSYS2, execute: pacman -S mingw-w64-x86_64-make
    echo 2. Adicione C:\msys64\mingw64\bin ao PATH
    echo.
    pause
    exit /b 1
)

REM Verificar se o pkg-config está instalado
where pkg-config >nul 2>nul
if %errorlevel% neq 0 (
    echo ERRO: pkg-config não encontrado!
    echo.
    echo Para instalar o pkg-config:
    echo 1. No MSYS2, execute: pacman -S mingw-w64-x86_64-pkg-config
    echo 2. Adicione C:\msys64\mingw64\bin ao PATH
    echo.
    pause
    exit /b 1
)

echo Verificando dependências...

REM Verificar SDL2
pkg-config --exists sdl2
if %errorlevel% neq 0 (
    echo ERRO: SDL2 não encontrado!
    echo.
    echo Para instalar o SDL2:
    echo 1. No MSYS2, execute: pacman -S mingw-w64-x86_64-SDL2
    echo 2. Configure o PKG_CONFIG_PATH se necessário
    echo.
    pause
    exit /b 1
)

REM Verificar SDL2_ttf
pkg-config --exists SDL2_ttf
if %errorlevel% neq 0 (
    echo ERRO: SDL2_ttf não encontrado!
    echo.
    echo Para instalar o SDL2_ttf:
    echo 1. No MSYS2, execute: pacman -S mingw-w64-x86_64-SDL2_ttf
    echo.
    pause
    exit /b 1
)

REM Verificar SDL2_mixer
pkg-config --exists SDL2_mixer
if %errorlevel% neq 0 (
    echo ERRO: SDL2_mixer não encontrado!
    echo.
    echo Para instalar o SDL2_mixer:
    echo 1. No MSYS2, execute: pacman -S mingw-w64-x86_64-SDL2_mixer
    echo.
    pause
    exit /b 1
)

echo Todas as dependências estão instaladas!
echo.

REM Criar diretórios necessários
echo Criando diretórios...
if not exist "obj" mkdir obj
if not exist "obj\modules" mkdir obj\modules
if not exist "bin" mkdir bin
if not exist "assets" mkdir assets
if not exist "assets\fonts" mkdir assets\fonts
if not exist "assets\sounds" mkdir assets\sounds
if not exist "assets\images" mkdir assets\images
if not exist "logs" mkdir logs

REM Compilar o projeto
echo Compilando MateCheck...
make
if %errorlevel% neq 0 (
    echo ERRO: Falha na compilação!
    echo.
    echo Verifique se todas as dependências estão instaladas.
    echo.
    pause
    exit /b 1
)

echo Compilação concluída com sucesso!
echo.

REM Criar arquivo de configuração
echo Criando arquivo de configuração...
(
echo [Game]
echo PlayerName=Jogador
echo Difficulty=1
echo Score=0
echo ShowMoves=true
echo SoundEnabled=true
echo MusicEnabled=true
echo.
echo [Graphics]
echo WindowWidth=1000
echo WindowHeight=800
echo Fullscreen=false
echo VSync=true
echo.
echo [Audio]
echo Volume=0.8
echo MusicVolume=0.6
) > config.ini

REM Criar arquivo de log
echo. > logs\matecheck.log

echo Assets criados!
echo.

REM Testar o jogo
echo Testando MateCheck...
if exist "bin\matecheck.exe" (
    echo Executável encontrado!
    echo.
    echo Para executar o jogo:
    echo   bin\matecheck.exe
    echo.
    echo Para mais informações:
    echo   make help
    echo.
) else (
    echo ERRO: Executável não encontrado!
    echo.
    pause
    exit /b 1
)

REM Perguntar se quer instalar
set /p install="Deseja instalar o MateCheck no sistema? (y/n): "
if /i "%install%"=="y" (
    echo Instalando MateCheck...
    copy "bin\matecheck.exe" "C:\Windows\System32\" >nul 2>nul
    if %errorlevel% neq 0 (
        echo ERRO: Não foi possível instalar. Execute como administrador.
        echo.
    ) else (
        echo MateCheck instalado com sucesso!
        echo.
    )
)

echo.
echo ========================================
echo Instalação Concluída!
echo ========================================
echo.
echo Para executar o jogo: bin\matecheck.exe
echo Para mais informações: make help
echo.
echo Obrigado por usar o MateCheck!
echo.
pause
