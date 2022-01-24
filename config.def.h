/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */

static const unsigned int gappih    = 30;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 20;       /* vert inner gap between windows */
static const unsigned int gappoh    = 20;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 20;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */

static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
//static const char *fonts[]          = { "Hack Nerd Font Mono:style=Regular:size=14" };
// BASIC:
static const char *fonts[]          = {"FiraCode Nerd Font Mono", "JetBrainsMono Nerd Font Mono:size12", "Hack Regular Nerd Font Complete:size=12" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font Mono:size=12";
 //static const char dmenufont[]       = "Hack Nerd Font Mono:style=Regular:size=12";
//static const char *upvol[]          = { "/usr/bin/pactl", "set-sink-volume", "@DEFAULT_SINK@", "+10%",     NULL };
//static const char *downvol[]        = { "/usr/bin/pactl", "set-sink-volume", "@DEFAULT_SINK@", "-10%",     NULL };
//static const char *mutevol[]        = { "/usr/bin/pactl", "set-sink-mute",   "@DEFAULT_SINK@", "toggle",  NULL };
//static const char *brightness_up[]  =   { "changebrightness", "up", NULL };
//static const char *brightness_down[]  = { "changebrightness", "down", NULL };

static const char col_grayCUSTOM[]       = "#4c566a";
//static const char col_grayCUSTOM[]       = "#454444";

static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_nord_blue[]   = "#81a1c1";
static const char col_red[]        = "#dc0005";
static const char col_black[]        = "#3b4252";


static const char col_test1[]        = "#ffffff";
static const char col_test2[]        = "#ab0000";
static const char col_test3[]        = "#dddddd";

static const char *colors[][3]      = {
	/*               fg(text of selected)         bg(selected window and middle bar)         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
//[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	//[SchemeSel]  = { col_gray4, col_black,  col_nord_blue },
	[SchemeSel]  = { col_nord_blue, col_gray1,  col_nord_blue },
};

/* staticstatus */
static const int statmonval = 0;

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

//static const char ptagf[] = "%s: %s";	/* format of a tag label */
static const char ptagf[] = "%s";	/* format of a tag label */
static const char etagf[] = "%s";	/* format of an empty tag */
static const int lcaselbl = 0;		/* 1 means make tag label lowercase */	

//static const char ptagf[] = "[%s %s]";	/* format of a tag label */
//static const char etagf[] = "[%s]";	/* format of an empty tag */
//static const int lcaselbl = 0;		/* 1 means make tag label lowercase */	

static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	// { "Gimp",     NULL,       NULL,       0,            1,           -1 },
	// { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	// { "Nautilus",  NULL,       NULL,      0,            1,   	 -1 },
	// { "discord",  NULL,       NULL,       1 << 8,            0,   	 -1 },
	/* class      instance    title       tags mask     isfloating   monitor    scratch key */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1,        0  },
	{ "firefox",  NULL,       NULL,       0,       		0,           -1,        0  },
	{ "Nautilus", NULL,       NULL,       0,            1,   	 	 -1, 		0 },
	{ "discord",  NULL,       NULL,       1 << 8,       0,   	 	 -1,		0 },
	{ NULL,       NULL,   "scratchpad",   0,            1,           -1,       's' },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
#include "shiftview.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[@]",      spiral },
	{ "[M]",      monocle },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
//static const char *termcmd[]  = { "st", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
/*First arg only serves to match against key in rules*/
static const char *scratchpadcmd[] = {"s", "alacritty", "-t", "scratchpad", NULL}; 

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,     	            	XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_o,  	   togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	//{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	//{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },
  	{ MODKEY,                       XK_l,      shiftview,      {.i = +1 } },
	{ MODKEY,                       XK_h,      shiftview,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	//GAPS, meant to remove some:
	{ MODKEY|Mod1Mask,              XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	//{ MODKEY|Mod1Mask,              XK_i,      incrigaps,      {.i = +1 } },
	//{ MODKEY|Mod1Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	//{ MODKEY|Mod1Mask,              XK_o,      incrogaps,      {.i = +1 } },
	//{ MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	//{ MODKEY|Mod1Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	//{ MODKEY|Mod1Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	//{ MODKEY|Mod1Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	//{ MODKEY|Mod1Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	//{ MODKEY|Mod1Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	//{ MODKEY|Mod1Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	//{ MODKEY|Mod1Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	//{ MODKEY|Mod1Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,	                   	XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[12]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[8]} },
	{ MODKEY,                       XK_space,  setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ControlMask,  		    XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_x,      spawn,	   SHCMD("slock") },
	{ MODKEY|ShiftMask,             XK_s,      spawn,	   SHCMD("flameshot gui -p ~/Pictures/screenshots") },
	{ MODKEY,                       XK_e,      spawn,	   SHCMD("nautilus") },
	{ MODKEY,                       XK_w,      spawn,	   SHCMD("chromium") },
	{ 0,			                XF86XK_AudioLowerVolume,	spawn,		SHCMD("pamixer --allow-boost -d 10; kill -44 $(pidof dwmblocks)") },
	{ 0,				            XF86XK_AudioRaiseVolume,    spawn,		SHCMD("pamixer --allow-boost -i 10; kill -44 $(pidof dwmblocks)") },
	{ 0,		           	        XF86XK_AudioMute,	        spawn,		SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
  	{ 0,                            XF86XK_MonBrightnessUp,   spawn,         SHCMD("brillo -A 5 -q") },
  	{ 0,                            XF86XK_MonBrightnessDown, spawn,         SHCMD("brillo -U 5 -q") },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

