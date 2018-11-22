#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 in_texCoord;

out vec2 texCoord;

uniform int canvas_w, canvas_h, renderMode;

void main () {
    switch (renderMode) {
        case 1: // Render plot
            gl_Position = vec4 (pos, 0.0f, 1.0f);
            texCoord = in_texCoord;
            break;
        case 3: // Render axes
            gl_Position = vec4 (pos.x / (canvas_w / 2), pos.y / (canvas_h / 2), 0.0f, 1.0f);
            break;
    }
}
