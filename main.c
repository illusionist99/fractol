#include <math.h>
#include <mlx.h>
#include <complex.h>

# define width 900
# define height 900
# include <stdio.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;
double gx = 0;
// Basic algorthm
void *image;
char *buffer;
// typedef double complex;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

    if (x <= 0 || x >= width || y <= 0 || y >= height)
        return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
# define abs(x) x < 0 ? -x : x
double squared_modules(double x, double y) {

    return (sqrt(x*x  + y*y));
}

float   normalize(float value, float start, float stop, float start1, float  stop1) {

    return (((stop1 - start1) * value)/stop + start1);
}

int color(int r, int g, int b) {

    return (r * 65536 + g * 256 + b);
}
# define iteration 50
void    mandelbrot_set(t_data *data) {

    int x = 0;
    int y;
    float a;
    float b;
    int  iterations;
    float z;
    float aa;
    float bb;
    float bright;
    int colors[3];

    colors[0] = 0xFFFFFF;
    colors[1] = 0;
    while (x < width) 
    {
        y = 0;
        while (y  < height)
        {
            a = normalize(x, 0, width, -2, 2);
            b = normalize(y, 0, height, -2, 2);
            // printf("a is : %f | b is : %f \n", a, b);
            iterations = 0;
            z = 0;
            float sa = a;
            float sb = b;
            while (iterations < iteration)
            {
                aa = a*a - b*b;
                bb = 2 * a * b;

                a = sa + aa;
                b = sb + bb;
                // printf("value is %f\n", aa + bb );
                if (a + b > 16)
                    break ;
                iterations++;
            }
            bright = normalize(iterations, 0, iteration, 0 ,255);
            my_mlx_pixel_put(data, x, y, color(cos(bright) * 255, sin(bright) * 255 , tan(bright)) % 255);
            y++;
        }
        
        x++;
    }
    
}
    

void    julia_set(t_data *data) {

    int x = 0;
    int y = 0;
    float sx;
    float xtemp;
    float cx;
    float cy;
    float colors;
    float sy;
    int iterations=0;
    # define n 20
    while (x < width)
    {
        y =0;
        while (y < height)
        {
            sx = normalize(x, 0, width, -2, 2);
            sy = normalize(y, 0, height, -2, 2);
            iterations = 0;
            while (iterations < iteration && sx*sx + sy*sy < 4)
            {
                xtemp = powf((sx * sx + sy * sy), (n / 2) * cos(n * atan2(sy, sx))) + sx;
                sy = powf((sx * sx + sy * sy) , (n / 2) * sin(n * atan2(sy, sx))) + sy;
                sx = xtemp;
                // xtemp = sx * sx - sy * sy;
                // sy = 2 * sx * sy  + sy;
                // sx = xtemp + sx;
    
                iterations++;
            }
            colors = normalize(iterations, 0, iteration, 0 ,255);
            if (iterations == iteration)
                my_mlx_pixel_put(data, x, y, color(colors , colors, colors));
            else
                my_mlx_pixel_put(data, x, y, color(0,0,0));
            y++;
        }
        
        x++;
    }
    
}

int	main(void)
{
	void	*mlx;
	t_data	img;
	void	*mlx_win;

	mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, width, height, "Hello world!");
	img.img = mlx_new_image(mlx, width, height);
	/*
	** After creating an image, we can call `mlx_get_data_addr`, we pass
	** `bits_per_pixel`, `line_length`, and `endian` by reference. These will
	** then be set accordingly for the *current* data address.
	*/
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	
    mandelbrot_set(&img);
    // julia_set(&img);

    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}