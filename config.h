#ifndef CONFIG_H
#define CONFIG_H

// Configurações do jogo MateCheck
// Este arquivo contém todas as configurações personalizáveis

// === CONFIGURAÇÕES DE JANELA ===
#define WINDOW_TITLE "MateCheck - Jogo de Xadrez Educacional"
#define WINDOW_ICON_PATH "assets/images/icon.png"

// === CONFIGURAÇÕES DE ÁUDIO ===
#define AUDIO_SAMPLE_RATE 44100
#define AUDIO_CHANNELS 2
#define AUDIO_BUFFER_SIZE 2048

// === CONFIGURAÇÕES DE FONTES ===
#define FONT_SIZE_SMALL 16
#define FONT_SIZE_MEDIUM 20
#define FONT_SIZE_LARGE 24
#define FONT_SIZE_TITLE 32

// === CONFIGURAÇÕES DE CORES ===
// Cores do tabuleiro
#define BOARD_LIGHT_COLOR 0xF0D9B5  // #F0D9B5
#define BOARD_DARK_COLOR 0xB58863   // #B58863

// Cores das peças
#define PIECE_WHITE_COLOR 0xFFFFFF   // #FFFFFF
#define PIECE_BLACK_COLOR 0x000000   // #000000

// Cores de destaque
#define HIGHLIGHT_COLOR 0xFFFF00    // #FFFF00
#define MOVE_HINT_COLOR 0x00FF00    // #00FF00
#define ATTACK_COLOR 0xFF0000       // #FF0000
#define SELECTED_COLOR 0x0000FF     // #0000FF

// === CONFIGURAÇÕES DE JOGO ===
#define MAX_MOVES 1000
#define MAX_DEPTH 10
#define TIMEOUT_SECONDS 30

// === CONFIGURAÇÕES DE PERFORMANCE ===
#define MAX_FPS 60
#define VSYNC_ENABLED 1
#define HARDWARE_ACCELERATION 1

// === CONFIGURAÇÕES DE DEBUG ===
#ifdef DEBUG
    #define DEBUG_PRINT 1
    #define DEBUG_LOGGING 1
    #define DEBUG_PERFORMANCE 1
#else
    #define DEBUG_PRINT 0
    #define DEBUG_LOGGING 0
    #define DEBUG_PERFORMANCE 0
#endif

// === CONFIGURAÇÕES DE MÓDULOS ===
#define MODULE_NOVATO_ENABLED 1
#define MODULE_AVENTUREIRO_ENABLED 1
#define MODULE_MESTRE_ENABLED 1

// === CONFIGURAÇÕES DE INTERFACE ===
#define UI_PANEL_WIDTH 100
#define UI_PANEL_HEIGHT 800
#define UI_MARGIN 20
#define UI_BUTTON_HEIGHT 40

// === CONFIGURAÇÕES DE SOM ===
#define SOUND_MOVE_FREQUENCY 440    // Nota Lá
#define SOUND_CAPTURE_FREQUENCY 880 // Nota Lá oitava
#define SOUND_DURATION 0.1          // 100ms

// === CONFIGURAÇÕES DE ANIMAÇÃO ===
#define ANIMATION_DURATION 0.3      // 300ms
#define ANIMATION_FRAMES 10
#define ANIMATION_EASING 1          // 1 = linear, 2 = ease-in-out

// === CONFIGURAÇÕES DE ARQUIVOS ===
#define SAVE_FILE_PATH "saves/"
#define CONFIG_FILE_PATH "config.ini"
#define LOG_FILE_PATH "logs/matecheck.log"

// === CONFIGURAÇÕES DE REDE ===
#define NETWORK_PORT 8080
#define NETWORK_TIMEOUT 5000        // 5 segundos
#define NETWORK_MAX_CONNECTIONS 4

// === CONFIGURAÇÕES DE SEGURANÇA ===
#define MAX_INPUT_LENGTH 100
#define MAX_FILENAME_LENGTH 255
#define SANITIZE_INPUT 1

// === CONFIGURAÇÕES DE LOCALIZAÇÃO ===
#define DEFAULT_LANGUAGE "pt_BR"
#define SUPPORTED_LANGUAGES {"pt_BR", "en_US", "es_ES"}

// === CONFIGURAÇÕES DE VERSÃO ===
#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define VERSION_PATCH 0
#define VERSION_BUILD 1

// === CONFIGURAÇÕES DE COMPATIBILIDADE ===
#define MIN_SDL_VERSION 2.0.0
#define MIN_TTF_VERSION 2.0.0
#define MIN_MIXER_VERSION 2.0.0

// === CONFIGURAÇÕES DE DESENVOLVIMENTO ===
#define ENABLE_PROFILING 0
#define ENABLE_MEMORY_DEBUG 0
#define ENABLE_ASSERTIONS 1

// === CONFIGURAÇÕES DE PLATAFORMA ===
#ifdef _WIN32
    #define PLATFORM_WINDOWS 1
    #define PATH_SEPARATOR '\\'
#elif __linux__
    #define PLATFORM_LINUX 1
    #define PATH_SEPARATOR '/'
#elif __APPLE__
    #define PLATFORM_MACOS 1
    #define PATH_SEPARATOR '/'
#else
    #define PLATFORM_UNKNOWN 1
    #define PATH_SEPARATOR '/'
#endif

// === MACROS ÚTEIS ===
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define CLAMP(value, min, max) (MIN(MAX(value, min), max))

// === CONFIGURAÇÕES DE COMPILAÇÃO ===
#ifndef NDEBUG
    #define DEBUG 1
#endif

// === CONFIGURAÇÕES DE FEATURES ===
#define FEATURE_SOUND 1
#define FEATURE_MUSIC 1
#define FEATURE_ANIMATIONS 1
#define FEATURE_PARTICLES 1
#define FEATURE_SHADERS 0
#define FEATURE_NETWORK 0

#endif // CONFIG_H
