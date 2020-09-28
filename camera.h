#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

struct SCamera {
    float x,
          y,
          z;
    float xRotate,
          zRotate;
};

void cameraApply();

void cameraRotation(float xAngle, float zAngle);

void cameraAutoMoveByMouse(int centerX,
                           int centerY,
                           float speed);

void wndResize(int x, int y);

void wndResizeApply(HWND hwnd);

void cameraMoveDirection(int forwardMove,
                         int rightMove,
                         float speed);

#endif // CAMERA_H_INCLUDED
