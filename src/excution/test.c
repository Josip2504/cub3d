/* void draw_ceiling_floor(t_mlx *mlx, int ray, int top_pixel, int bottom_pixel)
{
    int y;
    int floor_color;
    int ceiling_color;

    // Convert color values (assuming floor and ceiling are integers, not strings)
    floor_color = rgb_color(mlx->data->floor[0], mlx->data->floor[1], mlx->data->floor[2], 255);
    ceiling_color = rgb_color(mlx->data->ceil[0], mlx->data->ceil[1], mlx->data->ceil[2], 255);

    // Draw the floor
    y = bottom_pixel;
    while (y < S_H)
    {
        if (ray >= 0 && ray < S_W && y >= 0 && y < S_H)
            mlx_put_pixel(mlx->imgage, ray, y, floor_color);
        y++;
    }

    // Draw the ceiling
    y = 0;
    while (y < top_pixel)
    {
        if (ray >= 0 && ray < S_W && y >= 0 && y < S_H)
            mlx_put_pixel(mlx->imgage, ray, y, ceiling_color);
        y++;
    }
}
 */

/* uint32_t rgb_color(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

mlx_texture_t	*get_wall_color(t_mlx *mlx, int flag)
{
	double angle = mlx->ray->angle;

	// Normalize angle directly within the function
	while (angle < 0)
		angle += (2 * M_PI);
	while (angle > 2 * M_PI)
		angle -= (2 * M_PI);

	// Determine texture based on ray direction and flag
	if (flag == 0)  // Vertical wall
	{
		// Check if ray is hitting the west or east wall
		if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
			return (mlx->textur->west);  // West wall
		else
			return (mlx->textur->east);  // East wall
	}
	else  // Horizontal wall
	{
		// Check if ray is hitting the north or south wall
		if (angle > 0 && angle < M_PI)
			return (mlx->textur->south);  // South wall
		else
			return (mlx->textur->north);  // North wall
	}
}

void draw_wall(t_mlx *mlx, int t_pix, int b_pix, double wall_h)
{
    double          x_offset;
    double          y_offset;
    double          factor;
    uint32_t        *pixels;
    mlx_texture_t   *texture;
    double          dist_to_wall;
    double          wall_hit_pos;

    // Get the correct wall texture based on the flag.
    texture = get_wall_color(mlx, mlx->ray->wall_flag);  
    pixels = (uint32_t *)texture->pixels;  // Access texture pixel data.
    factor = (double)texture->height / wall_h;  // Calculate y-axis scaling factor.

    // Calculate the x offset based on the player's position and ray's angle.
    dist_to_wall = mlx->ray->distance;
    if (mlx->ray->wall_flag == 1)  // If it's a horizontal wall hit.
        wall_hit_pos = mlx->ply->player_x + dist_to_wall * cos(mlx->ray->angle);
    else  // Vertical wall hit.
        wall_hit_pos = mlx->ply->player_y + dist_to_wall * sin(mlx->ray->angle);
    
    // Calculate x offset directly.
    x_offset = fmod(wall_hit_pos, TILE_SIZE) / TILE_SIZE * texture->width;

    // Calculate the initial y offset for texture.
    y_offset = (t_pix - (S_H / 2) + (wall_h / 2)) * factor;
    if (y_offset < 0)
        y_offset = 0.0;  // Ensure y_offset doesn't go below 0.

    // Render the wall section by placing pixels between t_pix and b_pix.
    while (t_pix < b_pix)
    {
        // Draw a pixel from the texture at the current x and y offset.
        my_mlx_pixel_put(mlx, mlx->ray->index, t_pix,
            get_color(pixels[(int)y_offset * texture->width + (int)x_offset]));
        
        y_offset += factor;  // Increment y_offset for the next pixel.
        t_pix++;
    }
} */

/* unsigned int	get_color(int c)
{
	return (((c & 0x000000FF) << 24) | ((c & 0x0000FF00) << 8)
		| ((c & 0x00FF0000) >> 8) | ((c & 0xFF000000) >> 24));
} */