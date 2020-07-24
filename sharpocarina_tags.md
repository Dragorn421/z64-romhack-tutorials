# SharpOcarina tags

Tags are used to define some display and collision properties from Blender.

## `ModelFlags.xml`

From the folder where the `SharpOcarina.exe` executable is, can be found the file located at `XML/OOT/ModelFlags.xml`.

This file describes what tags can be used in Blender to directly set some model and collision settings in SharpOcarina, without using the interface. (tags may also be called flags)

## Adding tags

A `TagName` tag is added to an object in Blender by adding `#TagName` to its name. (names can be at most 63 characters long, this can be limiting)

<details>
<summary>Click here for an example</summary>
This adds `BackfaceCulling` and `Camera0` tags to the Cube, and the `Camera1` tag to the Plane:

![example tags in Blender (2.79)](https://421.es/doyu/1jmulc)
</details>

## Examples

In the interface, the "model settings" are located under `Group Settings` in the `Rooms` tab, and the "collision settings" are under `Polygon Types` in the `Collision & Exits` tab.

For example, in the collision settings can be found a `Hookshot-able` checkbox, the corresponding tag as can be found in `ModelFlags.xml` is `Hookshot`.

Tags can also define values, not only set a property like "is hookshot-able". For example, consider the following line from `ModelFlags.xml`:

```<!-- Flag Key="#Room" usage: #Room<number>, where <number> is the room number, this flag is only used if you press "Add multiple rooms"-->```

This means you can define what meshs are part of which room from Blender, by appending eg `#Room0` to the name of every mesh that should be in the first room.

## Tags priority

Mesh tags (the ones used for model settings, for displaying) are only applied on import or reload in SharpOcarina.

Collision tags are always enforced when exporting the map.

<details>
<summary>
Source

([Hylian Modding](https://discordapp.com/channels/388361645073629187/451783162859749386/728960330679451718))
</summary>

```
Nokaubure 2020-07-04T13:08:00Z
collision tags are absolute and take priority
but mesh tags all they do is checking the necessary checkboxes when you import the room or reload
so they're optional
with the exception of #Room and #NoMesh ofc
```
</details>

## Texture Tags

Tags can be added per-texture (`#ClampX`, `#ClampY`, `#MirrorX`, `#MirrorY`) by adding them to the image file name, like `texture#ClampX.png`.

<details>
<summary>
Source

([Hylian Modding](https://discordapp.com/channels/388361645073629187/451783162859749386/736185344004980816))
</summary>

```
2020-07-24T13:37:00Z
Dragorn421: could you confirm this (where should #ClampXY #MirrorXY go)
Nokaubure: inside texture filename
Dragorn421: do you allow texture#ClampX.png or do you require texture.png#ClampX
Nokaubure: the first
```
</details>
