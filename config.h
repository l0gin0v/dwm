/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>
#include "shift-tools.c"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel (standart: 32) */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {
	"FiraCode Nerd Font:style:SemiBold:size=18",
  	"Iosevka Nerd Font:style=SemiBold:size=18",
  	"Font Awesome 6 Free:size=18",
	"Noto Color Emoji:size=18"
};

static const char dmenufont[]       = "FiraCode Nerd Font:style=SemiBold:size=16";
static const char gray1[]       = "#222222";
static const char gray2[]       = "#444444";
static const char gray3[]       = "#bbbbbb";
static const char gray4[]       = "#eeeeee";
//static const char cyan[]        = "#005577";
//static const char red[]	    = "#960000";
static const char black[]	    = "#000000";
//static const char black1[]	    = "#0a0a0a";
//static const char black2[]	    = "#0a0c10";
//static const char black3[]	    = "#0d0d0d";
static const char white[]	 = "#ffffff";
static const char *colors[][3]      = {
	/*               fg         bg       border   */
	[SchemeNorm] = { white,    black,    gray1 },
	[SchemeSel]  = { black,    white,    white },
};

/* tagging */
const char *tags[] = {
  "", "", "", "󰓓", "5", "6", "󰈦", "8", "9 ",
  "", "", "", "", " ", "󰟓", "", "", "18"
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                 instance    title       tags mask     isfloating   monitor    ismaster*/
	//{ "Gimp",              NULL,       NULL,       0,            1,           -1 },
  { "st-256color",         NULL,       NULL,       1 << 0,	     0,           -1 },
  { "Firefox",             NULL,       NULL,       1 << 1,       0,           -1 },
  { "Telegram",            NULL,       NULL,       1 << 2,       0,           -1 },
  { "steam",               NULL,       NULL,       1 << 3,       0,           -1 },
  
  { "Zathura",             NULL,       NULL,       1 << 6,       0,           -1 },

  { "rider",               NULL,       NULL,       1 << 9,       0,           -1 },
  { "rustrover",           NULL,       NULL,       1 << 10,      0,           -1 },
  { "idea",                NULL,       NULL,       1 << 11,      0,           -1 },
  { "pycharm",             NULL,       NULL,       1 << 12,      0,           -1 },
  { "webstorm",            NULL,       NULL,       1 << 13,      0,           -1 },
  { "goland",              NULL,       NULL,       1 << 14,      0,           -1 },
  { "rubymine",            NULL,       NULL,       1 << 15,      0,           -1 },
  { "datagrip",            NULL,       NULL,       1 << 16,      0,           -1 },
};

/* layout(s) */
static const float mfact        = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;    /* number of clients in master area */
static const int resizehints    = 1;    /* 1 means respect size hints in tiled resizals */
static const int gap            = 0;
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[tile]",      tile },    /* first entry is default */
	{ "<float>",      NULL },    /* no layout function means floating behavior */
	{ "(monocle)",      monocle },
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

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", black, "-nf", white, "-sb", white, "-sf", black, NULL };
static const char *termcmd[]  = { "st", NULL };

static const char *upvol[]   = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL };
static const char *downvol[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL };
static const char *mutevol[] = { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };

static const Key keys[] = {
	/* modifier                     key                      function        argument */
	{ MODKEY,                       XK_p,                    spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,               spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,                    togglebar,      {0} },
	{ MODKEY,                       XK_j,                    focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                    focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                    incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                    incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                    setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                    setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return,               zoom,           {0} },
	{ MODKEY,                       XK_Tab,                  view,           {0} },
	{ MODKEY,	                      XK_q,                    killclient,     {0} },
	{ MODKEY,                       XK_t,                    setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,                    setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,                    setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,                setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,                togglefloating, {0} },
	{ MODKEY,                       XK_0,                    view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                    tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,               focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,               tagmon,         {.i = +1 } },
	{ 0,				                    XK_Print,                spawn,	         SHCMD("flameshot gui") },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
  { MODKEY|Mod1Mask,              XK_1,      view,      {.ui = 1 << 9} },   // тег 10
  { MODKEY|Mod1Mask,              XK_2,      view,      {.ui = 1 << 10} },  // тег 11
  { MODKEY|Mod1Mask,              XK_3,      view,      {.ui = 1 << 11} },  // тег 12
  { MODKEY|Mod1Mask,              XK_4,      view,      {.ui = 1 << 12} },  // тег 13
  { MODKEY|Mod1Mask,              XK_5,      view,      {.ui = 1 << 13} },  // тег 14
  { MODKEY|Mod1Mask,              XK_6,      view,      {.ui = 1 << 14} },  // тег 15
  { MODKEY|Mod1Mask,              XK_7,      view,      {.ui = 1 << 15} },  // тег 16
  { MODKEY|Mod1Mask,              XK_8,      view,      {.ui = 1 << 16} },  // тег 17
  { MODKEY|Mod1Mask,              XK_9,      view,      {.ui = 1 << 17} },  // тег 18
  
  { MODKEY|ShiftMask|Mod1Mask,              XK_1,      view,      {.ui = 1 << 9} },   // тег 10
  { MODKEY|ShiftMask|Mod1Mask,              XK_2,      view,      {.ui = 1 << 10} },  // тег 11
  { MODKEY|ShiftMask|Mod1Mask,              XK_3,      view,      {.ui = 1 << 11} },  // тег 12
  { MODKEY|ShiftMask|Mod1Mask,              XK_4,      view,      {.ui = 1 << 12} },  // тег 13
  { MODKEY|ShiftMask|Mod1Mask,              XK_5,      view,      {.ui = 1 << 13} },  // тег 14
  { MODKEY|ShiftMask|Mod1Mask,              XK_6,      view,      {.ui = 1 << 14} },  // тег 15
  { MODKEY|ShiftMask|Mod1Mask,              XK_7,      view,      {.ui = 1 << 15} },  // тег 16
  { MODKEY|ShiftMask|Mod1Mask,              XK_8,      view,      {.ui = 1 << 16} },  // тег 17
  { MODKEY|ShiftMask|Mod1Mask,              XK_9,      view,      {.ui = 1 << 17} },  // тег 18

	{ ControlMask|ShiftMask,        XK_q,                    quit,           {0} },

  { ControlMask|ShiftMask|MODKEY, XK_Left,                 shiftview,      { .i = -9 } },
  { ControlMask|ShiftMask|MODKEY, XK_Right,                shiftview,      { .i = +9 } },

  /* user's shortcuts */

  { MODKEY|ShiftMask,             XK_t,                    spawn,          SHCMD("Telegram") },
  { MODKEY|ShiftMask,             XK_f,                    spawn,          SHCMD("firefox") },
  { MODKEY|ShiftMask,             XK_z,                    spawn,          SHCMD("poweroff") },
  { MODKEY|ShiftMask,             XK_r,                    spawn,          SHCMD("reboot") },
  { 0,                            XF86XK_AudioMute,        spawn,          {.v = mutevol } },
  { 0,                            XF86XK_AudioLowerVolume, spawn,          {.v = downvol } },
  { 0,                            XF86XK_AudioRaiseVolume, spawn,          {.v = upvol   } },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

