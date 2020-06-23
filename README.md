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
     - xtile
     - monocle
     - true fullscreen (prevents focus shifting)
- DWM blocks: Statusbar with my build of [dwm blocks](https://github.com/vladdoster/dwm-blocks).
- XRDB: Read colors from xrdb (.Xresources) at run time.
- Scratchpads: Allows you to spawn or restore a floating terminal windows.
- Sticky: A sticky client is visible on all tags.
- Stacker: Move windows up the stack manually.
- Shift view: Cycle through tags.
- Swap focus: Single shortcut to reach last used window instead of having to think if you should use alt-j or alt-k.
- Useless gaps: Gaps allowed across all layouts.
- Swallow: If a program run from a terminal would make it inoperable, it temporarily takes its place to save space.
- Color bar: Change the foreground and background color of every statusbar element.
- No border: No border if single window on tag
- Per-tag layout: Keeps layout, mwfact, barpos and nmaster per tag.
- Cycle layouts: Cycles through all avaiable layouts
- X-tile: 
     - Generalization of the tile layout which adds two attributes (direction and fact) to three areas (global, master, stack). 
     - Global area is the entire allocatable visual space and it's subdivided into the master and stack subareas.
