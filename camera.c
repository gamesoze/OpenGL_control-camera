#include <GL/gl.h>
#include <windows.h>
#include "camera.h"
#include <math.h>

struct SCamera camera = {0, 0, 1.7, 0, 0};

void cameraApply()
{
    glRotatef(-camera.xRotate, 1, 0, 0);    //Shift axis x
    glRotatef(-camera.zRotate, 0, 0, 1);    //Shift axis z

    //Shift "camera" (coordinate systems)
    glTranslatef(-camera.x, -camera.y, -camera.z);
}

void cameraRotation(float xAngle, float zAngle)
{
    camera.zRotate += zAngle;
    //Dumping extra 2 * pi
        if(camera.zRotate < 0)      camera.zRotate += 360;
        if(camera.zRotate > 360)    camera.zRotate -= 360;

    camera.xRotate += xAngle;
    //Dumping extra pi
        if(camera.xRotate < 0)      camera.xRotate = 0;
        if(camera.xRotate > 180)    camera.xRotate = 180;
}

void cameraAutoMoveByMouse(int centerX, int centerY, float speed)
{
    //Getting cursor position
    POINT cursor;
    GetCursorPos(&cursor);

    //Reference point position ("NULL")
    POINT base = {centerX, centerY};

    //Shift for difference
    cameraRotation((base.y - cursor.y) * speed,
                   (base.x - cursor.x) * speed);

    //Return to "NULL"
    SetCursorPos(base.x, base.y);
}

void wndResize(int x, int y)
{
    glViewport(0, 0, x, y);

    float k = x / (float) y;
    float sz = 0.1;

    glLoadIdentity();

    glFrustum(-k * sz, k *sz, -sz, sz, sz * 2, 100);
}

void wndResizeApply(HWND hwnd)
{
    RECT rct;
    GetClientRect(hwnd,&rct);
    wndResize(rct.right, rct.bottom);
    //printf("%f", M_PI);
}

void cameraMoveDirection(int forwardMove, int rightMove, float speed)
{
    float angel = -camera.zRotate / 180 * M_PI;

    if(forwardMove > 0)
        angel += rightMove > 0 ? M_PI_4 : (rightMove < 0 ? -M_PI_4 : 0);
    if(forwardMove < 0)
        angel += M_PI + (rightMove > 0 ? -M_PI_4 : (rightMove < 0 ? M_PI_4 : 0));
    if(forwardMove == 0)
    {
        angel += rightMove > 0 ? M_PI_2 : -M_PI_2;

        if(rightMove == 0)  speed = 0;
    }

    if(speed != 0)
    {
        camera.x += sin(angel) * speed;
        camera.y += cos(angel) * speed;
    }
}
