/*
 * New editor name:  TDE, the Thomson-Davis Editor.
 * Author:           Frank Davis
 * Date:             June 5, 1992
 *
 * This file contains the credit screen, main help screen and the help
 * displays for functions where help would be useful.
 *
 * jmh 991022: changed all the frames to double-line.
 * jmh 010528: added command line help screen.
 */

/*
#include "tdestr.h"
#include "define.h"
*/
#include "letters.h"
#define NULL 0

#define VERSION  "   Version 5.1v   "   /* This width must not change! */
#define DATE     "   May 1, 2007    "   /* This width must not change! */
#define PVERSION "5.1v"
#define PDATE    "May 1, 2007"


const char * const tde_help =
"\
TDE, the Thomson-Davis Editor, version "PVERSION" ("PDATE").\n\
Jason Hood <jadoxa@yahoo.com.au>.  http://tde.adoxa.cjb.net/\n\
\n\
tde [-v] [-i config] [options] [filename(s)] [options] ...\n\
tde [-v] [-i config] [options] -f|F|g|G pattern filename(s)\n\
tde [-v] [-i config] -w [workspace [...]]\n\
\n\
-v is viewer mode (everything is loaded read-only).\n\
-i will load the specified configuration file.\n\
-w will load files from, or save to, the given workspace.\n\
\n\
Filenames (and directories) can include wildcards - use '-?\?' for help.\n\
\n\
'F' is a text-based search; 'G' is a regular expression search.\n\
Lowercase letter ignores case; uppercase letter matches case.\n\
Use '-G?' for help on regular expression syntax.  Add an equal\n\
sign after the letter to create a window containing the matching\n\
lines from all files.\n\
\n\
Options can be:\n\
   a              Load all files immediately\n\
   b[n]           Binary (default n is 64; 0 will force text; negative will\n\
                   keep text files; ! will ignore binary files)\n\
   c <title>      Name the window \"title\" (\".\" to use filename)\n\
   e <macro>      Execute \"macro\" after loading each file\n\
   l[lang]        Disable syntax highlighting, or use language \"lang\"\n\
   n              Create a new (scratch) window\n\
   r              Read-only\n\
   s              Scratch\n\
   t[n]           Use tab size n (default is 8; 0 will deflate tabs)\n\
   [line][:col]   Start at the specified position (negative line number\n\
                   will be taken from the end of the file, negative column\n\
                   from the end of the line)\n\
   +offset        Move to the specified offset (prefix with 0x for hex)\n\
\n\
Options prefixed with '-' will apply to all subsequent files (except title and\n\
movement); use a trailing '-' to restore default behavior.  Options prefixed\n\
with '+' will only apply to one file.  If the option is uppercase, it will\n\
apply to the previous file.  Example:\n\
\n\
   tde -b file1 -b- file2\n\
   tde file1 +B file2\n\
\n\
will both load \"file1\" as binary and auto-detect the type of \"file2\".\n\
\n\
TDE can also be used as a filter (eg: dir | tde >dir.lst).\
";


#if STAT_COUNT > STATS_COUNT
char *stat_screen[STAT_COUNT+1];  /* used for both status and statistics */
#else
char *stat_screen[STATS_COUNT+1];
#endif

int  help_dim[2][2] = { { 25, 80 }, { 25, 80 } };


#if !defined( __UNIX__ ) || defined( PC_CHARS )

const char * const credit_screen[] = {
"浜様様様様様様様様様様様様様様様様様様様様様様様様様融",
"�                                                    �",
"�           TDE, the Thomson-Davis Editor            �",
"�                                                    �",
"�                 "    VERSION     "                 �",
"�                                                    �",
"�                    Frank Davis                     �",
"�                        and                         �",
"�                     Jason Hood                     �",
"�                                                    �",
"�                 "      DATE      "                 �",
"�                                                    �",
"�                                                    �",
"�      This program is released into the public      �",
"�   domain.  You may use and distribute it freely.   �",
"�                                                    �",
"藩様様様様様様様様様様様様様様様様様様様様様様様様様夕",
NULL
};


