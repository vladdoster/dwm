/*
 * @Author: Vlad Doster <mvdoster@gmail.com>
 * @Date: 2020-06-22 11:49:08
 * @Last Modified by: Vlad Doster <mvdoster@gmail.com>
 * @Last Modified time: 2020-06-22 12:25:27
 */

/* See LICENSE file for copyright and license details. */

/* Appearance */
static const unsigned int borderpx = 3; /* border pixel of windows */
static const unsigned int gappx = 5;    /* gap pixel between windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int swallowfloating = 0;   /* 1 means swallow floating windows by default */
static const int showbar = 1; /* 0 means no bar */
static const int topbar = 0;  /* 0 means bottom bar */
static const char *fonts[] = { "Source Code Pro:size=10:antialias=true:autohint=true" };
static char dmenufont[] =      "Source Code Pro:size=15";
static char normbgcolor[] =     "#1c1c1c";
static char normbordercolor[] = "#444444";
static char normfgcolor[] =     "#bbbbbb";
static char selfgcolor[] =      "#ffffff";
static char selbordercolor[] =  "#9d0006";
static char selbgcolor[] =      "#484848";
static char *colors[][3] = {
    /*   fg            bg           border     */
    [SchemeNorm] = {normfgcolor, normbgcolor, normbordercolor},
    [SchemeSel] =  {selfgcolor, selbgcolor, selbordercolor},
    /* color bar */
    [SchemeStatus] =   {"#000000", "#5F6A6A", "#000000"}, // statusbar right
    [SchemeTagsSel] =  {"#000000", "#076678", "#1c1c1c"}, // tag bar left selected
    [SchemeTagsNorm] = {"#000000", "#5F6A6A", "#000000"}, // tag bar left unselected
    [SchemeInfoSel] =  {"#000000", "#5F6A6A", "#000000"}, // info bar middle  selected
    [SchemeInfoNorm] = {"#000000", "#5F6A6A", "#000000"}, // info bar middle  unselected
};

typedef struct {
  const char *name;
  const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL};
const char *spcmd2[] = {"st", "-n",    "spcalc", "-f", "monospace:size=16",
                        "-g", "50x20", "-e",     "bc", "-lq",
                        NULL};
