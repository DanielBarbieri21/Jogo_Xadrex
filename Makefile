# Makefile para MateCheck - Jogo de Xadrez Educacional
# Desenvolvido por Daniel Barbieri Dev

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -g
LDFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_mixer

# Diretórios
SRCDIR = .
MODULESDIR = modules
OBJDIR = obj
BINDIR = bin
ASSETSDIR = assets

# Nome do executável
TARGET = $(BINDIR)/matecheck

# Arquivos fonte
SOURCES = main.c game_engine.c board.c pieces.c ui.c
MODULE_SOURCES = $(MODULESDIR)/novato.c $(MODULESDIR)/aventureiro.c $(MODULESDIR)/mestre.c
ALL_SOURCES = $(SOURCES) $(MODULE_SOURCES)

# Arquivos objeto
OBJECTS = $(ALL_SOURCES:%.c=$(OBJDIR)/%.o)

# Regra principal
all: $(TARGET)

# Criar diretórios necessários
$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/modules

$(BINDIR):
	mkdir -p $(BINDIR)

$(ASSETSDIR):
	mkdir -p $(ASSETSDIR)/fonts
	mkdir -p $(ASSETSDIR)/sounds
	mkdir -p $(ASSETSDIR)/images

# Compilar executável
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "Compilação concluída: $@"

# Compilar arquivos objeto
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regras específicas para módulos
$(OBJDIR)/modules/%.o: $(MODULESDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -rf $(OBJDIR) $(BINDIR)
	@echo "Arquivos de compilação removidos"

# Limpeza completa (incluindo assets)
distclean: clean
	rm -rf $(ASSETSDIR)
	@echo "Limpeza completa realizada"

# Instalar dependências (Windows com MinGW)
install-deps-windows:
	@echo "Instalando dependências para Windows..."
	@echo "Por favor, baixe SDL2-devel-2.32.0-mingw.tar.gz de https://www.libsdl.org/"
	@echo "Extraia os arquivos para C:/mingw64/ ou configure as variáveis de ambiente apropriadas"

# Instalar dependências (Linux)
install-deps-linux:
	@echo "Instalando dependências para Linux..."
	sudo apt-get update
	sudo apt-get install -y libsdl2-dev libsdl2-ttf-dev libsdl2-mixer-dev

# Instalar dependências (macOS)
install-deps-macos:
	@echo "Instalando dependências para macOS..."
	brew install sdl2 sdl2_ttf sdl2_mixer

# Executar o jogo
run: $(TARGET)
	./$(TARGET)

# Executar com debug
debug: CFLAGS += -DDEBUG -g3
debug: $(TARGET)
	gdb ./$(TARGET)

# Executar com valgrind (Linux)
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# Criar pacote de distribuição
package: $(TARGET) | $(ASSETSDIR)
	@echo "Criando pacote de distribuição..."
	mkdir -p matecheck-dist
	cp $(TARGET) matecheck-dist/
	cp -r $(ASSETSDIR) matecheck-dist/ 2>/dev/null || true
	cp README.md matecheck-dist/
	cp LICENSE matecheck-dist/ 2>/dev/null || true
	tar -czf matecheck-dist.tar.gz matecheck-dist/
	@echo "Pacote criado: matecheck-dist.tar.gz"

# Instalar o jogo
install: $(TARGET)
	@echo "Instalando MateCheck..."
	mkdir -p /usr/local/bin
	cp $(TARGET) /usr/local/bin/matecheck
	@echo "MateCheck instalado em /usr/local/bin/matecheck"

# Desinstalar o jogo
uninstall:
	@echo "Desinstalando MateCheck..."
	rm -f /usr/local/bin/matecheck
	@echo "MateCheck desinstalado"

# Verificar dependências
check-deps:
	@echo "Verificando dependências..."
	@which gcc > /dev/null || (echo "GCC não encontrado" && exit 1)
	@which pkg-config > /dev/null || (echo "pkg-config não encontrado" && exit 1)
	@pkg-config --exists sdl2 || (echo "SDL2 não encontrado" && exit 1)
	@pkg-config --exists SDL2_ttf || (echo "SDL2_ttf não encontrado" && exit 1)
	@pkg-config --exists SDL2_mixer || (echo "SDL2_mixer não encontrado" && exit 1)
	@echo "Todas as dependências estão instaladas"

# Mostrar ajuda
help:
	@echo "MateCheck - Jogo de Xadrez Educacional"
	@echo "======================================"
	@echo ""
	@echo "Comandos disponíveis:"
	@echo "  make              - Compilar o jogo"
	@echo "  make run          - Compilar e executar"
	@echo "  make clean        - Limpar arquivos de compilação"
	@echo "  make distclean     - Limpeza completa"
	@echo "  make debug         - Compilar com debug"
	@echo "  make valgrind      - Executar com valgrind (Linux)"
	@echo "  make package       - Criar pacote de distribuição"
	@echo "  make install       - Instalar o jogo"
	@echo "  make uninstall     - Desinstalar o jogo"
	@echo "  make check-deps    - Verificar dependências"
	@echo "  make help          - Mostrar esta ajuda"
	@echo ""
	@echo "Instalação de dependências:"
	@echo "  make install-deps-windows  - Windows (MinGW)"
	@echo "  make install-deps-linux    - Linux (Ubuntu/Debian)"
	@echo "  make install-deps-macos    - macOS (Homebrew)"
	@echo ""
	@echo "Para mais informações, consulte o README.md"

# Regras que não são arquivos
.PHONY: all clean distclean install-deps-windows install-deps-linux install-deps-macos run debug valgrind package install uninstall check-deps help

# Dependências
$(OBJECTS): chess_engine.h