/*
 * The lines in this help screen need to be exactly 80 characters (otherwise
 * editor residue will be visible; however, the config will blank out unused
 * characters). There can be any number of lines, but of course it won't
 * display beyond the bottom of the screen.
 * jmh 990430: turned into a 2d array, removed the signature.
 * jmh 050710: added the viewer screen as another array.
 */
char help_screen[2][HELP_HEIGHT][HELP_WIDTH+1] = { {
"浜様様様様様様様様様様様様様様様様様� HELP 様様様様様様様様様様様様様様様様様様�",
"菜陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�  敖陳陳陳陳陳陳�   敖陳陳陳陳陳陳陳陳陳陳朕�",
"些 # = Shift   @ = Alt   ^ = Ctrl �  � ^\\ for Menu �   � abort command     ^[ 該",
"裟陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�  青陳陳陳陳陳陳�   青陳陳陳陳陳陳陳陳陳陳潰�",
"菜陳陳陳陳陳陳陳陳陳 Cursor Movement 陳陳陳陳陳陳陳陳朕敖陳 Screen Movement 陳榛",
"些 next line, first char/begin/end        #/^/#^Enter 崖 pan left       @Left 該",
"些 first column                                 #Home 崖 pan right     @Right 該",
"挫陳陳陳陳陳陳陳陳陳陳陳陳賃陳陳陳陳陳陳陳陳陳陳陳陳陳干 pan up           @Up 該",
"些 stream left       #Left � stream right      #Right 崖 pan down       @Down 該",
"些 word left         ^Left � word right        ^Right 崖 scroll up        ^Up 該",
"些 string left      #^Left � string right     #^Right 崖 scroll down    ^Down 該",
"些 word end left        @; � word end right        @' 垣陳陳陳陳陳陳陳陳陳陳陳拑",
"些 string end left     #@; � string end right     #@' 楽陳陳陳陳 Macro 陳陳陳朕�",
"些 set marker     @1 -  @3 � match () [] {} <> \"   ^] 崖 marker           #@M 該",
"些 goto marker   #@1 - #@3 � previous position     @~ 崖 pause             ^P 該",
"裟陳陳陳陳陳陳陳陳陳陳陳陳珍陳陳陳陳陳陳陳陳陳陳陳陳陳拈陳陳陳陳陳陳陳陳陳陳陳拑",
"菜陳陳陳陳陳陳� Insert / Delete 陳陳陳陳陳陳陳笥陳陳陳陳陳� Block 陳陳陳陳陳陳榛",
"些 insert newline, match indentation    Enter 崖 box                       @B 該",
"些 next tab, add spaces if insert         Tab 崖 line                      @L 該",
"些 previous tab, delete if insert        #Tab 崖 stream                    @X 該",
"些 delete, join lines if at eol       ^Delete 崖 unmark / re-mark          @U 該",
"些 delete word, previous word       ^T, ^Bksp 崖 adjust begin/end    #@[, #@] 該",
"些 restore, undo, redo     Esc, @Bksp, #@Bksp 崖 move to begin/end    @[,  @] 該",
"裟陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳拈陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳拑",
"藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様夕",
}, {

/*
 * Help screen when in viewer (read-only) mode.
 */
"浜様様様様様様様様様様様様様様様� VIEWER HELP 様様様様様様様様様様様様様様様様融",
"�                                                                              �",
"�  敖陳陳陳 File 陳陳陳朕   敖陳陳陳 Location 陳陳陳朕   敖陳陳 Search 陳陳朕  �",
"�  � next, prev   :n :p �   � top of file   '^ B     �   � define find  < > �  �",
"�  � goto, first  :x :X �   � end of file   '$ F G   �   � repeat find  , . �  �",
"�  � open         :e  E �   � goto line      g       �   � define regx  / ? �  �",
"�  � close        :q  q �   � previous      '' `     �   � repeat regx  n N �  �",
"�  � status       :f  = �   � set  marker   m1 m2 m3 �   青陳陳陳陳陳陳陳陳潰  �",
"�  � exit viewer   v    �   � goto marker   '1 '2 '3 �                         �",
"�  � exit TDE     :Q  Q �   青陳陳陳陳陳陳陳陳陳陳陳潰                         �",
"�  青陳陳陳陳陳陳陳陳陳潰                                                      �",
"�                                                                              �",
"�  敖陳陳陳陳陳陳 Window 陳陳陳陳陳朕   敖� Screen 陳�   敖 Miscellaneous 朕   �",
"�  � up     b       � half up     u �   � up     k y �   � shell         ! �   �",
"�  � down   f space � half down   d �   � down   j e �   � user screen   s �   �",
"�  � left   {       � half left   [ �   � left   h   �   � redraw        R �   �",
"�  � right  }       � half right  ] �   � right  l   �   � repeat        r �   �",
"�  青陳陳陳陳陳陳陳珍陳陳陳陳陳陳陳潰   青陳陳陳陳陳潰   青陳陳陳陳陳陳陳陳�   �",
"�                                                                              �",
"�                                                                              �",
"�                   敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳朕                   �",
"�                   � Press F1 or H for other help screen. �                   �",
"�                   青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳潰                   �",
"�                                                                              �",
"藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様夕",
} };


