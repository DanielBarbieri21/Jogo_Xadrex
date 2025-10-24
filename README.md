# 🏆 MateCheck - Jogo de Xadrez Educacional

<div align="center">
  <img src="https://img.shields.io/badge/Linguagem-C-blue.svg" alt="Linguagem C">
  <img src="https://img.shields.io/badge/SDL2-2.32.0-green.svg" alt="SDL2">
  <img src="https://img.shields.io/badge/Plataforma-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg" alt="Plataforma">
  <img src="https://img.shields.io/badge/Licença-MIT-yellow.svg" alt="Licença">
</div>

## 📖 Sobre o Projeto

O **MateCheck** é um projeto inovador desenvolvido em C com interface gráfica utilizando a biblioteca SDL2. Este jogo foi criado como parte de um desafio da empresa fictícia MateCheck, com o objetivo de ensinar programação por meio da lógica dos movimentos das peças de xadrez.

Em vez de mover as peças manualmente, você controla seus movimentos através de código, explorando estruturas de repetição, loops aninhados e recursividade.

## 🎯 Características Principais

- **Interface Gráfica Moderna**: Interface bonita e intuitiva usando SDL2
- **Três Módulos de Dificuldade**: Novato, Aventureiro e Mestre
- **Sistema de Pontuação**: Acompanhe seu progresso
- **Efeitos Sonoros**: Sons para movimentos e capturas
- **Código Modular**: Arquitetura limpa e bem organizada
- **Documentação Completa**: Guias detalhados para cada módulo

## 🎮 Módulos do Jogo

### 🟢 Módulo Novato
**Conceitos**: Estruturas de repetição (for, while, do-while)
- **Torre**: Movimentos horizontais e verticais
- **Bispo**: Movimentos diagonais
- **Rainha**: Combinação de Torre + Bispo

### 🟡 Módulo Aventureiro
**Conceitos**: Loops aninhados, validação de limites
- **Cavalo**: Movimento em "L" usando loops aninhados
- **Algoritmo de Busca**: Encontrar caminhos válidos

### 🔴 Módulo Mestre
**Conceitos**: Recursividade, backtracking, otimização
- **Algoritmo Recursivo**: Encontrar menor caminho do cavalo
- **Memoização**: Otimização de performance
- **Comparação de Algoritmos**: Diferentes abordagens

## 🚀 Instalação

### Pré-requisitos

- **Sistema**: Windows (MinGW64), Linux ou macOS
- **Compilador**: GCC instalado
- **Dependências**: SDL2, SDL2_ttf, SDL2_mixer

### Windows (MinGW)

```bash
# Instalar dependências
make install-deps-windows

# Compilar
make

# Executar
make run
```

### Linux (Ubuntu/Debian)

```bash
# Instalar dependências
make install-deps-linux

# Compilar
make

# Executar
make run
```

### macOS (Homebrew)

```bash
# Instalar dependências
make install-deps-macos

# Compilar
make

# Executar
make run
```

## 🛠️ Compilação Manual

```bash
# Verificar dependências
make check-deps

# Compilar
make

# Compilar com debug
make debug

# Limpar arquivos
make clean
```

## 📁 Estrutura do Projeto

```
MateCheck/
├── 📄 main.c                 # Arquivo principal
├── 📄 chess_engine.h         # Cabeçalho principal
├── 📄 game_engine.c          # Motor do jogo
├── 📄 board.c                # Lógica do tabuleiro
├── 📄 pieces.c                # Movimentos das peças
├── 📄 ui.c                    # Interface do usuário
├── 📁 modules/               # Módulos específicos
│   ├── 📄 novato.c           # Módulo Novato
│   ├── 📄 aventureiro.c      # Módulo Aventureiro
│   └── 📄 mestre.c           # Módulo Mestre
├── 📁 assets/                # Recursos do jogo
│   ├── 📁 fonts/             # Fontes
│   ├── 📁 sounds/            # Sons
│   └── 📁 images/            # Imagens
├── 📄 Makefile               # Sistema de build
└── 📄 README.md              # Este arquivo
```

