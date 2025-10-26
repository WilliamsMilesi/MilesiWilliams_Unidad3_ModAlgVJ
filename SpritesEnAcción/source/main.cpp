#ifndef NDEBUG
#include <vld.h> // Visual Leak Detector, útil en modo Debug para detectar fugas de memoria
#endif

#include "raylib.h"

int main(void)
{
    // Inicializamos una ventana de 1024x768 píxeles con un título personalizado
    InitWindow(1024, 768, "Sprites en acción Milesi Williams");

    // Configuramos el framerate deseado (opcional, pero recomendado)
    SetTargetFPS(60);

    // Definimos color personalizado para el fondo
    Color fondo = BLACK;

    // TEXTURA Y FILTRO
    // Cargamos una textura desde un archivo PNG
    Texture2D Textura = LoadTexture("Sprite.png");

    // Aplicamos filtro bilineal para suavizar la imagen al escalarla y evitar que se vea pixelada
    SetTextureFilter(Textura, TEXTURE_FILTER_BILINEAR);

    // VARIABLES PRINCIPALES
    // Definimos el punto central de la escena (mitad de la ventana), para luego centrar bien los Sprites
    Vector2 centro = { 512, 384 };

    // Establecemos las escalas de cada Sprite
    float Escala1 = 0.5f;
    float Escala2 = 1.0f;

    // Definimos los colores para cada Sprite (simula materiales distintos)
    Color Color1 = WHITE;
    Color Color2 = RED;

    // Rotacion de cada Sprite (en este caso incializamos en 0 grados)
    float Rotacion1 = 0.0f;
    float Rotacion2 = 0.0f;

    // Velocidad con la se moverá el grupo de Sprites
    float Velocidad = 3.0f;

    // Bucle principal del juego (se repite hasta que se cierre la ventana)
    while (!WindowShouldClose())
    {
        // CONTROL DEL MOVIMIENTO
        // Permite mover ambos Sprites juntos en la pantalla usando las flechas
        if (IsKeyDown(KEY_RIGHT)) centro.x += Velocidad;
        if (IsKeyDown(KEY_LEFT))  centro.x -= Velocidad;
        if (IsKeyDown(KEY_UP))    centro.y -= Velocidad;
        if (IsKeyDown(KEY_DOWN))  centro.y += Velocidad;


        // SWAP VISUAL (intercambio de propiedades)
        // Al presionar la tecla ESPACIO, se intercambian las propiedades visuales (escala, color y rotación)
        if (IsKeyPressed(KEY_SPACE))
        {
            // Intercambia la escala entre Sprite 1 y Sprite 2
            float TempEsc = Escala1;
            Escala1 = Escala2;
            Escala2 = TempEsc;
            
            // Intercambia los colores
            Color TempCol = Color1;
            Color1 = Color2;
            Color2 = TempCol;

            // Intercambia las rotaciones
            float TempRot = Rotacion1;
            Rotacion1 = Rotacion2;
            Rotacion2 = TempRot;

        }

        // CÁLCULOS DE POSISICONES DE LOS SPRITES
        // Calculamos la distancia entre los Sprites para evitar que se superpongan
        float distancia = (Textura.width * Escala1 + Textura.width * Escala2) / 2 + 20; // 20 píxeles de espacio entre los sprites

        // Posición del primer Sprite (izquierda)
        Vector2 Pos1 = {
            centro.x - distancia / 2 - (Textura.width * Escala1) / 2,
            centro.y - (Textura.height * Escala1) / 2
        };

        // Posición del segundo Sprite (derecha)
        Vector2 Pos2 = {
            centro.x + distancia / 2 - (Textura.width * Escala2) / 2,
            centro.y - (Textura.height * Escala2) / 2
        };


        // Iniciamos la etapa de dibujo
        BeginDrawing();

        // Limpiamos la pantalla 
        ClearBackground(fondo);

        // Dibujamos los dos Sprites (Texturas cos sus propiedades)
        DrawTextureEx(Textura, Pos1, Rotacion1, Escala1, Color1);
        DrawTextureEx(Textura, Pos2, Rotacion2, Escala2, Color2);
       
        // INFORMACIÓN EN PANTALLA
        // Mostramos el nombre del color actual de cada Sprite (blanco o rojo)
        const char* NombreColor1 = (Color1.r == 255 && Color1.g == 255 && Color1.b == 255) ? "Blanco" : "Rojo";
        const char* NombreColor2 = (Color2.r == 255 && Color2.g == 255 && Color2.b == 255) ? "Blanco" : "Rojo";

        // Mostramos Propiedades del Sprite 1: Posición escala y color
        DrawText(TextFormat("Sprite 1 = Pos(%.0f, %.0f) Escala: %.2f Color: %s",
            Pos1.x, Pos1.y, Escala1, NombreColor1), 20, 20, 20, WHITE);

        // Mostramos Propiedades del Sprite 2: Posición escala y color
        DrawText(TextFormat("Sprite 2 = Pos(%.0f, %.0f) Escala: %.2f Color: %s",
            Pos2.x, Pos2.y, Escala2, NombreColor2), 20, 50, 20, WHITE);

        // Mostramos mensajes de ayuda para el usuario
        DrawText("Usa las flechas del teclado para mover los Sprites", 20, 700, 22, WHITE);

        DrawText("Presiona ESPACIO para intercambiar las propiedades (swap visual)", 20, 730, 22, WHITE);

        // Finalizamos el dibujo
        EndDrawing();
    }

    // Liberamos la textura cargada
    UnloadTexture(Textura);

    // Cerramos la ventana y liberamos recursos
    CloseWindow();

    return 0;
}