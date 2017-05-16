This project is divided into 2 unit. 

1 ParsingJason, using object class, take Json file path as input and store Json value in this private variable 

2 tracing part. 

This part has 3 classes. Sphere class, Vector3d class and Plane class. 
Sphere class and Plane class handled the intersection of rays. Vector3d class handled vector calculation

//———————————————
Multi- threading
To implement multi-threading, i cut the image vertically into several pieces. Each pieces will calculated on one thread.