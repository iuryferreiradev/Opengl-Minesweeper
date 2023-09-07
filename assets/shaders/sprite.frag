#version 330 core
uniform sampler2D textureID;
in vec2 textureCoords;

void main()
{
  gl_FragColor = texture(textureID, textureCoords);
}