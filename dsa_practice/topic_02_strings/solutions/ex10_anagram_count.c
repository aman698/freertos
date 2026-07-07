/* Check if two lowercase strings are anagrams using frequency counts. */
#include <stdbool.h>
#include <stdio.h>

int main(void)
{
    const char *a = "listen";
    const char *b = "silent";
    int freq[26] = {0};
    bool ok = true;
    for (size_t i = 0; a[i] != '\0'; i++) freq[a[i] - 'a']++;
    for (size_t i = 0; b[i] != '\0'; i++) freq[b[i] - 'a']--;
    for (size_t i = 0; i < 26; i++) if (freq[i] != 0) ok = false;
    printf("anagram=%s\n", ok ? "yes" : "no");
    return 0;
}
