# tetons

### Description

This project allows one to process 3 ppms where a consensus can be found among
most pixels to filter out extraneous objects in the image.

### Usage

##### Getting the Code.

To get and build the project, run through the following commands:

```bash
>$ git clone http://github.com/crockeo/tetons.git

>$ cd tetons/ # Moving into the directory.
>$ cmake .    # Generating a Makefile
>$ make       # Maing the project.

##### Program Commands

For running the program when you've built it (it'll need to be moved out of the
`bin` directory right after you build it), here are the possible commands:

```
# Making the image grayscale.
>$ tetons grayscale <img> <out>

# Flipping the image in the X-axis.
>$ tetons flipx <img> <out>

# Flipping the image in the Y-axis.
>$ tetons flipy <img> <out>

# Filtering out extraneous objects.
>$ tetons <img 1> <img 2> ... <img n> <out>
```

### License

Copyright (c) 2014 Cerek Hillen

Distributed under the MIT license.
