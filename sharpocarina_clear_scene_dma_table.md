# SharpOcarina: clear scene dma table

One of the crashes often encountered when loading maps injected with SharpOcarina can be avoided thanks to another SharpOcarina feature.

Consider using [zzrtl](http://www.z64.me/tools/zzrtl) instead for injecting maps exported from SharpOcarina, if you want to make managing files easier. It removes the cause of this issue at its root.

## Instructions

In SharpOcarina, under `Tools`, click `Clear scene DMA table (all)`

![Tools > Clear scene DMA table in SharpOcarina ui](https://421.es/doyu/1l59b2)

If you are in `Global ROM Mode` the Global ROM will be modified, otherwise you will be prompted for the ROM file to edit in-place.

This only has to be done once per ROM file.

This prevents compressing the ROM. Use `Rebuild DMA table` before compressing.

Apparently for MM `Rebuild DMA table` is mandatory for the game to work?

## Explanations

The [DMA table](https://wiki.cloudmodding.com/oot/Filesystem) lists all the files stored in ROM, including their size. When you inject your map into the rom, the corresponding files overwrite existing ones, but their size may be bigger. Because the DMA table is not updated, it then means that the game only loads a fraction of the file that was initially injected, and it usually leads to a crash when reading the data when loading the map.

[zzrtl](http://www.z64.me/tools/zzrtl) rebuilds the whole rom, including the dma table, which makes this a non-issue when using it.
