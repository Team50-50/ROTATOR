#ifndef CAMERA_H
#define CAMERA_H

#include "main.h"

static D3DXVECTOR2 g_CameraPosition;

static D3DXVECTOR2 g_Screen_Position;

void InitCamera();
void UninitCamera();
void UpdateCamera();
void DrawCamera();

#endif CAMERA_H
