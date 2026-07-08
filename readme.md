# Fractol - artcore

Got some awesome fractal render !

## Artcore
simlply do ```make artcore``` and you will got a fractol.png !

## The way its working
Launch `./fractol mandelbrot`, then go where you want with a low iteration count to have a fast preview, quit and it will output a fractol.frt file, then `./img_generator fractal.frt` and you will get the png !

My fractol wasnt build to go to certain coordinate, so i just output where i go in a .frt file then i create a little program img_generator that use that output to generate higher itteration png of the fractal (using a little lib for png named libattopng)
