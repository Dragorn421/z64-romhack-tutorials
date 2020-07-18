Blender screenshots made with Blender 2.79

### Contents

 - [Enable backface culling in Blender](#enable-backface-culling-in-blender)
 - [Show face normals in Blender](#show-face-normals-in-blender)
 - [Flipping normals in Blender](#flipping-normals-in-blender)
 - [Making both front and back sides visible](#making-both-front-and-back-sides-visible)

# Backface Culling

Backface culling refers to faces not displaying if they are viewed from the back side.

<details>
<summary>Click here for an example demonstrating the difference between backface culling enabled (by default in SharpOcarina) and disabled (by default in Blender)</summary>
SharpOcarina:

![How it looks in SharpOcarina](https://421.es/doyu/1jmsf7)

Blender:

![How it looks in Blender (2.79)](https://421.es/doyu/1jmsin)
</details>

## Enable backface culling in Blender

![backface culling Blender 2.79 option](https://421.es/doyu/1jmoqx)

## Show face normals in Blender

What defines which side of a face is "back" or "front" is face normals, those can be seen in Blender in `Edit Mode`

![show normals in Blender 2.79](https://421.es/doyu/1jmota)

<details>
<summary>In Blender 2.82</summary>
 
![show normals in Blender 2.82](https://421.es/doyu/1kdad1)
</details>

## Flipping normals in Blender

To change which direction normals are facing, select the faces and use the flip normals operator.

The operator search is (by default) brought up by hitting `Space` in Blender 2.79, and `F3` in Blender 2.8x

![flip normals operator in Blender 2.79](https://421.es/doyu/1jmoua)

Result:

![after flip normals in Blender 2.79](https://421.es/doyu/1jmovq)

With backface culling enabled in Blender and after deleting the top face:

![easier to see result of flip normals](https://421.es/doyu/1jmowv)

## Making both front and back sides visible

For geometry that is actually supposed to be viewed from both sides (like a wall), backface culling can be disabled.

### Method 1: in the SharpOcarina interface

There is a `Backface Culling` checkbox that can be unticked for every mesh to disable backface culling for.

![backface culling checkbox in SharpOcarina](https://421.es/doyu/1jmthd)

### Method 2: in Blender with SharpOcarina tags

See [SharpOcarina tags](sharpocarina_tags.md) for an explanation of tags.

The `BackfaceCulling` tag can be used to disable backface culling on the desired objects (yes, the tag name is counter-intuitive).