const char * const regx_help[] = {
"浜様様様様用様様様様様様様様様様様様様様様様様様様様様様用様様様様様様様�",
"�  c       �  any non-operator character                 �  Felis       �",
"�  \\c      �  c literally and C escapes (0abefnrtv)      �  catus\\.     �",
"�  \\n      �  backreference (1 to 9)                     �  (boo)\\1     �",
"�  \\:c     �  predefined character set                   �  \\:a+.?\\(    �",
"�          �    a - alphanumeric d - decimal l - lower   �              �",
"�          �    b - white space  h - hex.    u - upper   �              �",
"�          �    c - alphabetic   Uppercase not in set    �              �",
"�  .       �  any character                              �  c.t         �",
"�  ,       �  space or tab characters                    �  ,cat,       �",
"�  < >     �  beginning and end of word                  �  <cat>       �",
"�  << >>   �  beginning and end of string                �  <<cat>>     �",
"�  ^ $     �  beginning and end of line                  �  ^cat$       �",
"�  [x]     �  any character in x                         �  [\\:c0-9]    �",
"�  [^x]    �  any character not in x                     �  [^AEIOU]    �",
"�  r* r*?  �  zero or more r's, longest or shortest      �  ca*t        �",
"�  r+ r+?  �  one or more r's, longest or shortest       �  ca[b-t]+    �",
"�  r? r??  �  zero or one r, prefer one or zero          �  c.?t        �",
"�  rs      �  r followed by s                            �  ^$          �",
"�  r|s     �  either r or s                              �  kitty|cat   �",
"�  (r)     �  r                                          �  (c)?(a+)t   �",
"�  (?:r)   �  r, without generating a backreference      �              �",
"�  r(?=s)  �  match r only if s matches                  �  label(?=:)  �",
"�  r(?!s)  �  match r only if s does not match           �  kit(?!ten)  �",
"藩様様様様溶様様様様様様様様様様様様様様様様様様様様様様溶様様様様様様様�",
NULL
};


const char * const replace_help[] = {
"浜様様様冤様様様様様様様様様様様様様様様�",
"�  \\c   �  c literally and C escapes    �",
"�  \\n   �  backreference (1 to 9)       �",
"�  \\&   �  entire match                 �",
"�  \\+?  �  uppercase match or backref   �",
"�  \\-?  �  lowercase match or backref   �",
"�  \\^?  �  capitalise match or backref  �",
"藩様様様詫様様様様様様様様様様様様様様様�",
NULL
};


