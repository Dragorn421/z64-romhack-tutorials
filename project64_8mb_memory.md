# Use 8 MB memory with Project64

One of the crashs often encountered is due to using a 4 MB memory size, when the game expects 8 MB. This explains how to change memory size from 4 MB to 8 MB in Project64.

This apparently isn't needed with recent development builds of Project64.

## Older Project64 versions

Screenshots made with Project64 `v2.3.2.202` (latest release build at time of writing).

Memory size is a per-rom settings and seems to default to 4 MB.

If you open the settings when emulation is not active:

![open project64 settings](https://421.es/doyu/1l58cc)

You only get those settings:

![project64 settings when not running](https://421.es/doyu/1l58fk)

So, load the ROM you want to set the memory size on and open the settings:

![open project64 settings when running](https://421.es/doyu/1l58i1)

It may seem that the game crashes immediately, staying still on a black screen such as:

![stuck on black screen after loading rom](https://421.es/doyu/1l58mr)

You can still proceed to opening the Settings window, click on `Config: ...` and locate `Memory size`:

![project64 game-specific settings with memory size](https://421.es/doyu/1l58rk)

You can then set `Memory size` to `8 MB`, it should look like this:

![project64 8mb memory size](https://421.es/doyu/1l58v5)

Click `OK` to save and exit the settings. You must then reset for the changes to be in effect:

![system > reset in project64 ui](https://421.es/doyu/1l58x1)

The game should now load fine.

You may need to set the memory size to 8 MB again after more modifications of the ROM!

## Recent Project64 versions

**Only in recent development builds** like Project64 `v2.4.0-1361-g1fad798`.

With such builds which you should **not have memory size issues** anyway, because it apparently defaults to 8 MB on "Unknown ROMs".

You can still set the per-game memory as in older Project64 versions [as described above](#older-project64-versions), but you can also set the default memory size in case it is required:

<details>

<summary>
Click to show instructions
</summary>

Screenshots made with Project64 `v2.4.0-1361-g1fad798` (latest development build at time of writing).

Open the Project64 settings through the menu at the top of the Project64 window:

![open settings button in pj64 ui](https://421.es/doyu/1l56zf)

Locate and unchecked the `Hide advanced settings` checkbox, to enable advanced settings:

![default pj64 settings](https://421.es/doyu/1l56pj)

`Defaults` and `Advanced` now appeared in the menu on the left, most importantly `Defaults`:

![pj64 settings with advanced settings shown](https://421.es/doyu/1l56s3)

Click `Defaults` and locate the `Memory size` dropdown. By default, it is set to `4 MB`:

![pj64 settings default memory size](https://421.es/doyu/1l56u9)

Set `Memory size` to `8 MB`. It should look like this:

![pj64 settings default memory size set to 8 MB](https://421.es/doyu/1l56w7)

Click `OK` to save and exit the settings.

</details>
