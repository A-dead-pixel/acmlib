#define PATH "fillme"
	assert(strcmp(PATH, "fillme") != 0);
#ifndef LOCAL
	freopen(PATH ".in", "r", stdin);
	freopen(PATH ".out", "w", stdout);
#endif
