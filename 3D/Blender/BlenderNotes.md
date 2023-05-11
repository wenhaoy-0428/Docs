# Blender

## How To

#### How to separate part of the object

1. select the part you want to separate. (X-RAY can be helpful selecting edges/faces behind the object)

2. press hotkey `p` and select `separate selected` to make the edges/faces their own object.


## Bevel

#### Default Bevelling 
Beveling is to add more geometries around the corners. The default way of adding Beveling is by

1. selecting the object first
2. hit `tab` to enter edit mode
3. If you decide to add corner to the edges of the object, simply use select edges on the top tool bar.
4. select all edges you wish to select by holding `shift` for selecting multiple ones.
5. then hit `cmd+b` or the bevel button on the left tool box. 
6. Adjust the `weight` and `segments` to your best fit.

However, the default Beveling has 1 major issue is that ones the effect is applied, there is no easy way to go back and undo the bevelling.

#### Bevel Modifier

Another way of doing this is to add Bevel Modifier to the selected object. This allows us to remove the bevelling by simply removing the modifier. However, unlike default bevel tool, where we can simply select edges we wish to bevel with simple clicks, bevel modifier doesn't allow us to manually select. 

Bevel Modifier provides a limit check property which acts as a filter. We can increase the bevel weight on the selected edges and use bevel weight to filter them.

A detail demonstration can be found at [Bevel Better with the Bevel Modifier | Blender 2.93](https://www.youtube.com/watch?v=ID09Y28kvTo). 

> For how bevel width works, the video is also a great reference to watch.


## Material

#### [How to add material to different faces of an object](https://artisticrender.com/how-to-assign-materials-to-objects-and-faces-in-blender/0)

1. Select an object and enter edit mode by press `tab` 

2. Select the 3rd select tool on the top tool bar to select faces.

3. Assign them to an existing Martial that is already applied to the object.


### Extrude 

Hit `E` to add extra surfaces.

## Exporting

When exporting, procedural materials are not properly exported as they only work with Blender. To properly export them, we have to **bake** them into image texture. A reference can be found here [Some textures missing after exporting to Gltf](https://blender.stackexchange.com/questions/242552/some-textures-missing-after-exporting-to-gltf)


### Baking procedural materials


To bake a procedural material in Blender, we have to first unwrap the 3D texture into 2D image texture. UV/ImageEditor is the one to help us do this. 

>> What is UV?
> In 3D computer graphics, UV refers to the 2D coordinate system used to map a 2D image onto a 3D object.

> The letters "UV" refer to the axes of this coordinate system, where "U" corresponds to the horizontal direction and "V" corresponds to the vertical direction. The term "UV mapping" is used to describe the process of creating a 2D texture image that can be applied to a 3D object using this coordinate system.

> UV mapping is important because it allows artists and designers to create complex and detailed textures that can be applied to 3D objects. By mapping the texture image onto the 3D model using UV coordinates, the texture can be stretched, scaled, and distorted to fit the 3D geometry of the object, creating a realistic and detailed surface.

> UV coordinates are typically created by "unwrapping" the 3D model into a 2D flat surface, which can then be edited in a 2D image editing program like Photoshop or GIMP. Once the texture is edited, it can be re-applied to the 3D model using the UV coordinates.

The basic process is that:

1. we select the faces/object with the material we wish to bake. 
2. Then unwrap the shape of the 3D model into 2D using UV mapping.
3. Select the properties of the material to bake individually (color, roughness, normal) into images respectively.
4. Remap the procedural nodes to the image texture. 
5. Export as normal.

> Some of the properties, such as color, requires `metallic` to be 0 to be baked properly.

Now, with the basic idea of what's going on. This is an excellent tutorial on how to manage this [How to Bake Metallic Maps in Blender (Tutorial)](https://www.youtube.com/watch?v=aaRspfc9OBU)

!> During baking, make all color spaces of all mapping to `non-color` except for base color. Otherwise, the result of baking may not work as expected. 

> As for `metallic` mapping, unplug all attributes and plug the metallic mapping to `emission` and bake `emit` instead, then plug the generated image texture to `metallic`