## 🎯 Como Jogar

1. **Inicie o jogo**: Execute `make run`
2. **Escolha o módulo**: Use as setas para navegar no menu
3. **Selecione peças**: Clique nas peças para selecioná-las
4. **Veja os movimentos**: Movimentos possíveis são destacados
5. **Faça o movimento**: Clique no destino desejado
6. **Aprenda**: Observe como o código controla os movimentos

## 🎓 Conceitos de Programação Ensinados

### Módulo Novato
- **Estruturas de Repetição**: `for`, `while`, `do-while`
- **Arrays**: Armazenamento de posições
- **Funções**: Modularização do código

### Módulo Aventureiro
- **Loops Aninhados**: Percorrer matrizes 2D
- **Validação**: Verificar limites do tabuleiro
- **Algoritmos de Busca**: Encontrar caminhos

### Módulo Mestre
- **Recursividade**: Funções que chamam a si mesmas
- **Backtracking**: Desfazer movimentos inválidos
- **Memoização**: Otimizar cálculos repetidos
- **Complexidade**: Análise de algoritmos

## 🔧 Comandos Úteis

```bash
# Compilar e executar
make run

# Compilar com debug
make debug

# Executar com valgrind (Linux)
make valgrind

# Criar pacote de distribuição
make package

# Instalar o jogo
make install

# Verificar dependências
make check-deps

# Mostrar ajuda
make help
```

## 🎨 Personalização

### Cores
As cores podem ser personalizadas no arquivo `chess_engine.h`:

```c
#define COLOR_WHITE {255, 255, 255, 255}
#define COLOR_BLACK {0, 0, 0, 255}
#define COLOR_LIGHT_BROWN {240, 217, 181, 255}
#define COLOR_DARK_BROWN {181, 136, 99, 255}
```

### Sons
Adicione arquivos de som na pasta `assets/sounds/`:
- `move.wav` - Som de movimento
- `capture.wav` - Som de captura
- `background.wav` - Música de fundo

### Fontes
Adicione fontes na pasta `assets/fonts/`:
- `arial.ttf` - Fonte principal

## 🐛 Solução de Problemas

### Erro de Compilação
```bash
# Verificar dependências
make check-deps

# Limpar e recompilar
make clean
make
```

### Erro de SDL2
```bash
# Linux
sudo apt-get install libsdl2-dev libsdl2-ttf-dev libsdl2-mixer-dev

# macOS
brew install sdl2 sdl2_ttf sdl2_mixer
```

### Erro de Fontes
- Certifique-se de que as fontes estão na pasta `assets/fonts/`
- O jogo tentará usar fontes do sistema como fallback

## 📊 Performance

O jogo foi otimizado para diferentes níveis de performance:

- **Módulo Novato**: O(n) - Linear
- **Módulo Aventureiro**: O(n²) - Quadrático
- **Módulo Mestre**: O(8^n) → O(n²) com otimização

## 🤝 Contribuição

Contribuições são bem-vindas! Para contribuir:

1. Fork o projeto
2. Crie uma branch para sua feature
3. Commit suas mudanças
4. Push para a branch
5. Abra um Pull Request


## 👨‍💻 Autor

**Daniel Barbieri Dev**
- Desenvolvedor do projeto MateCheck
- Especialista em programação educacional
- Criador de jogos educacionais em C

## 🙏 Agradecimentos

- **SDL2 Team** - Biblioteca gráfica incrível
- **Comunidade C** - Linguagem poderosa e elegante
- **Educadores** - Inspiração para projetos educacionais

## 📞 Contato

Para dúvidas, sugestões ou problemas:

- **Email**: dibarbieri21@gmail.com
- **GitHub**: [@danielbarbieri](https://github.com/DanielBarbieri21))
- **LinkedIn**: [Daniel Barbieri](https://www.linkedin.com/in/daniel-barbieri-4990462a)

---

<div align="center">
  <p><strong>MateCheck</strong> - Aprenda programação jogando xadrez! 🏆</p>
  <p>Desenvolvido com ❤️ por Daniel Barbieri Dev</p>

</div>

