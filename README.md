<div align=center>

<img src="https://dwm.suckless.org/dwm.svg"
     data-canonical-src="https://dwm.suckless.org/dwm.svg"
     width="200"
     height="100" />

#### Personal build of Dynamic Window Manager (DWM)
This is suckless, the source code is the documentation! Check out [config.h](config.h).

</div>

## Patches and features

- Layouts:
     - floating
     - monocle
     - true fullscreen
     - x-tile
- Color bar: Change the foreground and background color of every statusbar element.
- Cycle layouts: Cycles through all avaiable layouts
- DWM blocks: Statusbar with my build of [dwm blocks](https://github.com/vladdoster/dwm-blocks).
- No border: No border if single window on tag
- Per-tag layout: Keeps layout, mwfact, barpos and nmaster per tag.
- Scratchpads: Allows you to spawn or restore a floating terminal windows.
- Shift view: Cycle through tags.
- Stacker: Move windows up the stack manually.
- Sticky: A sticky client is visible on all tags.
- Swallow: If a program run from a terminal would make it inoperable, it temporarily takes its place to save space.
- Swap focus: Single shortcut to reach last used window instead of having to think if you should use alt-j or alt-k.
- Useless gaps: Gaps allowed across all layouts.
- XRDB: Read colors from xrdb (.Xresources) at run time.
- X-tile: 
     - Generalization of the tile layout which adds two attributes (direction and fact) to three areas (global, master, stack). 
     - Global area is the entire allocatable visual space and it's subdivided into the master and stack subareas.