const char * const wildcard_help[] = {
"浜様様様様様冤様様様様様様様様様様様様様様様様様様様様様融",
"�  *        �  match zero or more characters             �",
"�  ?        �  match any one character                   �",
"�  [set]    �  match any character in the set            �",
"�  [!set]   �  match any character not in the set        �",
"�  [^set]   �  same as above                             �",
"�  a;b!c;d  �  match \"a\" or \"b\" but exclude \"c\" and \"d\"  �",
"�  !a;b     �  match everything except \"a\" and \"b\"       �",
"�           �                                            �",
"�  ...      �  enter subdirectories (eg: \".../*.c\")      �",
"�  dirname  �  same as \"dirname/*\"                       �",
"把陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳超",
"�  A set is a group (\"a1.\") and/or range (\"a-z\") of      �",
"�  characters.  To include '!^]-' in the set, precede    �",
"�  it with '\\'.  To match ';' or '!' make it part of a   �",
"�  set.  The names will be sorted according to the       �",
"�  current directory list order (name or extension).     �",
#if defined( __UNIX__ )
"�  ':' can be used instead of ';'.                       �",
#endif
"藩様様様様様様様様様様様様様様様様様様様様様様様様様様様夕",
NULL
};


const char * const stamp_help[] = {
"浜様様様冤様様様様様様様様様様様融",
"�  %d   �  day of month          �",
"�  %D   �  day of week           �",
"�  %e   �  enter new line        �",
"�  %h   �  hour (12-hour)        �",
"�  %H   �  hour (24-hour)        �",
"�  %m   �  month (number)        �",
"�  %M   �  month (word)          �",
"�  %n   �  minutes               �",
"�  %p   �  am or pm              �",
"�  %s   �  seconds               �",
"�  %t   �  tab                   �",
"�  %y   �  year (two digits)     �",
"�  %Y   �  year (full)           �",
"�  %Z   �  timezone (abbr.)      �",
"�  %0?  �  zero-padded numbers,  �",
"�       �  abbreviated words     �",
"�  %2?  �  blank-padded numbers  �",
"�  %+?  �  left-aligned words    �",
"�  %-?  �  right-aligned words   �",
"�  %%   �  a percent sign        �",
"藩様様様詫様様様様様様様様様様様夕",
NULL
};


const char * const border_help[] = {
"浜様様様様様様用様様様様様様様様様様様様様様様様様様様様様様様様様融",
"�  # of chars  �                  Style characters                 �",
"�   in style   �                     represent                     �",
"把陳陳陳陳陳陳津陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳超",
"�      0       �  current graphic set                              �",
"�      1       �  entire border                                    �",
"�      2       �  vertical and horizontal edges                    �",
"�      3       �  corners, vertical and horizontal edges           �",
"�      4       �  left, right, top and bottom edges                �",
"�      5       �  top-left, top-right, bottom-left,                �",
"�              �    bottom-right corners and the edges             �",
"�      6       �  the four corners, vertical and horizontal edges  �",
"�      8       �  the four corners and the four edges              �",
"藩様様様様様様溶様様様様様様様様様様様様様様様様様様様様様様様様様夕",
NULL
};


const char * const exec_help[] = {
"浜様様様様冤様様様様様様様様様様様様様融",
"�  %[=]f  �  filename (relative path)  �",
"�  %[=]F  �  filename (absolute path)  �",
"�  %p     �  prompt for parameter      �",
"�  %w     �  copy the current word     �",
"�  %W     �  copy the current string   �",
"�  %%     �  a percent sign            �",
"把陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳超",
"�    The filename will be quoted if    �",
"�    needed; '=' will prevent that.    �",
"藩様様様様様様様様様様様様様様様様様様夕",
NULL
};


const char * const char_help[] = {
"浜様様様様様様様様様様様様様様様様様様様融",
"�              Character Set             �",
"�                                        �",
"�    敖0�1�2�3�4�5�6�7�8�9�0�1�2�3�4�5朕 �",
"�   0�   \x01 \x02 \x03 \x04 \x05 \x06 \x07 "
       "\x08 \x09 \x0a \x0b \x0c \x0d \x0e \x0f � �",
"�  16� \x10 \x11 \x12 \x13 \x14 \x15 \x16 \x17 "
       "\x18 \x19 \x1a \x1b \x1c \x1d \x1e \x1f � �",
"�  32�   ! \" # $ % & ' ( ) * + , - . / � �",
"�  48� 0 1 2 3 4 5 6 7 8 9 : ; < = > ? � �",
"�  64� @ A B C D E F G H I J K L M N O � �",
"�  80� P Q R S T U V W X Y Z [ \\ ] ^ _ � �",
"�  96� ` a b c d e f g h i j k l m n o � �",
"� 112� p q r s t u v w x y z { | } ~  � �",
"� 128� � � � � � � � � � � � � � � � � � �",
"� 144� � � � � � � � � � � � � � � � � � �",
"� 160� � � � � � � � � � � � � � � � � � �",
"� 176� � � � � � � � � � � � � � � � � � �",
"� 192� � � � � � � � � � � � � � � � � � �",
"� 208� � � � � � � � � � � � � � � � � � �",
"� 224� � � � � � � � � � � � � � � � � � �",
"� 240� � � � � � � � � � � � � � � � � � �",
"�    青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳� �",
"藩様様様様様様様様様様様様様様様様様様様夕",
NULL
};


