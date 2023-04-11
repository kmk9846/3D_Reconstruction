#include <GLUT/glut.h>
#include "voxel.h"
#include "drawVoxel.h"
#include <math.h>

int lastX, lastY;
int xAngle = 0, yAngle = 0;
float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 5.0f;
float sensitivity = 0.1;

GLfloat camera_position[] = {0.0, 0.0, 5.0}; // 초기 카메라 위치
GLfloat camera_yaw = 0.0; // 카메라 좌우 회전 각도
GLfloat camera_pitch = 0.0; // 카메라 상하 회전 각도

void display()
{
    // VoxelGrid voxelGrid;
    DrawVoxel drawVoxel;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera_position[0], camera_position[1], camera_position[2], 
             camera_position[0] + sin(camera_yaw), camera_position[1] + sin(camera_pitch), 
             camera_position[2] + cos(camera_yaw), 0.0, 1.0, 0.0);

    glTranslatef(0.0f, 0.0f, -5.0f);  // 카메라를 -z 방향으로 이동
    glRotatef(xAngle, 1.0f, 0.0f, 0.0f);  // x축 기준으로 회전
    glRotatef(yAngle, 0.0f, 1.0f, 0.0f);  // y축 기준으로 회전

    for(int i = 0; i < VoxelNuum; i++)
    {
        for(int j = 0; j < VoxelNuum; j++)
        {
            for(int k = 0; k < VoxelNuum; k++)
            {
                glColor3f(1.0f, 1.0f, 1.0f);
                drawVoxel.drawVoxel(drawVoxel.voxel[i][j][k].centerPoint.x, drawVoxel.voxel[i][j][k].centerPoint.y, drawVoxel.voxel[i][j][k].centerPoint.z);
            }
        }
    }

    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0); // x축 빨간색
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);

    glColor3f(0.0, 1.0, 0.0); // y축 초록색
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);

    glColor3f(0.0, 0.0, 1.0); // z축 파란색
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1.0);
    glEnd();
    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        lastX = x;
        lastY = y;
    }
}

void motion(int x, int y)
{
    int deltaX = x - lastX;
    int deltaY = y - lastY;

    xAngle += y - lastY;
    yAngle += x - lastX;

    lastX = x;
    lastY = y;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
   switch (key) {
      case 'w':
         // 카메라 위치를 바라보는 방향으로 이동
         camera_position[0] += sin(camera_yaw);
         camera_position[2] += cos(camera_yaw);
         break;
      case 's':
         // 카메라 위치를 바라보는 반대 방향으로 이동
         camera_position[0] -= sin(camera_yaw);
         camera_position[2] -= cos(camera_yaw);
         break;
      case 'a':
         // 카메라를 왼쪽으로 회전
         camera_yaw -= 0.1;
         break;
      case 'd':
         // 카메라를 오른쪽으로 회전
         camera_yaw += 0.1;
         break;
      case 'q':
         // 카메라를 위쪽으로 회전
         camera_pitch -= 0.1;
         break;
      case 'e':
         // 카메라를 아래쪽으로 회전
         camera_pitch += 0.1;
         break;
   }

   glutPostRedisplay(); // 화면 다시 그리기
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Voxel Camera");

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, 1.0f, 0.1f, 100.0f);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMainLoop();
    return 0;
}
