#version 330 core

in vec2 texCoord;

out vec4 color;

uniform int renderMode;
uniform sampler2D plotTexture;

void main () {
    switch (renderMode) {
        case 1: // Render plot
            color = texture (plotTexture, texCoord);
            break;
        case 3: // Render axes
            color = vec4 (0.0f, 0.0f, 0.0f, 1.0f);
            break;
    }
}