#else

const char * const credit_screen[] = {
"+----------------------------------------------------+",
"|                                                    |",
"|           TDE, the Thomson-Davis Editor            |",
"|                                                    |",
"|                 "    VERSION     "                 |",
"|                                                    |",
"|                    Frank Davis                     |",
"|                        and                         |",
"|                     Jason Hood                     |",
"|                                                    |",
"|                 "      DATE      "                 |",
"|                                                    |",
"|                                                    |",
"|      This program is released into the public      |",
"|   domain.  You may use and distribute it freely.   |",
"|                                                    |",
"+----------------------------------------------------+",
NULL
};


char help_screen[2][HELP_HEIGHT][HELP_WIDTH+1] = { {
"+==================================== HELP ====================================+",
"|+--------------------------------+  +-------------+   +----------------------+|",
"|| # = Shift   @ = Alt   ^ = Ctrl |  | ^\\ for Menu |   | abort command     ^[ ||",
"|+--------------------------------+  +-------------+   +----------------------+|",
"|+------------------ Cursor Movement -----------------++--- Screen Movement --+|",
"|| next line, first character                       - || pan left           - ||",
"|| next line, first column                          - || pan right          - ||",
"|+-------------------------+--------------------------+| pan up             - ||",
"|| word left         #Left | word end left          - || pan down           - ||",
"|| word right       #Right | word end right         - || scroll up          - ||",
"|| string left           - | string end left        - || scroll down        - ||",
"|| string right          - | string end right       - |+----------------------+|",
"|+-------------------------+--------------------------++-------- Macro -------+|",
"|| set marker    ^K! - ^K# | match () [] {} <> \"   ^] || marker           ^Km ||",
"|| goto marker   ^K1 - ^K3 | previous position      - || pause            ^Kp ||",
"|+----------------------------------------------------++----------------------+|",
"|+------------- Insert / Delete --------------++----------- Block ------------+|",
"|| insert newline, match indentation    Enter || box                       ^B ||",
"|| next tab, add spaces if insert         Tab || line                      ^L ||",
"|| previous tab, delete if insert        #Tab || stream                    ^X ||",
"|| delete, join lines if at eol             - || unmark / re-mark          ^^ +|",
"|| delete word, previous word           ^T, - || adjust begin/end    ^Kb, ^Kk ||",
"|| undo, redo                           ^U, - || move to begin/end ^K^B, ^K^K ||",
"|+--------------------------------------------++------------------------------+|",
"+==============================================================================+",
}, {

"+================================ VIEWER HELP =================================+",
"|                                                                              |",
"|  +------- File -------+   +------- Location -------+   +----- Search -----+  |",
"|  | next, prev   :n :p |   | top of file   '^ B     |   | define find  < > |  |",
"|  | goto, first  :x :X |   | end of file   '$ F G   |   | repeat find  , . |  |",
"|  | open         :e  E |   | goto line      g       |   | define regx  / ? |  |",
"|  | close        :q  q |   | previous      '' `     |   | repeat regx  n N |  |",
"|  | status       :f  = |   | set  marker   m1 m2 m3 |   +------------------+  |",
"|  | exit viewer   v    |   | goto marker   '1 '2 '3 |                         |",
"|  | exit TDE     :Q  Q |   +------------------------+                         |",
"|  +--------------------+                                                      |",
"|                                                                              |",
"|  +------------- Window -----------+   +-- Screen --+   +- Miscellaneous -+   |",
"|  | up     b       | half up     u |   | up     k y |   | shell         ! |   |",
"|  | down   f space | half down   d |   | down   j e |   | user screen   s |   |",
"|  | left   {       | half left   [ |   | left   h   |   | redraw        R |   |",
"|  | right  }       | half right  ] |   | right  l   |   | repeat        r |   |",
"|  +----------------+---------------+   +------------+   +-----------------+   |",
"|                                                                              |",
"|                                                                              |",
"|                   +--------------------------------------+                   |",
"|                   | Press F1 or H for other help screen. |                   |",
"|                   +--------------------------------------+                   |",
"|                                                                              |",
"+==============================================================================+",
} };


