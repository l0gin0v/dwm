/* Sends a window to the next/prev tag */

#define TAGS 18

void
shifttag(const Arg *arg)
{
	Arg shifted;
	shifted.ui = selmon->tagset[selmon->seltags];


	if (arg->i > 0)	/* left circular shift */
		shifted.ui = ((shifted.ui << arg->i) | (shifted.ui >> (TAGS - arg->i)));
	else		/* right circular shift */
		shifted.ui = (shifted.ui >> (- arg->i) | shifted.ui << (TAGS + arg->i));
	tag(&shifted);
}
/* Sends a window to the next/prev tag that has a client, else it moves it to the next/prev one. */
void
shifttagclients(const Arg *arg)
{

	Arg shifted;
	Client *c;
	unsigned int tagmask = 0;
	shifted.ui = selmon->tagset[selmon->seltags];

	for (c = selmon->clients; c; c = c->next)
		if (!(c->tags))
			tagmask = tagmask | c->tags;


	if (arg->i > 0)	/* left circular shift */
		do {
			shifted.ui = (shifted.ui << arg->i)
			   | (shifted.ui >> (TAGS - arg->i));
		} while (tagmask && !(shifted.ui & tagmask));
	else		/* right circular shift */
		do {
			shifted.ui = (shifted.ui >> (- arg->i)
			   | shifted.ui << (TAGS + arg->i));
		} while (tagmask && !(shifted.ui & tagmask));
	tag(&shifted);
}
/* Navigate to the next/prev tag */
void
shiftview(const Arg *arg)
{
	Arg shifted;
	shifted.ui = selmon->tagset[selmon->seltags];

	if (arg->i > 0)	/* left circular shift */
		shifted.ui = (shifted.ui << arg->i) | (shifted.ui >> (TAGS - arg->i));
	else		/* right circular shift */
		shifted.ui = (shifted.ui >> (- arg->i) | shifted.ui << (TAGS + arg->i));
	view(&shifted);
}
/* Navigate to the next/prev tag that has a client, else moves it to the next/prev tag */
void
shiftviewclients(const Arg *arg)
{
	Arg shifted;
	Client *c;
	unsigned int tagmask = 0;
	shifted.ui = selmon->tagset[selmon->seltags];

	for (c = selmon->clients; c; c = c->next)
		if (!(c->tags))
			tagmask = tagmask | c->tags;


	if (arg->i > 0)	/* left circular shift */
		do {
			shifted.ui = (shifted.ui << arg->i)
			   | (shifted.ui >> (TAGS - arg->i));
		} while (tagmask && !(shifted.ui & tagmask));
	else		/* right circular shift */
		do {
			shifted.ui = (shifted.ui >> (- arg->i)
			   | shifted.ui << (TAGS + arg->i));
		} while (tagmask && !(shifted.ui & tagmask));
	view(&shifted);
}
/* move the current active window to the next/prev tag and view it. More like following the window */
void
shiftboth(const Arg *arg)
{
	Arg shifted;
	shifted.ui = selmon->tagset[selmon->seltags];

	if (arg->i > 0)	/* left circular shift */
		shifted.ui = ((shifted.ui << arg->i) | (shifted.ui >> (TAGS - arg->i)));
	else		/* right circular shift */
		shifted.ui = ((shifted.ui >> (- arg->i) | shifted.ui << (TAGS + arg->i)));
	tag(&shifted);
	view(&shifted);
}
//helper function for shiftswaptags.
//see: https://github.com/moizifty/DWM-Build/blob/65379c62640788881486401a0d8c79333751b02f/config.h#L48
void
swaptags(const Arg *arg)
{
	Client *c;
	unsigned int newtag = arg->ui & ((1 << TAGS) - 1);
	unsigned int curtag = selmon->tagset[selmon->seltags];

	if (newtag == curtag || !curtag || (curtag & (curtag-1)))
		return;

	for (c = selmon->clients; c != NULL; c = c->next) {
		if ((c->tags & newtag) || (c->tags & curtag))
			c->tags ^= curtag ^ newtag;

		if (!c->tags)
			c->tags = newtag;
	}

	//move to the swaped tag
	//selmon->tagset[selmon->seltags] = newtag;

	focus(NULL);
	arrange(selmon);
}
/* swaps "tags" (all the clients) with the next/prev tag. */
void
shiftswaptags(const Arg *arg)
{
	Arg shifted;
	shifted.ui = selmon->tagset[selmon->seltags];

	if (arg->i > 0)	/* left circular shift */
		shifted.ui = ((shifted.ui << arg->i) | (shifted.ui >> (TAGS - arg->i)));
	else		/* right circular shift */
		shifted.ui = ((shifted.ui >> (- arg->i) | shifted.ui << (TAGS + arg->i)));
	swaptags(&shifted);
	// uncomment if you also want to "go" (view) the tag where the the clients are going
	//view(&shifted);
}
