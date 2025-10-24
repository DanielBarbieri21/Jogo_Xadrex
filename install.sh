#!/bin/bash

# Script de instalação para MateCheck
# Desenvolvido por Daniel Barbieri Dev

set -e  # Parar em caso de erro

# Cores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Função para imprimir mensagens coloridas
print_message() {
    echo -e "${2}${1}${NC}"
}

# Função para verificar se um comando existe
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Função para detectar o sistema operacional
detect_os() {
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        echo "linux"
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        echo "macos"
    elif [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "cygwin" ]]; then
        echo "windows"
    else
        echo "unknown"
    fi
}

# Função para instalar dependências no Linux
install_linux_deps() {
    print_message "Instalando dependências para Linux..." $BLUE
    
    if command_exists apt-get; then
        sudo apt-get update
        sudo apt-get install -y build-essential libsdl2-dev libsdl2-ttf-dev libsdl2-mixer-dev
    elif command_exists yum; then
        sudo yum install -y gcc gcc-c++ SDL2-devel SDL2_ttf-devel SDL2_mixer-devel
    elif command_exists pacman; then
        sudo pacman -S --noconfirm base-devel sdl2 sdl2_ttf sdl2_mixer
    else
        print_message "Gerenciador de pacotes não suportado. Instale manualmente:" $YELLOW
        print_message "- build-essential (gcc, make)" $YELLOW
        print_message "- libsdl2-dev" $YELLOW
        print_message "- libsdl2-ttf-dev" $YELLOW
        print_message "- libsdl2-mixer-dev" $YELLOW
        exit 1
    fi
}

# Função para instalar dependências no macOS
install_macos_deps() {
    print_message "Instalando dependências para macOS..." $BLUE
    
    if command_exists brew; then
        brew install sdl2 sdl2_ttf sdl2_mixer
    else
        print_message "Homebrew não encontrado. Instale o Homebrew primeiro:" $YELLOW
        print_message "/bin/bash -c \"\$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)\"" $YELLOW
        exit 1
    fi
}

# Função para instalar dependências no Windows
install_windows_deps() {
    print_message "Instalando dependências para Windows..." $BLUE
    
    print_message "Para Windows, você precisa:" $YELLOW
    print_message "1. Instalar MinGW-w64 ou MSYS2" $YELLOW
    print_message "2. Baixar SDL2-devel-2.32.0-mingw.tar.gz de https://www.libsdl.org/" $YELLOW
    print_message "3. Extrair os arquivos para o diretório do MinGW" $YELLOW
    print_message "4. Configurar as variáveis de ambiente PATH e PKG_CONFIG_PATH" $YELLOW
    
    if command_exists pacman; then
        print_message "MSYS2 detectado. Instalando dependências..." $BLUE
        pacman -S --noconfirm mingw-w64-x86_64-gcc mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_ttf mingw-w64-x86_64-SDL2_mixer
    else
        print_message "MinGW não encontrado. Instale o MinGW-w64 primeiro." $YELLOW
        exit 1
    fi
}

# Função para verificar dependências
check_dependencies() {
    print_message "Verificando dependências..." $BLUE
    
    # Verificar GCC
    if ! command_exists gcc; then
        print_message "GCC não encontrado!" $RED
        return 1
    fi
    
    # Verificar Make
    if ! command_exists make; then
        print_message "Make não encontrado!" $RED
        return 1
    fi
    
    # Verificar pkg-config
    if ! command_exists pkg-config; then
        print_message "pkg-config não encontrado!" $RED
        return 1
    fi
    
    # Verificar SDL2
    if ! pkg-config --exists sdl2; then
        print_message "SDL2 não encontrado!" $RED
        return 1
    fi
    
    # Verificar SDL2_ttf
    if ! pkg-config --exists SDL2_ttf; then
        print_message "SDL2_ttf não encontrado!" $RED
        return 1
    fi
    
    # Verificar SDL2_mixer
    if ! pkg-config --exists SDL2_mixer; then
        print_message "SDL2_mixer não encontrado!" $RED
        return 1
    fi
    
    print_message "Todas as dependências estão instaladas!" $GREEN
    return 0
}

# Função para compilar o projeto
compile_project() {
    print_message "Compilando MateCheck..." $BLUE
    
    # Criar diretórios necessários
    mkdir -p obj modules obj/modules bin assets/fonts assets/sounds assets/images
    
    # Compilar
    if make; then
        print_message "Compilação concluída com sucesso!" $GREEN
    else
        print_message "Erro na compilação!" $RED
        exit 1
    fi
}

# Função para criar assets básicos
create_assets() {
    print_message "Criando assets básicos..." $BLUE
    
    # Criar arquivo de configuração
    cat > config.ini << EOF
[Game]
PlayerName=Jogador
Difficulty=1
Score=0
ShowMoves=true
SoundEnabled=true
MusicEnabled=true

[Graphics]
WindowWidth=1000
WindowHeight=800
Fullscreen=false
VSync=true

[Audio]
Volume=0.8
MusicVolume=0.6
EOF
    
    # Criar arquivo de log
    mkdir -p logs
    touch logs/matecheck.log
    
    print_message "Assets criados!" $GREEN
}

# Função para instalar o jogo
install_game() {
    print_message "Instalando MateCheck..." $BLUE
    
    # Criar diretório de instalação
    INSTALL_DIR="/usr/local/bin"
    if [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "cygwin" ]]; then
        INSTALL_DIR="/usr/bin"
    fi
    
    # Copiar executável
    if [[ -f "bin/matecheck" ]]; then
        sudo cp bin/matecheck "$INSTALL_DIR/"
        sudo chmod +x "$INSTALL_DIR/matecheck"
        print_message "MateCheck instalado em $INSTALL_DIR" $GREEN
    else
        print_message "Executável não encontrado. Compile primeiro com 'make'." $RED
        exit 1
    fi
}

# Função para testar o jogo
test_game() {
    print_message "Testando MateCheck..." $BLUE
    
    if [[ -f "bin/matecheck" ]]; then
        print_message "Executando teste básico..." $BLUE
        timeout 5s ./bin/matecheck --test 2>/dev/null || true
        print_message "Teste concluído!" $GREEN
    else
        print_message "Executável não encontrado!" $RED
        exit 1
    fi
}

# Função principal
main() {
    print_message "=== MateCheck - Instalador ===" $GREEN
    print_message "Desenvolvido por Daniel Barbieri Dev" $BLUE
    print_message ""
    
    # Detectar sistema operacional
    OS=$(detect_os)
    print_message "Sistema operacional detectado: $OS" $BLUE
    
    # Instalar dependências
    case $OS in
        "linux")
            install_linux_deps
            ;;
        "macos")
            install_macos_deps
            ;;
        "windows")
            install_windows_deps
            ;;
        *)
            print_message "Sistema operacional não suportado!" $RED
            exit 1
            ;;
    esac
    
    # Verificar dependências
    if ! check_dependencies; then
        print_message "Instale as dependências primeiro!" $RED
        exit 1
    fi
    
    # Compilar projeto
    compile_project
    
    # Criar assets
    create_assets
    
    # Testar jogo
    test_game
    
    # Perguntar se quer instalar
    read -p "Deseja instalar o MateCheck no sistema? (y/n): " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        install_game
    fi
    
    print_message ""
    print_message "=== Instalação Concluída! ===" $GREEN
    print_message "Para executar o jogo: ./bin/matecheck" $BLUE
    print_message "Para mais informações: make help" $BLUE
    print_message ""
    print_message "Obrigado por usar o MateCheck!" $GREEN
}

# Executar função principal
main "$@"