const char * const regx_help[] = {
"+----------+---------------------------------------------+--------------+",
"|  c       |  any non-operator character                 |  Felis       |",
"|  \\c      |  c literally and C escapes (0abefnrtv)      |  catus\\.     |",
"|  \\n      |  backreference (1 to 9)                     |  (boo)\\1     |",
"|  \\:c     |  predefined character set                   |  \\:a+.?\\(    |",
"|          |    a - alphanumeric d - decimal l - lower   |              |",
"|          |    b - white space  h - hex.    u - upper   |              |",
"|          |    c - alphabetic   Uppercase not in set    |              |",
"|  .       |  any character                              |  c.t         |",
"|  ,       |  space or tab characters                    |  ,cat,       |",
"|  < >     |  beginning and end of word                  |  <cat>       |",
"|  << >>   |  beginning and end of string                |  <<cat>>     |",
"|  ^ $     |  beginning and end of line                  |  ^cat$       |",
"|  [x]     |  any character in x                         |  [\\:c0-9]    |",
"|  [^x]    |  any character not in x                     |  [^AEIOU]    |",
"|  r* r*?  |  zero or more r's, longest or shortest      |  ca*t        |",
"|  r+ r+?  |  one or more r's, longest or shortest       |  ca[b-t]+    |",
"|  r? r??  |  zero or one r, prefer one or zero          |  c.?t        |",
"|  rs      |  r followed by s                            |  ^$          |",
"|  r|s     |  either r or s                              |  kitty|cat   |",
"|  (r)     |  r                                          |  (c)?(a+)t   |",
"|  (?:r)   |  r, without generating a backreference      |              |",
"|  r(?=s)  |  match r only if s matches                  |  label(?=:)  |",
"|  r(?!s)  |  match r only if s does not match           |  kit(?!ten)  |",
"+----------+---------------------------------------------+--------------+",
NULL
};


const char * const replace_help[] = {
"+-------+-------------------------------+",
"|  \\c   |  c literally and C escapes    |",
"|  \\n   |  backreference (1 to 9)       |",
"|  \\&   |  entire match                 |",
"|  \\+?  |  uppercase match or backref   |",
"|  \\-?  |  lowercase match or backref   |",
"|  \\^?  |  capitalise match or backref  |",
"+-------+-------------------------------+",
NULL
};


const char * const wildcard_help[] = {
"+-----------+--------------------------------------------+",
"|  *        |  match zero or more characters             |",
"|  ?        |  match any one character                   |",
"|  [set]    |  match any character in the set            |",
"|  [!set]   |  match any character not in the set        |",
"|  [^set]   |  same as above                             |",
"|  a:b!c:d  |  match \"a\" or \"b\" but exclude \"c\" and \"d\"  |",
"|  !a:b     |  match everything except \"a\" and \"b\"       |",
"|           |                                            |",
"|  ...      |  enter subdirectories (eg: \".../*.c\")      |",
"|  dirname  |  same as \"dirname/*\"                       |",
"+-----------+--------------------------------------------+",
"|  A set is a group (\"a1.\") and/or range (\"a-z\") of      |",
"|  characters.  To include '!^]-' in the set, precede    |",
"|  it with '\\'.  To match ';' or '!' make it part of a   |",
"|  set.  The names will be sorted according to the       |",
"|  current directory list order (name or extension).     |",
"|  ';' can be used instead of ':'.                       |",
"+--------------------------------------------------------+",
NULL
};


