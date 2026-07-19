# RayTracer

A simple raytracer built from scratch in C++ using the guidance from "Ray Tracing in One Weekend"

It features three materials: lambertan, metal, and glass.
Each of these can be used to change the appearance of a sphere.

The camera features variable fov, depth of field effect and multisample anti-aliasing.

# Try it out

To run the ray tracer run

`./raytracer.exe <output-file.cpp>`

Then choose between rendering a **_default scene_** or **_creating your own_**.

<br>

## Default Scene

There are two default scenes that you can choose to render.
Depending on how much sampling you choose and the size of the image. Rendering can take quite a while.

### Space

![Space](./images/space.png)

### Marbles

![Marbles](./images/marbles.png)

<br>

## Make Your Own

To create your own scene you will need to input each sphere you want to render, and then the camera and render properties for your image.

For each sphere you want to create input the line:

`x y z radius material material-properties`

After making generating all the spheres you can choose camera parameters like **_location_**, **_direction_**, **_fov_**, **_depth of field_**, **_multi-sampling_** and the **_width_** of the output image.

It will then render your image to the **_output file_** that you first specified.

![Glass](./images/glass.png)

<br>

## Viewing the image

Since the image is stored in a **_ppm_**, you will need to find some way to view the image.
I used this vscode extension

![Install Extension](vscode:extension/ngtystr.ppm-pgm-viewer-for-vscode)
