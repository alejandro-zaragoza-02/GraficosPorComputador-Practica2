
/****************************************************************************************************

    CarGL (main.cpp)

    Grado en Ingenier�a Multimedia.
    Pr�ctica de Gr�ficos por Computador.
    OpenGL con Shaders.
  ------------------------------------------------------------------------------------------

    CarsGL, 2012 - 2022 (C) Juan Antonio Puchol Garc�a (puchol@dccia.ua.es)

    Changelog:

    Versi�n 1.0 (Noviembre 2012)
        - Versi�n inicial para Code::Blocks 10.05

    Versi�n 1.1 (Noviembre 2012)
        - Arreglado el bug de selecci�n incorrecta debido al panel inferior de controles

    Versi�n 1.2 (Octubre 2013 )
        - Adaptaci�n de la librer�a GLUI a Code::Blocks 12.11 y 13.12

    Versi�n 1.3 (Octubre 2014 )
        - Adaptaci�n de la librer�a GLUI a Code::Blocks 13.12

    Versi�n 2.0 (Octubre 2015 )
        - Adaptaci�n del c�digo empleando Shaders (Modern OpenGL Graphics)

    Versi�n 2.1 (Septiembre 2016 )
        - Modificaci�n de los scrollbars de las luces para manipular la posisi�n (compatible con Code::Blocks 16.01)

    Versi�n 2.2 (Octubre 2022 )
        - Correcci�n de peque�os bugs
        - A�adidos dos edificios de ejemplo (m�todo TEscena::CrearEscena)

    ----------------------------------------------------------------------------------------------------------------

    NOTA:   Para que esta aplicaci�n compile correctamente se necesita tener copiados los
            siguientes archivos desde la carpeta "Para Copiar":

            glut32.dll  -> C:\Windows\system

            Si es un Windows de 32 bits:
            glew32s.lib -> C:\Program Files\CodeBlocks\MinGW\lib
            glew32.lib  -> C:\Program Files\CodeBlocks\MinGW\lib
            libglui32.a -> C:\Program Files\CodeBlocks\MinGW\lib
            glut32.lib  -> C:\Program Files\CodeBlocks\MinGW\lib

            glui.h      -> C:\Program Files\CodeBlocks\MinGW\include\GL
            glut.h      -> C:\Program Files\CodeBlocks\MinGW\include\GL
            glew.h      -> C:\Program Files\CodeBlocks\MinGW\include\GL

            y la carpeta completa
            glm         -> C:\Program Files\CodeBlocks\MinGW\include

            Si es un Windows de 64 bits:
            glew32s.lib -> C:\Program Files (x86)\CodeBlocks\MinGW\lib
            glew32.lib  -> C:\Program Files (x86)\CodeBlocks\MinGW\lib
            libglui32.a -> C:\Program Files (x86)\CodeBlocks\MinGW\lib
            glut32.lib  -> C:\Program Files (x86)\CodeBlocks\MinGW\lib

            glui.h      -> C:\Program Files (x86)\CodeBlocks\MinGW\include\GL
            glut.h      -> C:\Program Files (x86)\CodeBlocks\MinGW\include\GL
            glew.h      -> C:\Program Files (x86)\CodeBlocks\MinGW\include\GL

            y la carpeta completa
            glm         -> C:\Program Files (x86)\CodeBlocks\MinGW\include


            ACLARACI�N:
                Hay varias librer�as libglui32.a en la carpeta "otros"
                - Renombrar libglui32.10.05.a a libglui32.a para usar Code::Blocks 10.05
                - Renombrar libglui32.12.11.a a libglui32.a para usar Code::Blocks 12.11
                - Renombrar libglui32.13.12.a a libglui32.a para usar Code::Blocks 13.12 a 17.12
                - De momento no funciona con la versi�n Code::Blocks 20.03

****************************************************************************************************/

#include "Objects.h"
#include <GL\glui.h>

/**************************************** myGlutKeyboard() **********/

void Keyboard(unsigned char Key, int x, int y)
{
    switch(Key)
    {
        case 27:
        case 'q':
        case 'Q':
            exit(0);
            break;

    }

    glutPostRedisplay();
}

/**************************************** mySpecialKey() *************/

static void SpecialKey(int key, int x, int y)
{
    TPrimitiva *car = escena.GetCar(escena.seleccion);

    // Comprobar que el puntero car no sea NULL
    switch (key)
    {
        case GLUT_KEY_UP:   // El coche avanza
            car->rr += 8;
            car->gc += car->gr;
            car->tx += 0.3*sin(glm::radians(car->gc));
            car->tz += 0.3*cos(glm::radians(car->gc));
            break;
        case GLUT_KEY_DOWN:   // El coche retrocede
            car->rr -= 8;
            car->gc -= car->gr;
            car->tx -= 0.3*sin(glm::radians(car->gc));
            car->tz -= 0.3*cos(glm::radians(car->gc));
            break;
        case GLUT_KEY_LEFT:
            if(car->gr < 5.0){
                car->gr += 0.5;
            }
            break;
        case GLUT_KEY_RIGHT:
            if(car->gr > -5.0){
                car->gr -= 0.5;
            }
            break;
    }

    glutPostRedisplay();
}

/***************************************** myGlutMenu() ***********/

void Menu( int value )
{
  Keyboard( value, 0, 0 );
}

void Mouse(int button, int button_state, int x, int y )
{
    gui.Mouse(button, button_state, x, y);
}

void Render()
{
    escena.Render();
}
/*
void RenderSelection()
{
    escena.RenderSelection();
}

void processSelection(int xx, int yy)
{
    escena.processSelection(xx, yy);
}
*/
void Idle()
{
    gui.Idle();
}

void Reshape(int x, int y){
    gui.Reshape(x, y);
}

void Motion(int x, int y){
    gui.Motion(x, y);
}

/**************************************** main() ********************/

int main(int argc, char* argv[])
{

    // Inicializa GLUT and crea la ventana principal
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE );
    glutInitWindowPosition( 10, 10 );
    glutInitWindowSize( 1200, 800 );

    int main_window = glutCreateWindow( "CarGL V2.2 (2022) con Shaders" );

    // Inicializa los valores de OpenGL para esta Aplicaci�n
    escena.InitGL();
    gui.Init(main_window);

    glutDisplayFunc( Render );
    GLUI_Master.set_glutReshapeFunc( Reshape );
    GLUI_Master.set_glutKeyboardFunc( Keyboard );
    GLUI_Master.set_glutSpecialFunc( SpecialKey );
    GLUI_Master.set_glutMouseFunc( Mouse );
    glutMotionFunc( Motion );

    /**** We register the idle callback with GLUI, *not* with GLUT ****/
    GLUI_Master.set_glutIdleFunc( Idle );

    // Crea el escenario
    escena.CrearEscenario();

    /**** Regular GLUT main loop ****/
    glutMainLoop();

    return EXIT_SUCCESS;
}

