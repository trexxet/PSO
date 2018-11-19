void kernel calc_coordinate_map (const float step_x, const float step_y,
                                 global float* out_x, global float* out_y)
{
    int w = get_global_size (0);
    int h = get_global_size (1);
    int x = get_global_id (0);
    int y = get_global_id (1);
    out_x[x] = (x - w / 2) * step_x;
    out_y[y] = (h / 2 - y) * step_y;
}