static Sp scratchpads[] = {
    /* name          cmd  */
    {"spterm", spcmd1},
    {"spranger", spcmd2},
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
static const Rule rules[] = {
    /* class    instance     title       tags mask  isfloating    isterminal  noswallow  monitor */
    {"St",       NULL,       NULL,          0,          0,            1,          0,       -1},
    {NULL,       NULL,      "Event Tester", 0,          0,            0,          1,       -1},
    {NULL,      "spterm",    NULL,          SPTAG(0),   1,            1,          0,       -1},
    {NULL,      "spcalc",    NULL,          SPTAG(1),   1,            1,          0,       -1},
};

/* Layout(s) */
static const int dirs[3] =     {DirHor, DirVer, DirVer}; /* tiling dirs */
static const float facts[3] =  {1.1, 1.1, 1.1};          /* tiling facts */
static const int nmaster =     1;                        /* number of clients in master area */
static const int resizehints = 1;                        /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT  1     /* nrowgrid layout: force two clients to always split vertically */

static const Layout layouts[] = {
    {"[tiled]", tile},      /* Master on left, slaves on right */
    {"[monocle]", monocle}, /* All windows on top of eachother */
    {NULL, NULL},           /* Description here would be point(er)less */
};

/* Key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},
#define TILEKEYS(MOD, G, M, S)                                                 \
  {MOD, XK_r, setdirs, {.v = (int[]){INC(G * +1), INC(M * +1), INC(S * +1)}}}, \
      {MOD,                                                                    \
       XK_h,                                                                   \
       setfacts,                                                               \
       {.v = (float[]){INC(G * -0.1), INC(M * -0.1), INC(S * -0.1)}}},         \
      {MOD,                                                                    \
       XK_l,                                                                   \
       setfacts,                                                               \
       {.v = (float[]){INC(G * +0.1), INC(M * +0.1), INC(S * +0.1)}}},
#define STACKKEYS(MOD, ACTION)                                                 \
  {MOD, XK_j, ACTION##stack, {.i = INC(+1)}},                                  \
      {MOD, XK_k, ACTION##stack, {.i = INC(-1)}},                              \
      {MOD, XK_v, ACTION##stack, {.i = 0}},

/* Helper for spawning shell commands */
#define SHCMD(cmd) { .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL } }

/* Commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {"dmenu_run", "-m",  dmenumon,    "-fn",
                                 dmenufont,   "-nb", normbgcolor, "-nf",
                                 normfgcolor, "-sb", selbgcolor,  "-sf",
                                 selfgcolor,  NULL};
static const char *termcmd[] = {"st", NULL};

#include "shiftview.c"
#include <X11/XF86keysym.h>
static Key keys[] = {
    STACKKEYS(MODKEY, focus) STACKKEYS(MODKEY | ShiftMask, push)
    /* Layout bindings  */
    TAGKEYS(XK_1, 0) 
    TAGKEYS(XK_2, 1)
    TAGKEYS(XK_3, 2)
    TAGKEYS(XK_4, 3)
    TAGKEYS(XK_5, 4)
    TAGKEYS(XK_6, 5) 
    TAGKEYS(XK_7, 6)
    TAGKEYS(XK_8, 7)
    TAGKEYS(XK_9, 8)
    /* Xtile bindings  */
    TILEKEYS(MODKEY,                           1, 0, 0) 
    TILEKEYS(MODKEY | ShiftMask,               0, 1, 0)
    TILEKEYS(MODKEY | ControlMask,             0, 0, 1)
    TILEKEYS(MODKEY | ShiftMask | ControlMask, 1, 1, 1)
    /* modifier            key              function                    argument  */
    {MODKEY,               XK_0,             view,               {.ui = ~0}},
    {MODKEY | ShiftMask,   XK_0,             tag,                {.ui = ~0}},
    {MODKEY,               XK_t,             setlayout,          {.v = &layouts[0]}}, /* xtile */
    {MODKEY | ShiftMask,   XK_u,             setlayout,          {.v = &layouts[1]}}, /* monocle */
    /* Alphabetic keys */
    {MODKEY,               XK_b,             togglebar,          {0}},
    {MODKEY,               XK_c,             killclient,         {0}},
    {MODKEY,               XK_d,             spawn,              {.v = dmenucmd}},
    {MODKEY,               XK_e,             spawn,              SHCMD("st -e nvim")},
    {MODKEY,               XK_f,             spawn,              SHCMD("st -e ranger")},
    {MODKEY | ShiftMask,   XK_f,             togglefullscr,      {0}},
    {MODKEY,               XK_g,             shiftview,          {.i = -1}},
    {MODKEY | ShiftMask,   XK_g,             shifttag,           {.i = -1}},
    {MODKEY | ShiftMask,   XK_h,             spawn,              SHCMD("st -e htop")},
    {MODKEY | ShiftMask,   XK_l,             setdirs,            {.v = (int[]){DirHor, DirVer, DirVer}}},
    {MODKEY | ControlMask, XK_l,             setdirs,            {.v = (int[]){DirVer, DirHor, DirHor}}},
    {MODKEY,               XK_m,             spawn,              SHCMD("dmenu_music_options")},
    {MODKEY | ShiftMask,   XK_m,             spawn,              SHCMD("pamixer --toggle-mute; kill -44 $(pidof dwmblocks)")},
    {MODKEY,               XK_n,             spawn,              SHCMD("st -e nvim -c VimwikiIndex")},
    {MODKEY,               XK_o,             incnmaster,         {.i = +1}},
    {MODKEY | ShiftMask,   XK_o,             incnmaster,         {.i = -1}},
    {MODKEY,               XK_s,             swapfocus,          {.i = -1}},
    {MODKEY | ShiftMask,   XK_s,             togglesticky,       {0}},
    {MODKEY,               XK_w,             spawn,              SHCMD("$BROWSER")},
    {MODKEY | ShiftMask,   XK_w,             spawn,              SHCMD("st -e sudo nmtui")},
    /* Punctuation keys */
    {MODKEY,               XK_apostrophe,    togglescratch,      {.ui = 0}}, /* terminal scratchpad */
    {MODKEY | ShiftMask,   XK_apostrophe,    togglescratch,      {.ui = 1}}, /* bc scratchpad */
    {MODKEY,               XK_BackSpace,     spawn,              SHCMD("dmenu_system_functions")},
    {MODKEY | ShiftMask,   XK_BackSpace,     spawn,              SHCMD("dmenu_system_functions")},
    {MODKEY,               XK_grave,         spawn,              SHCMD("dmenu_unicode")},
    {MODKEY,               XK_minus,         spawn,              SHCMD("pamixer -d 5;  kill -44 $(pidof dwmblocks)")},
    {MODKEY | ShiftMask,   XK_minus,         spawn,              SHCMD("pamixer -d 15; kill -44 $(pidof dwmblocks)")},
    {MODKEY,               XK_equal,         spawn,              SHCMD("pamixer -i 5;  kill -44 $(pidof dwmblocks)")},
    {MODKEY | ShiftMask,   XK_equal,         spawn,              SHCMD("pamixer -i 15; kill -44 $(pidof dwmblocks)")},
    {MODKEY,               XK_space,         zoom,               {0}},
    {MODKEY | ShiftMask,   XK_space,         togglefloating,     {0}},
    {MODKEY,               XK_Tab,           view,               {0}},
    {MODKEY,               XK_semicolon,     shiftview,          {.i = 1}},
    {MODKEY | ShiftMask,   XK_semicolon,     shifttag,           {.i = 1}},
    {MODKEY,               XK_t, spawn,                          {.v = termcmd}},
    /* Navigation keys */
    {MODKEY,               XK_Left,          focusmon,           {.i = -1}},
    {MODKEY | ShiftMask,   XK_Left,          tagmon,             {.i = -1}},
    {MODKEY,               XK_Right,         focusmon,           {.i = +1}},
    {MODKEY | ShiftMask,   XK_Right,         tagmon,             {.i = +1}},
    {MODKEY,               XK_Page_Up,       shiftview,          {.i = -1}},
    {MODKEY | ShiftMask,   XK_Page_Up,       shifttag,           {.i = -1}},
    {MODKEY,               XK_Page_Down,     shiftview,          {.i = +1}},
    {MODKEY | ShiftMask,   XK_Page_Down,     shifttag,           {.i = +1}},
    {MODKEY,               XK_Insert,        spawn,              SHCMD("show_clipboard_contents")},
    {0,                    XK_Print,         spawn,              SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png")},
    {ShiftMask,            XK_Print,         spawn,              SHCMD("dmenu_maim_pick")},
    {MODKEY,               XK_Print,         spawn,              SHCMD("dmenu_record")},
    {MODKEY | ShiftMask,   XK_Print,         spawn,              SHCMD("dmenu_record kill")},
    {MODKEY,               XK_Scroll_Lock,   spawn,              SHCMD("killall screenkey || screenkey &")},
    /* Function keys */
    {MODKEY,               XK_F3,            spawn,              SHCMD("dmenu_display_options")},
    {MODKEY,               XK_F4,            spawn,              SHCMD("dmenu_music_options; kill -44 $(pidof dwmblocks)")},
    {MODKEY,               XK_F5,            xrdb,               {.v = NULL}},
};

/* Button definitions */
static Button buttons[] = {
    /* click            event mask      btn       function        arg */
    {ClkClientWin,        MODKEY,     Button1,    movemouse,      {0}},
    {ClkClientWin,        MODKEY,     Button3,    resizemouse,    {0}},
    {ClkRootWin,            0,        Button2,    togglebar,      {0}},
    {ClkStatusText,         0,        Button1,    sigdwmblocks,   {.i = 1}},
    {ClkStatusText,         0,        Button2,    sigdwmblocks,   {.i = 2}},
    {ClkStatusText,         0,        Button3,    sigdwmblocks,   {.i = 3}},
    {ClkStatusText,         0,        Button4,    sigdwmblocks,   {.i = 4}},
    {ClkStatusText,         0,        Button5,    sigdwmblocks,   {.i = 5}},
    {ClkStatusText,     ShiftMask,    Button1,    sigdwmblocks,   {.i = 6}},
    {ClkStatusText,     ShiftMask,    Button3,    spawn,          SHCMD("st -e nvim ~/.local/src/dwmblocks.git/config.h")},
    {ClkTagBar,             0,        Button1,    view,           {0}},
    {ClkTagBar,             0,        Button3,    toggleview,     {0}},
    {ClkTagBar,             0,        Button4,    shiftview,      {.i = -1}},
    {ClkTagBar,             0,        Button5,    shiftview,      {.i = 1}},
    {ClkTagBar,           MODKEY,     Button1,    tag,            {0}},
    {ClkTagBar,           MODKEY,     Button3,    toggletag,      {0}},
    {ClkWinTitle,           0,        Button2,    zoom,           {0}},
};
