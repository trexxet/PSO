void kernel calculate (const global float *var_x, const global float *var_y, global float *out)
{
    int nx = get_global_id (0);
    int ny = get_global_id (1);
    int width = get_global_size (0);
    float x = var_x[nx];
    float y = var_y[ny];
    int out_pos = nx + ny * width;

    float val = - (cos(x) * cos(y)) / exp ((x*x + y*y) / 32.f);
    out[out_pos] = val;
}
