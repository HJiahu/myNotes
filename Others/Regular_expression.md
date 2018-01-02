正则表达式
======================================================
### C++11中的正则表达式
*	C++11支持不同语法规则的正则表达式，[官方文档给出了对应的语法][1]
*	[这里][2]是basic语法(C++11)
### 其他参考
*	[Learn regular expressions in about 55 minutes][3]

### 正则表达式的一些规定
*	If the pattern permits a variable number of matching characters and thus there is more than one such sequence starting at that point, the longest such sequence is matched.（最长优先） 

### special code
这里以syntax_option_type::basic语法为例进行说明

#### ordinary character（matches itself）
any character in the supported character set, except for the BRE special characters

*	`.`, matches any character other than a newline
*	`[`,
*	`\`,
*	`*`, repeat the previous term as many times as necessary to guarantee a match
*	`$`,
#### BRE Special Characters


*	`\b`, match the position at the beginning or end of any word


*	`\d`, match any single digit
*	`{n}`, n is a digit ,repeat the preceding character n times

#### RE Bracket Expression
A bracket expression (an expression enclosed in square brackets, "[]" ) is an RE that shall match a specific set of single characters, and may match a specific set of multi-character collating elements, based on the non-empty set of list expressions contained in the bracket expression.


#### BRE Expression Anchoring
A BRE can be limited to matching expressions that begin or end a string; this is called "anchoring".

*	`^`, A <circumflex> ( '^' ) shall be an anchor when used as the first character of an entire BRE.
*	`$`,A <dollar-sign> ( '$' ) shall be an anchor when used as the last character of an entire BRE. 


#### Character classes
A character class is a collection of characters in square brackets. This means, "find any one of these characters".

*	The regular expression c[aeiou]t means, "find a c followed by a vowel followed by a t". In a piece of text, this will find cat, cet, cit, cot and cut.

##### Character class ranges
Within a character class, you can express a range of letters or digits, using a hyphen:

	[b-f] is the same as [bcdef] and means "find a b or a c or a d or an e or an f".
	[A-Z] is the same as [ABCDEFGHIJKLMNOPQRSTUVWXYZ] and means "find an upper-case letter".
	[1-9] is the same as [123456789] and means "find a non-zero digit".

Ranges and isolated characters may coexist in the same character class:  
> Ranges are ranges of characters, not ranges of numbers. The regular expression [1-31] means "find a 1 or a 2 or a 3", not "find an integer from 1 to 31".

	[0-9.,] means "find a digit or a full stop or a comma".
	[0-9a-fA-F] means "find a hexadecimal digit".
	[a-zA-Z0-9\-] means "find an alphanumeric character or a hyphen".

##### Character class negation

	[^a] means "find any character other than an a".
	[^a-zA-Z0-9] means "find a non-alphanumeric character".
	[\^abc] means "find a caret or an a or a b or a c".
	[^\^] means "find any character other than a caret". (Ugh!)

##### Freebie character classes

	The regular expression \d means the same as [0-9]: "find a digit".
	\w means the same as [0-9A-Za-z_]: "find a word character".
	\s means "find a space character (space, tab, carriage return or line feed)".

	\D means [^0-9]: "find a non-digit".
	\W means [^0-9A-Za-z_]: "find a non-word character".
	\S means "find a non-space character".

#### Multipliers

	a{3} means "find an a followed by an a followed by an a".
	a{0} means "find the empty string".
	[abc]{2} means "find a or b or c, followed by a or b or c".
	Braces have no special meaning inside character classes. [{}] means "find a left brace or a right brace".

##### Multiplier ranges

	x{4,4} is the same as x{4}.
	colou{0,1}r means "find colour or color".
	a{1,} means "find one or more as in a row".
	.{0,} means "find anything".
	a{3,5} means "find aaaaa or aaaa or aaa".Note that the longer possibility is most preferred, because multipliers are greedy. If your input text is I had an aaaaawful day then this regular expression will find the aaaaa in aaaaawful. It won't just stop after three as.

##### Freebie multipliers

	? means the same as {0,1}.
	* means the same as {0,}.
	+ means the same as {1,}.
	[?*+] means "find a question mark or an asterisk or a plus sign".

##### Non-greed
Multipliers can be made non-greedy by appending a question mark.

	\d{4,5}? exactly the same behaviour as \d{4}.
	".*?" means "find a double quote, followed by as few characters as possible, followed by a double quote". 

##### Alternation

	cat|dog means "find cat or dog".
	red|blue| and red||blue and |red|blue all mean "find red or blue or the empty string".
	a|b|c is the same as [abc].
	cat|dog|\| means "find cat or dog or a pipe".
	[cat|dog] means "find a or c or d or g or o or t or a pipe".



Learn regular expressions in about 55 minutes

### example
*	`\belvis\b.*\balive\b`, Find text with "elvis" followed by "alive"



[1]:http://en.cppreference.com/w/cpp/regex/syntax_option_type
[2]:http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap09.html#tag_09_03
[3]:https://qntm.org/files/re/re.html
