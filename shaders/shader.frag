#version 330 core

in vec2 texCoord;

out vec4 color;

uniform int renderMode;
uniform float renderMaximum;
uniform sampler2D plotTexture;

void main () {
    switch (renderMode) {
        case 1: // Render plot
            float val = texture (plotTexture, texCoord).r;
            color.r = (val > 0.f) ? val / renderMaximum : 0.f;
            color.g = (val > 0.f) ? (1 - val / renderMaximum) : (1 + val / renderMaximum);
            color.b = (val > 0.f) ? 0.f : (-val / renderMaximum);
            color.a = 1.f;
            break;
        case 3: // Render axes
            color = vec4 (0.f, 0.f, 0.f, 1.f);
            break;
    }
}
