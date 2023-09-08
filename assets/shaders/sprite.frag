#version 330 core
uniform sampler2D textureID;
in vec2 textureCoords;
uniform vec4 color;

void main()
{
  gl_FragColor = texture(textureID, textureCoords) * color;
}