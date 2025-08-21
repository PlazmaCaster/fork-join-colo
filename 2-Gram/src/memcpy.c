/**
 * Terribly inefficient implementation of memset
 *
 * Fills the first n bytes of the memory area pointed to by d with
 * the first n bytes of the memory area pointed to by s
 */
void *
memcpy(void *d, const void *s, int n) {
	char *dst = (char *) d;
	char *src = (char *) s;
	for (int i=0; i<n; i++) {
		dst[i] = src[i];
	}
}
