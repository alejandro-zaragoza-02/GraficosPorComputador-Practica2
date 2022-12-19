
//precision mediump float;	// Precisión media, en algunas gráficas no se soporta (depende de la versión de GLSL), en ese caso comentar o quitar esta línea

varying vec4 v_Color;		// in: color del vertex shader
varying vec4 t_Color;

void main()
{
    		gl_FragColor = v_Color*t_Color;
}
