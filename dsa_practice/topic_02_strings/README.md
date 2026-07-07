# Topic 02 - Strings

C strings are character arrays terminated by `'\0'`. Algorithms must protect buffer limits and avoid reading past the terminator.

## Brief Theory

| Concept | Use |
|---------|-----|
| Null terminator | Marks string end |
| Manual length | Scan until `'\0'` |
| Reverse | Two-pointer swap |
| Compare | Lexicographic order |
| Token/parse | Convert text into data |

---

## Exercises

| # | File | Problem | Key Concept |
|---|------|---------|-------------|
| 01 | [ex01_strlen_manual.c](solutions/ex01_strlen_manual.c) | Manual string length | Terminator |
| 02 | [ex02_count_vowels.c](solutions/ex02_count_vowels.c) | Count vowels | Character scan |
| 03 | [ex03_reverse_string.c](solutions/ex03_reverse_string.c) | Reverse string in place | Two pointers |
| 04 | [ex04_palindrome.c](solutions/ex04_palindrome.c) | Check palindrome | Symmetry |
| 05 | [ex05_string_compare.c](solutions/ex05_string_compare.c) | Compare two strings | Lexicographic |
| 06 | [ex06_copy_safe.c](solutions/ex06_copy_safe.c) | Bounded copy | Buffer safety |
| 07 | [ex07_find_char.c](solutions/ex07_find_char.c) | Find first character | Search |
| 08 | [ex08_count_words.c](solutions/ex08_count_words.c) | Count words | State scan |
| 09 | [ex09_atoi_manual.c](solutions/ex09_atoi_manual.c) | Convert text to int | Parsing |
| 10 | [ex10_anagram_count.c](solutions/ex10_anagram_count.c) | Check lowercase anagram | Frequency |
