# Ajex
A tool for searching plain-text data sets for lines that match a regular expression.
To use Regular Expressions, one must learn the syntax. Regular Expressions use special characters, wildcards,
to match a range of other characters.


Wildcard or Meta-Characters 	Description and Examples

. 	The dot character matches any single character.
For example, the terminology rule regular expression, "a.b", matches all text where there is an "a" followed by any single character,
followed by a "b", as in, "a5b".

* 	The asterisk matches the preceding pattern or character zero or more times.
For example, "fo*" matches the following text fragments:
"f", "fo", "foo", "fooo"
Combining the period and asterisk, "a.*b" will match "a5b", "a55b", "a123b", and so on.

+ 	The plus sign matches the preceding pattern or character one or more times.
For example, "ca+r" matches the following text fragments: "car", "caar" and "caaar", but will not match "cr".

? 	The question mark character matches the preceding pattern or character zero or once.
For example, "ca?r" matches both "car" and "cr"; it will not match "caar".

{n} 	The curly brackets are used to match exactly n instances of the proceeding character or pattern.
For example, "x{2}" matches "xx".
Note: The curly brackets are used in the application to differentiate white space bounded text or characters from text or characters
 that are embedded among other characters with no identifiable white space.

{n,m} 	This form of the curly brackets is used to match the preceding character or pattern from n to m times,
with n greater than m. If m is not present then the pattern is matched n or more times.
For example, "x{2,3}" matches "xx" and "xxx".

[..] 	The square brackets match any one of characters inside the brackets. A range of characters in the alphabet can be matched using the hyphen.
For example, "[xyz]" will match any of "x", "y", or "z". Also, "[xyz]+" will match "x", "xx", "y", "yy", and so on.
Within square brackets, a range of characters can be defined using the dash (-). For example, "[a-z]" matches any lowercase letter,
and "[A-Z]" matches any uppercase letter. When using the dash to define a range of characters, the first character must precede the
second character in alphabetic or numeric order.
For example, "[0-9]" is valid, but "[9-0]" is not valid.

() 	The parentheses are used to group characters.
For example, "(cars?)|bus" will match "car", "cars", or "bus".

x|y 	The pipe (|) character matches either "x" or "y", where "x" or "y" are blocks of characters.
For example, "car|bus" will match either "car" or "bus".

\ 	Backslash has two meanings:
Matches against characters that normally have special meaning such as star (*) and dot (.), see preceding descriptions. In this case a "\*" matches the star character. Similarly "" matches the dot character.

Used to define a meta-character. The character "w" will normally match "w". A "\w" will match a sequence of alphanumeric characters not interrupted by white space, see the following description.

\w 	Matches any alphanumeric character or the underscore. This is identical to "[A-Za-z0-9_]".

\W 	Matches any character that is not alphanumeric and not underscore.

\d 	Matches all digits. Identical to "[0-9]".
For example, "/\d+/" will match one or more digits.

For example, positive integers.
\D 	Matches all non-digits including white space.
---------------------------------------------------------------------------------------------------------------------------------------------------

The input for the program is taken by using command line arguments.
For example: If the file's name is regular.c and the regular expression is given by "int [A-Za-z_][A-Za-z0-9]+\(" then the command is:
/a.out "int +[A-Za-z_][A-Za-z0-9]+\(" regular.c
The aforementioned regular expression would print all the functions that return a variable of type 'int'.


COMPILE AND RUN:
make
./agex "int +[A-Za-z_][A-Za-z0-9]+\(" regular.c


Caveat:
The regular expression should be put in double quotes.


