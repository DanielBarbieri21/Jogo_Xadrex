# Jogo de Xadrez - MateCheck
Bem-vindo ao Jogo de Xadrez - MateCheck, um projeto inovador desenvolvido em C com interface gráfica utilizando a biblioteca SDL2. Este jogo foi criado como parte de um desafio da empresa fictícia MateCheck, com o objetivo de ensinar programação por meio da lógica dos movimentos das peças de xadrez. Em vez de mover as peças manualmente, você controla seus movimentos através de código, explorando estruturas de repetição, loops aninhados e recursividade.

## O projeto é dividido em três módulos de dificuldade crescente: Novato, Aventureiro e Mestre, cada um focado em diferentes aspectos da programação em C.

# Estrutura do Projeto
Módulo Novato: Implementa os movimentos básicos da Torre, Bispo e Rainha usando estruturas de repetição simples (for, while, do-while).
Módulo Aventureiro: Simula o movimento em "L" do Cavalo com loops aninhados.
Módulo Mestre: Usa recursividade para calcular o menor número de movimentos do Cavalo entre duas posições.
# Requisitos
Sistema
Windows (testado com MinGW64), Linux ou macOS.
Compilador GCC instalado.
## Dependências
SDL2: Biblioteca para interface gráfica.
Windows (MinGW): Baixe SDL2-devel-2.32.0-mingw.tar.gz em libsdl.org.
Linux: Instale com sudo apt-get install libsdl2-dev.
macOS: Use brew install sdl2.
## Funcionalidades
Módulo Novato:
Movimentos lineares da Torre (vermelho), Bispo (verde) e Rainha.
Interface gráfica com tabuleiro 8x8.
Módulo Aventureiro:
Movimento em "L" do Cavalo (azul).
Validação de limites do tabuleiro.
Módulo Mestre:
Cálculo recursivo do menor número de movimentos do Cavalo (amarelo).
Exibição de posições exploradas.
Estrutura do Código
modulo_novato.c: Implementa o módulo Novato.
modulo_aventureiro.c: Implementa o módulo Aventureiro.
modulo_mestre.c: Implementa o módulo Mestre.

### Desenvolvido por Daniel Barbieri Dev como parte do desafio MateCheck !!!

