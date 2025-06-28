#ifndef TRANSITION_CIRCLE_H
#define TRANSITION_CIRCLE_H

#include <stdbool.h>

// Inicializa el efecto de transición circular
void TransitionCircle_Init(void);

// Actualiza la animación de la transición
void TransitionCircle_Update(void);

// Dibuja la transición circular por pantalla
void TransitionCircle_Draw(void);

// Indica si la transición terminó
bool TransitionCircle_IsDone(void);

#endif // TRANSITION_CIRCLE_H