const char * const stamp_help[] = {
"+-------+------------------------+",
"|  %d   |  day of month          |",
"|  %D   |  day of week           |",
"|  %e   |  enter new line        |",
"|  %h   |  hour (12-hour)        |",
"|  %H   |  hour (24-hour)        |",
"|  %m   |  month (number)        |",
"|  %M   |  month (word)          |",
"|  %n   |  minutes               |",
"|  %p   |  am or pm              |",
"|  %s   |  seconds               |",
"|  %t   |  tab                   |",
"|  %y   |  year (two digits)     |",
"|  %Y   |  year (full)           |",
"|  %Z   |  timezone (abbr.)      |",
"|  %0?  |  zero-padded numbers,  |",
"|       |  abbreviated words     |",
"|  %2?  |  blank-padded numbers  |",
"|  %+?  |  left-aligned words    |",
"|  %-?  |  right-aligned words   |",
"|  %%   |  a percent sign        |",
"+-------+------------------------+",
NULL
};


const char * const border_help[] = {
"+--------------+---------------------------------------------------+",
"|  # of chars  |                  Style characters                 |",
"|   in style   |                     represent                     |",
"+--------------+---------------------------------------------------+",
"|      0       |  current graphic set                              |",
"|      1       |  entire border                                    |",
"|      2       |  vertical and horizontal edges                    |",
"|      3       |  corners, vertical and horizontal edges           |",
"|      4       |  left, right, top and bottom edges                |",
"|      5       |  top-left, top-right, bottom-left,                |",
"|              |    bottom-right corners and the edges             |",
"|      6       |  the four corners, vertical and horizontal edges  |",
"|      8       |  the four corners and the four edges              |",
"+--------------+---------------------------------------------------+",
NULL
};


const char * const exec_help[] = {
"+---------+----------------------------+",
"|  %[=]f  |  filename (relative path)  |",
"|  %[=]F  |  filename (absolute path)  |",
"|  %p     |  prompt for parameter      |",
"|  %w     |  copy the current word     |",
"|  %W     |  copy the current string   |",
"|  %%     |  a percent sign            |",
"+---------+----------------------------+",
"|    The filename will be quoted if    |",
"|    needed; '=' will prevent that.    |",
"+--------------------------------------+",
NULL
};


const char * const char_help[] = {
"+----------------------------------------+",
"|              Character Set             |",
"|                                        |",
"|    +-0-1-2-3-4-5-6-7-8-9-0-1-2-3-4-5-+ |",
"|   0|   \x01 \x02 \x03 \x04 \x05 \x06 \x07 "
       "\x08 \x09 \x0a \x0b \x0c \x0d \x0e \x0f | |",
"|  16| \x10 \x11 \x12 \x13 \x14 \x15 \x16 \x17 "
       "\x18 \x19 \x1a \x1b \x1c \x1d \x1e \x1f | |",
"|  32|   ! \" # $ % & ' ( ) * + , - . / | |",
"|  48| 0 1 2 3 4 5 6 7 8 9 : ; < = > ? | |",
"|  64| @ A B C D E F G H I J K L M N O | |",
"|  80| P Q R S T U V W X Y Z [ \\ ] ^ _ | |",
"|  96| ` a b c d e f g h i j k l m n o | |",
"| 112| p q r s t u v w x y z { | } ~  | |",
"| 128| � � � � � � � � � � � � � � � � | |",
"| 144| � � � � � � � � � � � � � � � � | |",
"| 160| � � � � � � � � � � � � � � � � | |",
"| 176| � � � � � � � � � � � � � � � � | |",
"| 192| � � � � � � � � � � � � � � � � | |",
"| 208| � � � � � � � � � � � � � � � � | |",
"| 224| � � � � � � � � � � � � � � � � | |",
"| 240| � � � � � � � � � � � � � � � � | |",
"|    +---------------------------------+ |",
"+----------------------------------------+",
NULL
};

#endif
