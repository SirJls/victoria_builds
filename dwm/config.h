/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "Cousine:size=10";
#define NUMCOLORS 7
static const char colors[NUMCOLORS][ColLast][8] = {
    // border    foreground background
    { "#212121", "#202020", "#303030" }, /* 1 = selected */
    { "#decc94", "#ffffff", "#303030" }, /* 2 = bar */
    { "#212121", "#decc94", "#303030" }, /* 3 = green */
    { "#212121", "#b23636", "#303030" }, /* 4 = yellow */
    { "#212121", "#b23636", "#303030" }, /* 5 = red */
    { "#212121", "#dec994", "#303030" }, /* 6 = magenta */
    { "#212121", "#c0c0c0", "#303030" }, /* 7 = grey */
};
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 8;        /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "base", "web", "term", "mail", };

static const Rule rules[] = {
    /* class        instance    title       tags mask     isfloating   monitor */
   { "Vimb",        NULL,       NULL,       1 << 1,       False,       -1 },
   { "Tabbed",      NULL,       NULL,       1 << 1,       False,       -1 },
   { "Skype",       NULL,       NULL,       1 << 0,       True,        -1 },
   { "Mpv",         NULL,       NULL,       1 << 0,       True,        -1 },
   { "Gimp",        NULL,       NULL,       1 << 0,       True,        -1 },
   { "Pcmanfm",     NULL,       NULL,       1 << 0,       True,        -1 },
   {  NULL,         NULL,      "mutt",      1 << 3,       False,       -1 },
   {  NULL,         NULL,      "tmux",      1 << 2,       False,       -1 },
   {  NULL,         NULL,      "ssh",       1 << 0,       False,       -1 },
   {  NULL,         NULL,      "scratchpad",     0,       True,        -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False;/* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[T]",      tile },    /* first entry is default */
    { "[F]",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
    { "[@]",      spiral },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[]   = { "dmenu_run", "-i", "-p", "Run it:", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG],"-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL };
static const char *ncmpcppcmd[] = { "termite", "-e", "ncmpcpp", NULL };
static const char *termcmd[]    = { "termite", NULL };
static const char *xtermcmd[]   = { "xterm",  NULL };
static const char *mailcmd[]    = { "termite", "--title", "mutt", "-e", "mutt", NULL };
static const char *tmuxcmd[]    = { "termite", "--title", "tmux", "-e", "tmux", "-f", "/home/jls/.tmux/conf", NULL };
static const char *padcmd[]     = { "termite", "--title", "scratchpad", "--geometry", "600x200-30+40", NULL };
static const char *lockcmd[]    = { "i3lock-fancy", NULL };
static const char *rebootcmd[]  = { "systemctl", "reboot", NULL };
static const char *shutcmd[]    = { "systemctl", "poweroff", NULL };

static Key keys[] = {
    /* modifier                     key        function        argument */
    { 0,                            XK_Menu,   spawn,          {.v = dmenucmd} },
    { 0,                            XK_F12,    spawn,          {.v = dmenucmd} },
    { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    { ControlMask|Mod1Mask,         XK_m,      spawn,          {.v = mailcmd } },
    { ControlMask|Mod1Mask,         XK_x,      spawn,          {.v = xtermcmd } },
    { ControlMask|Mod1Mask,         XK_t,      spawn,          {.v = tmuxcmd } },
    { ControlMask|Mod1Mask,         XK_n,      spawn,          {.v = ncmpcppcmd } },
    { ControlMask|Mod1Mask,         XK_c,      spawn,          SHCMD("$HOME/scripts/dpass") },
    { ControlMask|Mod1Mask,         XK_l,      spawn,          {.v = lockcmd } },
    { ControlMask|Mod1Mask,         XK_p,      spawn,          {.v = padcmd } },
    { ControlMask|Mod1Mask,         XK_r,      spawn,          {.v = rebootcmd } },
    { ControlMask|Mod1Mask,         XK_q,      spawn,          {.v = shutcmd } },
    { ControlMask|Mod1Mask,         XK_s,      spawn,          SHCMD("$HOME/scripts/screenie") },
    { ControlMask|Mod1Mask,         XK_w,      spawn,          SHCMD("$(tabbed -c -d -p -2 >/tmp/tabbed.xid); vimb -e $(</tmp/tabbed.xid)") },
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY|ControlMask,           XK_j,      pushdown,       {0} },
    { MODKEY|ControlMask,           XK_k,      pushup,         {0} },
    { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_Return, zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_s,      setlayout,      {.v = &layouts[3]} },
    { MODKEY,                       XK_space,  setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    { MODKEY,                       XK_Left,   cycle,          {.i = -1 } },
    { MODKEY,                       XK_Right,  cycle,          {.i = +1 } },
    { MODKEY|ControlMask,           XK_Left,   tagcycle,       {.i = -1 } },
    { MODKEY|ControlMask,           XK_Right,  tagcycle,       {.i = +1 } },
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

