void kernel calculate (const global float *var_x, const global float *var_y, global float *out,
                       const float max, global float *rgb)
{
    int nx = get_global_id (0);
    int ny = get_global_id (1);
    int width = get_global_size (0);
    float x = var_x[nx];
    float y = var_y[ny];
    int out_pos = nx + ny * width;

    float val = - (cos(x*x + y*y)) / exp ((x*x + y*y) / 8.f);
    out[out_pos] = val;

    int rgb_pos = out_pos * 3;
    float min = -max;
    rgb[rgb_pos + 0] = (val > 0.f) ? (val / max) : 0.f;
    rgb[rgb_pos + 1] = (val > 0.f) ? (1 - val / max) : (1 - val / min);
    rgb[rgb_pos + 2] = (val > 0.f) ? 0.f : (val / min);
}
