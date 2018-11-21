#version 330 core

layout (location = 0) in vec2 pos;

uniform int canvas_w, canvas_h;

void main () {
    gl_Position = vec4 (pos.x / (canvas_w / 2), pos.y / (canvas_h / 2), 0.0f, 1.0f);
}
