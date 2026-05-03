# Setup

To be most useful or even work at all, there are modifications to make to the crash screen system.

See the following commits in my `mod_base_for_mods` branch https://github.com/zeldaret/oot/compare/main...Dragorn421:mod_base_for_mods :

Required:

- Fix the built-in crash debugger
    - Without this fix, the crash screen itself crashes.

Recommended:

- Add `ALWAYS_GC_FAULT` option (default 1 (yes))
    - If building a N64 version of the game such as ntsc-1.0, the fault screen is an older version. This makes it so that the newer "gc" version of the fault screen is also used for N64 versions.
- Remove the button combo for starting the crash debugger
- Fill VPC in crash handler for actor overlays, to facilitate debugging
- Silence a spammy warning from the interrupt request manager under fault
