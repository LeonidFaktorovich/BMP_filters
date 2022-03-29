# BMP_filters

Application works with file formats: bmp  
Filters supported by the application:  
crop (command: -crop width(integer value) height(integer value))  
crystallize (command: -crystal(integer value))  
edge detection (command: -edge threshold(floating number))  
blur (command: -blur sigma(floating number))  
grayscale (command: -gs)  
negative (command: -neg)  
reflection (command: -ref)  
rotation (command: -rot phi(integer value))  
sharpening (command: -sharp)  
The application takes as the first parameter the path to the original image,  
the second parameter is the path to write a new image, then there are commands for  
filters and their parameters as shown above.  
Program launch example:  
./image_processor before_filters.bmp after_filters.bmp -neg -rot 60 -edge 0.04 -crop 1000 1000  