// Helper to skip leading spaces
static int	skip_leading_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (i);
}

// Helper to find the actual end of content (excluding trailing spaces)
static int	find_content_end(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	// Move backwards to skip trailing spaces
	while (i > 0 && (line[i - 1] == ' ' || line[i - 1] == '\t'))
		i--;
	return (i);
}

int	check_space_map(t_map map)
{
	int	x;
	int	y;
	int	start_y;
	int	end_y;

	x = 1;
	while (x < map.rows - 1)
	{
		start_y = skip_leading_spaces(map.grid[x]);
		end_y = find_content_end(map.grid[x]);
		
		y = start_y;
		while (y < end_y)  // Only check up to content end
		{
			if (map.grid[x][y] == ' ' || map.grid[x][y] == '\t')
			{
				// Check all surrounding cells, but be careful with bounds
				if ((x > 0 && map.grid[x - 1][y] != '1' && map.grid[x - 1][y] != ' ') ||
					(x < map.rows - 1 && map.grid[x + 1][y] != '1' && map.grid[x + 1][y] != ' ') ||
					(y > 0 && map.grid[x][y - 1] != '1' && map.grid[x][y - 1] != ' ') ||
					(y < (int)ft_strlen(map.grid[x]) - 1 && map.grid[x][y + 1] != '1' && map.grid[x][y + 1] != ' '))
				{
					printf("Invalid map\nSpace must be surrounded by '1' or other spaces\n");
					printf("line: %s, position: %d, %d\n", map.grid[x], x, y);
					return (0);
				}
			}
			y++;
		}
		x++;
	}
	return (1);
}