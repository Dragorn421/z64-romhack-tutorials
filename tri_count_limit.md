# Tri count limit

From a romhacking perspective, there are two types of tris: displayed tris, and collision tris. They are used by two main components of the game: maps and actors.

## For maps

Tri count usage by maps is only **limited by lag**. Usual "limits" before fps drops are **in the thousands** for each type (displayed/collision).

Collision tris aren't directly limited, but the amount of vertices making the collision tris must not be more than **8192 vertices for collision**.

Though, for displayed tris, proper **culling** can do wonders. Some scene ids also are associated to unoptimized collision computation, avoid those for complex scenes.

And since lag also depends on how much is going on in the scene (for example amount/variety/complexity of actors) it means an acceptable tri count really **varies a lot depending on context**.

For **multi-room scenes**: keep in mind two rooms may be loaded at the same time (for example during transitions), and that the whole map collision is entirely loaded at all times, regardless of what room you're in, but that displayed tris are only from the currently loaded rooms.

It is unlikely that you get limited by ROM/RAM in how much tris to put into a map.

If using decomp, you can edit collision parameters in code (see `BgCheck_Allocate` in z_bgcheck.c) to match your memory/performance needs.

## For actors

Again, the only limit for displayed tris by an actor is **lag**, which again makes it **depend on context**.

However, there is a limit for collision tris (`dynapoly`) of **512 tris, 512 vertices for dynapoly collision** (or more rarely 256, see decomp for details).

The memory size available for loaded objects is roughly **1 MB** and may become a constraint for putting a lot of different actors in a scene.

## Sources

Considered "a lot" in a map context: 3000, 1500, 1000

Considered "ok" in a map context: 850, 1000, 2000

<details>
<summary>
8192 vertices max for map collision

([Hylian Modding](https://discordapp.com/channels/388361645073629187/451783162859749386/551920484632100874))
</summary>

```
2019-03-04T00:14:00Z
Nokaubure: Verts is the vertex count, this is limited to 8192 on collision mesh, higher than that will crash/remove collision ingame
```
</details>

<details>
<summary>
scene ids with unoptimized collision

([Hylian Modding](https://discordapp.com/channels/388361645073629187/388362111534759942/593074065724538891))
</summary>

```
2019-06-25T13:44:00Z
Nokaubure: 36 non-optimized collision, use for houses only
```
</details>

[z_bgcheck.c in decomp](https://github.com/zeldaret/oot/blob/5c4fdb706b51350c6de10e0a20c2e01476c98e52/src/code/z_bgcheck.c#L1491) (thanks mzx for decompiling z_bgcheck and noticing this file could make use of it)
