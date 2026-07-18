# RayTracer

A simple raytracer built from scratch in C++ using the guidance from "Ray Tracing in One Weekend"

It features three materials: lambertan, metal, and glass.
Each of these can be used to change the appearance of a sphere.

The camera features variable fov, depth of field effect and multisample anti-aliasing.

##Try it out
To run the ray tracer run
`
main.exe <outputfile.cpp>
`

You then be able to choose between some default scenes.
Depending on how much sampling you choose and the size of the image. Rendering can take quite a while.
![Space](space.ppm)

![Marbles](marbles.ppm)

You can also choose to make your own scene.

For each sphere you want to create write a line

x y z radius material material-properties

After making generating all the spheres you can choose camera parameters like location, direction, fov, depth of field, multi-sampling and the width of the output image.

It will then render your image to the outputfile that you first specified.

Try and to make something like this

![Glass](glass.ppm)


